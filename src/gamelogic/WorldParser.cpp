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
        vector<tuple<size_t, size_t, char*>> object_list;

        rapid_adapter.setup_document( file_location );
        string path = file_location.substr( 0, file_location.find_last_of( "\\/" ) ) + "/" + rapid_adapter.get_texture_source();
        if ( !level.assets->init( path, rapid_adapter.get_tile_width(), rapid_adapter.get_tile_height(), rapid_adapter.get_tile_count() ) ) {
            std::cout << "AssetsManager has not initted correctly." << std::endl;
        }

        int_map = rapid_adapter.get_map();
        level.set_field(
            this->_generate_tilemap(int_map, level.assets)
        );

        object_list = rapid_adapter.get_objects();

        level.set_spawnpoint(
            this->_get_spawnpoint(object_list, level.get_field())
        );

        this->_set_objects(object_list, level.get_field());
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

    /// \brief Checks and gets the location of the spawnpoint object
    /// 
    /// This function  Checks and gets the location of the spawnpoint object of the .tmx.
    ///
    /// \param object_list the object list which contains a spawnpoint
    /// \param map the tilemap
    /// \return returns a CoordinateDouble of the spawnlocation
    CoordinateDouble WorldParser::_get_spawnpoint( vector<tuple<size_t, size_t, char*>> object_list, vector<vector<Tile*>> map )
    {
        for ( size_t i = 0; i < object_list.size(); i++ ) {
            if ( std::strcmp( get<2>( object_list[i] ), "PlayerSpawn" ) == 0 ) {
                size_t y = get<1>( object_list[i] );
                size_t x = get<0>( object_list[i] );
                if ( y < map.size() && x < map[y].size() ) {
                    if ( map[y][x]->is_wall() ) {
                        throw FileInvalidException();
                    }
                    else {
                        //our map is y,x based that's why spawn point is y,x
                        return CoordinateDouble { y + this->_spawn_tile_offset, x + this->_spawn_tile_offset };
                    }
                }
                else {
                    throw FileInvalidException();
                }

            }
        }
        throw FileInvalidException();
    }

    /// \brief Checks and sets the location of other object
    /// 
    /// This function  Checks and sets the location of other object of the .tmx.
    ///
    /// \param object_list the object list
    /// \param map the tilemap
    void WorldParser::_set_objects( vector<tuple<size_t, size_t, char*>> object_list, vector<vector<Tile*>> map )
    {
        for ( auto object : object_list) {
            int y = get<1>( object );
            int x = get<0>( object );
            if ( y < map.size() && x < map[y].size() ) {
                if ( std::strcmp( get<2>( object ), "DoorTrigger" ) == 0 ) {
                    std::function<void( Level& )> door = [y, x]( Level& level) {
                        level.get_tile_in_level({y, x})->set_wall(!level.get_tile_in_level({y, x })->is_wall());
                    };
                    TileTrigger* tileTrigger = new TileTrigger(door);
                    map[y][x]->add_action_tiletrigger(tileTrigger);
                }
                else if ( std::strcmp( get<2>( object ), "WinTrigger" ) == 0 ){
                    std::function<void( Level& )> door = [y, x]( Level& level) {
                        level.set_level_over();
                    };
                    TileTrigger* tileTrigger = new TileTrigger( door );
                    map[y][x]->add_step_on_tiletrigger( tileTrigger );

                }
            }
        }
    }
}