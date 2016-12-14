#ifndef WorldParser_HPP
#define WorldParser_HPP

#include <string>
#include <vector>
#include <cstring>
#include "Level.hpp"
#include "Tile.hpp"
#include "rapidXML/RapidXMLAdapter.hpp"
#include "TileTrigger.hpp"

namespace GameLogic {

    using std::vector;
    using std::string;

    class WorldParser {
    public:
        WorldParser();
        ~WorldParser();

        void fill_level(Level& level, string file_location);
    private:
        RapidXMLAdapter _rapid_adapter;
        vector<vector<Tile*>> _generate_tilemap( vector<vector<int>> int_map, Engine::SPTR_AssetsManager assets );
        CoordinateDouble _get_spawnpoint( vector<tuple<int, int, char*>> object_list, vector<vector<Tile*>> map );
        void _set_objects( Level& level, vector<tuple<int, int, char*>> object_list, vector<vector<Tile*>> map, Engine::SPTR_AssetsManager assets, string file_location );
        double _spawn_tile_offset = 0.5;
        string _path;
    };

};
#endif // !WorldParser_HPP