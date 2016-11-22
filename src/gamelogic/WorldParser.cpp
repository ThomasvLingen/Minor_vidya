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


        //tile_set->texture_source = rapid_adapter->get_texture_source();
        //tile_set->tile_size = rapid_adapter->get_tile_width();
        //tile_set->tile_size = rapid_adapter->get_tile_height();
        //tile_set->tile_size = rapid_adapter->get_tile_count();
        //tile_set->tile_size = rapid_adapter->get_tile_colomn_size();

        int_map = rapid_adapter->get_map();

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

        object_list = rapid_adapter->get_objects();

        for ( size_t i = 0; i < object_list.size(); i++ ) {
            if ( std::strcmp( get<2>( object_list[i] ), "PlayerSpawn" ) == 0 ) {
                if ( map[get<1>( object_list[i] )][get<0>( object_list[i] )]->is_wall() ) {
                    throw exception( "file invalid spawn point inside wall" );
                }
                else {
                    spawn_point = CoordinateDouble { get<1>( object_list[i] ) + 0.5, get<0>( object_list[i] ) + 0.5 };
                }
            }
            // Other Objects
            //else if ( std::strcmp(get<2>( object_list[i] ), "Other_Object" ) == 0 ) {
            //}
        }


        // generated_level needs to be deleted in the mainclass/gameloop when this level has been completed/finished/player quits.
        Level generated_level = Level( map, spawn_point, assets );
        //generated_level->tile_set = tile_set;

        return generated_level;
    }
}