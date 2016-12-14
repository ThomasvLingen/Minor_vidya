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
        vector<vector<Tile*>> _generate_tilemap( vector<vector<size_t>> int_map, Engine::SPTR_AssetsManager assets );
        CoordinateDouble _get_spawnpoint( vector<tuple<size_t, size_t, char*>> object_list, vector<vector<Tile*>> map );
        void _set_objects( Level& level, vector<tuple<size_t, size_t, char*>> object_list, vector<vector<Tile*>> map, Engine::SPTR_AssetsManager assets, RapidXMLAdapter& rapid_adapter, string path );
        double _spawn_tile_offset = 0.5;
        string _path;
    };

};
#endif // !WorldParser_HPP