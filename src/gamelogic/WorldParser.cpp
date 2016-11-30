#include "WorldParser.hpp"
#include <tuple>
#include "Exceptions/FileInvalidException.hpp"


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
        vector<vector<size_t>> int_map;
        vector<vector<Tile*>> map;
        vector<tuple<size_t, size_t, char*>> object_list;
        CoordinateDouble spawn_point;
        rapid_adapter->setup_document( file_location );

        if ( !assets->init( "res/" + rapid_adapter->get_texture_source(), rapid_adapter->get_tile_width(), rapid_adapter->get_tile_height(), rapid_adapter->get_tile_count() ) ) {
            std::cout << "AssetsManager has not initted correctly." << std::endl;
        }

        int_map = rapid_adapter->get_map();
        map = this->_generate_tilemap( int_map, assets );
        object_list = rapid_adapter->get_objects();
        spawn_point = this->_get_spawnpoint(object_list, map);
        
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
        map.resize( int_map.size());
        //start at y = 1 as .tmx starts with empty row
        for ( int y = 1; y < int_map.size(); y++ ) {
            for ( int x = 0; x < int_map[y].size(); x++ ) {
                Tile* new_tile = new Tile( assets->get_texture( int_map[y][x] ) );
                if ( int_map[y][x] != 0 ) {
                    new_tile->set_wall( true );
                }
                map[y].push_back( new_tile );
            }
        }
        return map;
    }

    /// \brief Checks and gets the location of the spawnpoint object
    /// 
    /// This function  Checks and gets the location of the spawnpoint object of the .tmx.
    ///
    /// \param object_list the object list which contains a spwanpoint
    /// \param map the tilemap
    /// \return returns a CoordinateDouble of the spawnlocation
    CoordinateDouble WorldParser::_get_spawnpoint( vector<tuple<size_t, size_t, char*>> object_list, vector<vector<Tile*>> map )
    {
        for ( size_t i = 0; i < object_list.size(); i++ ) {
            if ( std::strcmp( get<2>( object_list[i] ), "PlayerSpawn" ) == 0 ) {
                int y = get<1>( object_list[i] );
                int x = get<0>( object_list[i] );
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
    }
}