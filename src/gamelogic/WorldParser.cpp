#include "WorldParser.hpp"
#include <tuple>
#include "exceptions/FileInvalidException.hpp"
#include "Player.hpp"

namespace GameLogic {
    using Exceptions::FileInvalidException;
    using std::tuple;
    using std::get;

    WorldParser::WorldParser()
    {
    }

    WorldParser::~WorldParser()
    {
    }

    /// \brief Fills a level using a source .tmx file
    /// 
    /// This function fills a Level object which has:
    /// * 2D vector of Tiles
    /// * TileSet struct
    /// needs to be inside try catch
    ///
    /// \param level level to fill
    /// \param file_location location of the file to be used
    void WorldParser::fill_level(Level& level, std::string file_location)
    {
        RapidXMLAdapter rapid_adapter;
        vector<vector<size_t>> int_map;
        vector<tuple<size_t, size_t, size_t, char*>> object_list;

        rapid_adapter.setup_document( file_location );
        string path = file_location.substr( 0, file_location.find_last_of( "\\/" ) ) + "/";
        if ( !level.assets->init( path + rapid_adapter.get_texture_source(), rapid_adapter.get_tile_width(), rapid_adapter.get_tile_height(), rapid_adapter.get_tile_count() ) ) {
            std::cout << "AssetsManager has not initted correctly." << std::endl;
        }

        int_map = rapid_adapter.get_map();
        level.set_field(
            this->_generate_tilemap(int_map, level.assets)
        );

        object_list = rapid_adapter.get_objects();
        this->_set_objects( level, object_list, rapid_adapter, path );
    }

    /// \brief Generates a 2D Tile vector from the int_map
    /// 
    /// This function generates a 2D Tile vector and adds the correct texture to the tiles
    ///
    /// \param int_map the integer valued that the tilemap needs to be generated from
    /// \param assets the assets manager of this .tmx
    /// \return returns a 2D Tile vector
    vector<vector<Tile*>> WorldParser::_generate_tilemap( vector<vector<size_t>> int_map, Engine::SPTR_AssetsManager assets )
    {
        vector<vector<Tile*>> map;
        map.resize( int_map.size());
        //start at y = 1 as .tmx starts with empty row
        for ( size_t y = 1; y < int_map.size(); y++ ) {
            for ( size_t x = 0; x < int_map[y].size(); x++ ) {
                Tile* new_tile = new Tile( assets->get_texture( (int)int_map[y][x] ) );
                new_tile->set_wall( int_map[y][x] != 0 );
                map[y-1].push_back( new_tile );
            }
        }
        return map;
    }

    /// \brief Checks and sets the location of other object
    /// 
    /// This function  Checks and sets the location of other object of the .tmx.
    ///
    /// \param level ref of level being made
    /// \param object_list list of all the object needed to be set
    /// \param rapid_adapter ref of current rapid_adapter
    /// \param path path to .tmx folder
    void WorldParser::_set_objects( Level& level, vector<tuple<size_t, size_t, size_t, char*>> object_list, RapidXMLAdapter& rapid_adapter, string path )
    {
        int spawnpoint_count = 0;
        for ( auto object : object_list ) {
            size_t y = get<2>( object );
            size_t x = get<1>( object );
            if ( y < level.get_field().size() && x < level.get_field()[y].size() ) {
                if ( std::strcmp( get<3>( object ), "PlayerSpawn" ) == 0 ) {
                    this->_set_spawnpoint(level, y, x);
                    spawnpoint_count++;
                }
                else if ( std::strcmp( get<3>( object ), "Entity" ) == 0 ) {
                    size_t id = get<0>( object );
                    this->_set_entity(level, y, x, id, rapid_adapter, path);
                }
                else if ( std::strcmp( get<3>( object ), "DoorTrigger" ) == 0 ) {
                    this->_set_door_trigger( level, y, x);
                }
                else if ( std::strcmp( get<2>( object ), "WinTrigger" ) == 0 ) {
                    this->_set_win_trigger( level, y, x );
                }
            }
        }
        if ( spawnpoint_count != 1 ) {
            throw FileInvalidException();
        }
    }

    /// \brief Sets spawnpoint on tile
    /// 
    /// This function sets spawnpoint on tile on location y,x
    ///
    /// \param level reference to current level
    /// \param y y position of the tile
    /// \param x x position of the tile
    void WorldParser::_set_spawnpoint( Level& level, size_t y, size_t x )
    {
        if ( level.get_field()[y][x]->is_wall() ) {
            throw FileInvalidException();
        }
        else {
            //our map is y,x based that's why spawn point is y,x
            level.set_spawnpoint( CoordinateDouble { y + this->_spawn_tile_offset, x + this->_spawn_tile_offset } );
        }
    }

    void WorldParser::_set_entity( Level & level, size_t y, size_t x, size_t id, RapidXMLAdapter & rapid_adapter, string path )
    {
        CoordinateDouble entity_spawn = { y + this->_spawn_tile_offset, x + this->_spawn_tile_offset };
        Engine::ImageBuffer* entitybuffer = level.assets->get_entity_texture( path + rapid_adapter.get_entity_texture( id ) );
        if ( entitybuffer == nullptr ) {
            throw FileInvalidException();
        }
        Engine::Entity* new_entity = new Engine::Entity( entitybuffer, entity_spawn );
        level.get_entities().push_back( new_entity );
    }

    /// \brief Sets door trigger on tile
    /// 
    /// This function sets door trigger on tile on location y,x
    ///
    /// \param level reference to current level
    /// \param y y position of the tile
    /// \param x x position of the tile
    void WorldParser::_set_door_trigger( Level & level, size_t y, size_t x )
    {
        std::function<void( Level& )> door = [y, x] ( Level& level ) {
            level.get_field()[y][x]->set_wall( !level.get_field()[y][x]->is_wall() );
        };
        level.get_field()[y][x]->add_action_tiletrigger( new TileTrigger( door ) );
    }

    /// \brief Sets win trigger on tile
    /// 
    /// This function sets win trigger on tile on location y,x
    ///
    /// \param level reference to current level
    /// \param y y position of the tile
    /// \param x x position of the tile
    void WorldParser::_set_win_trigger( Level & level, int y, int x )
    {
        std::function<void( Level& )> win = [] ( Level& level ) {
            level.set_level_over();
        };
        level.get_field()[y][x]->add_step_on_tiletrigger( new TileTrigger( win ) );
    }
}