#include "WorldParser.hpp"
#include <tuple>
#include "exceptions/FileInvalidException.hpp"

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
    void WorldParser::fill_level(Level& level, string file_location)
    {
        RapidXMLAdapter rapid_adapter;
        vector<vector<size_t>> int_map;
        vector<tuple<size_t, size_t, char*>> object_list;

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
        for ( int y = 1; y < int_map.size(); y++ ) {
            for ( int x = 0; x < int_map[y].size(); x++ ) {
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
    void WorldParser::_set_objects( Level& level, vector<tuple<size_t, size_t, char*>> object_list, RapidXMLAdapter& rapid_adapter, string path )
    {
        for (auto object : object_list) {
            if ( std::strcmp( get<2>( object ), "PlayerSpawn" ) == 0 ) {
                size_t y = get<1>( object );
                size_t x = get<0>( object );
                if ( y < level.get_field().size() && x < level.get_field()[y].size() ) {
                    if ( level.get_field()[y][x]->is_wall() ) {
                        throw FileInvalidException();
                    }
                    else {
                        //our map is y,x based that's why spawn point is y,x
                        level.set_spawnpoint(CoordinateDouble { y + this->_spawn_tile_offset, x + this->_spawn_tile_offset });
                    }
                }
                else {
                    throw FileInvalidException();
                }
            }
            else if ( std::strcmp( get<2>( object ), "Entity" ) == 0 ) {
                size_t y = get<1>( object );
                size_t x = get<0>( object );
                if ( y < level.get_field().size() && x < level.get_field()[y].size() ) {
                    level.get_entities().push_back(new Engine::Entity(level.assets->get_entity_texture( path + rapid_adapter.get_entity_texture(x,y)),CoordinateDouble{ y + this->_spawn_tile_offset, x + this->_spawn_tile_offset }));
                }
            }
            else if ( std::strcmp( get<2>( object ), "DoorTrigger" ) == 0 ) {
                size_t y = get<1>( object );
                size_t x = get<0>( object );
                if ( y < level.get_field().size() && x < level.get_field()[y].size() ) {
                    std::function<void( Level& )> door = [y, x] ( Level& level ) {
                        level.get_field()[y][x]->set_wall( !level.get_field()[y][x]->is_wall() );
                    };

                    TileTrigger* tileTrigger = new TileTrigger( door );
                    level.get_field()[y][x]->add_action_tiletrigger( tileTrigger );
                }
            }
        }
    }
}