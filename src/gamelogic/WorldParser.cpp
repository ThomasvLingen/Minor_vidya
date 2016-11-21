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
    Level WorldParser::generate_level( std::string file_location )
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
                Tile* new_tile = new Tile;
                // when textures implemented if ( int_map[y][x] != 0 ) { set_wall( true ) }
                switch ( int_map[y][x] ) {
                case 1:
                    new_tile->set_wall( true );
                    new_tile->set_color( { 255,0,0 } );
                    break;
                case 2:
                    new_tile->set_wall( true );
                    new_tile->set_color( { 0,255,0 } );
                    break;
                case 3:
                    new_tile->set_wall( true );
                    new_tile->set_color( { 0,0,255 } );
                    break;
                case 4:
                    new_tile->set_wall( true );
                    new_tile->set_color( { 255,255,255 } );
                    break;
                default:
                    new_tile->set_wall( false );
                }
                map_row.push_back( new_tile );
            }
            map.push_back( map_row );
        }

        object_list = rapid_adapter->get_objects();

        for ( size_t i = 0; i < object_list.size(); i++ ) {
            if ( std::strcmp( get<2>( object_list[i] ), "PlayerSpawn" ) == 0 ) {
                spawn_point = CoordinateDouble{ get<0>( object_list[i] )+0.5, get<1>( object_list[i] )+0.5 };
            }
            // Other Objects
            //else if ( std::strcmp(get<2>( object_list[i] ), "Other_Object" ) == 0 ) {

            //}
        }

        // generated_level needs to be deleted in the mainclass/gameloop when this level has been completed/finished/player quits.
        Level generated_level = Level( map, spawn_point );
        //generated_level->tile_set = tile_set;

        return generated_level;
    }
}