#include "WorldParser.hpp"
#include <tuple>

namespace GameLogic {

    using std::tuple;
    using std::get;

    WorldParser::WorldParser()
    {
    }

    WorldParser::~WorldParser()
    {
    }

    /// \brief Generates a level from the source .tmx file
    /// 
    /// This function generates a Level object which has:
    /// * 2D vector of Tiles
    /// * TileSet struct
    /// needs to be inside try catch
    ///
    /// \param file_location location of the file to be used
    /// \param assets the assets manager for this .tmx
    /// \return returns a Level
    Level WorldParser::generate_level( std::string file_location, Engine::SPTR_AssetsManager assets )
    {
        RapidXMLAdapter* rapid_adapter = new RapidXMLAdapter();
        //TileSet* tile_set = new TileSet();
        vector<vector<size_t>> int_map;
        vector<vector<Tile*>> map;
        vector<tuple<size_t, size_t, char*>> object_list;
        CoordinateDouble spawn_point;
        rapid_adapter->setup_document( file_location );

        if ( !assets->init( rapid_adapter->get_texture_source(), rapid_adapter->get_tile_width(), rapid_adapter->get_tile_height(), rapid_adapter->get_tile_count() ) ) {
            std::cout << "AssetsManager has not initted correctly." << std::endl;
        }

        int_map = rapid_adapter->get_map();
        map = this->_generate_tilemap( int_map, assets );
        object_list = rapid_adapter->get_objects();

        for ( size_t i = 0; i < object_list.size(); i++ ) {
            if ( std::strcmp( get<2>( object_list[i] ), "PlayerSpawn" ) == 0 ) {
                int y = get<1>( object_list[i] );
                int x = get<0>( object_list[i] );
                if ( y < map.size() ) {
                    if ( x < map[y].size() ) {
                        if ( map[y][x]->is_wall() ) {
                            throw exception( "file invalid spawn point inside wall" );
                        }
                        else {
                            //our map is y,x based that's why spawn point is y,x
                            spawn_point = CoordinateDouble { y + this->_spawn_tile_offset, x + this->_spawn_tile_offset };
                        }

                    }
                    else {
                        throw exception( "file invalid spawn point out of map" );
                    }
                }
                else {
                    throw exception( "file invalid spawn point out of map" );
                }

            }
        }

        return Level( map, spawn_point, assets );
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
        for ( int y = 1; y < int_map.size(); y++ ) {
            vector<Tile*> map_row;
            for ( int x = 0; x < int_map[y].size(); x++ ) {
                Tile* new_tile = new Tile( assets->get_texture( int_map[y][x] ) );
                if ( int_map[y][x] != 0 ) {
                    new_tile->set_wall( true );
                }
                map_row.push_back( new_tile );
            }
            map.push_back( map_row );
        }
        return map;
    }
}