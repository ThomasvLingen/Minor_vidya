#ifndef WorldParser_HPP
#define WorldParser_HPP

#include <string>
#include <vector>
#include <cstring>
#include "Level.hpp"
#include "Tile.hpp"
#include "rapidxml/RapidXMLAdapter.hpp"

namespace GameLogic {

    using std::vector;
    using std::string;

    class WorldParser {
    public:
        WorldParser();
        ~WorldParser();

        Level generate_level( std::string file_location, Engine::SPTR_AssetsManager assets );
    private:
        vector<vector<Tile*>> _generate_tilemap( vector<vector<size_t>> int_map, Engine::SPTR_AssetsManager assets );
        CoordinateDouble _get_spawnpoint( vector<tuple<size_t, size_t, char*>> object_list, vector<vector<Tile*>> map );
        double _spawn_tile_offset = 0.5;
    };

};
#endif // !WorldParser_HPP