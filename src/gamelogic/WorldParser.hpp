#ifndef WorldParser_HPP
#define WorldParser_HPP

#include <string>
#include <vector>
#include <cstring>
//#include "TileSet.hpp"
#include "Level.hpp"
#include "Tile.hpp"
#include "RapidXMLAdapter.hpp"

namespace GameLogic {

    using std::vector;
    using std::string;

    class WorldParser {
    public:
        WorldParser();
        ~WorldParser();

        Level generate_level( std::string file_location );
    };

};
#endif // !WorldParser_HPP