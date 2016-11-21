#ifndef TILEOBJECT_HPP
#define TILEOBJECT_HPP

#include <vector>
#include <map>
#include "Color.hpp"
#include "../SDLFacade.hpp"


namespace Engine {
    using std::vector;
    using std::string;
    using std::map;

    class TileObject {

    public:
        // direction for set_tile
        // Maps to a position in the _neighbour_tiles vector
        enum class Direction {
            up_tile    = 0,
            down_tile  = 1,
            left_tile  = 2,
            right_tile = 3
        };

    private:
        bool _wall;
        Color _color;
        const int _width = 1;        // TODO: implement width value
        const int _length = 1;        // TODO: implement height value
        vector<TileObject*> _neighbour_tiles;
        ImageBuffer& _texture;

    public:
        TileObject(ImageBuffer& texture);
        TileObject(const TileObject& obj) = delete;            // Copy constructor for a base class has to be deleted (slicing)
        TileObject& operator=(const TileObject& obj) = delete; // Copy assignment for a base class has to be deleted (slicing)

        virtual void update(int delta_time);

        void set_wall(bool has_wall);
        void set_color(Color color);

        void set_tile_neighbour(TileObject* tile, Direction direction);

        TileObject* get_tile_neighbour(Direction direction);

        bool is_wall();
        Color get_color();
    };
}

#endif // !TILEOBJECT_HPP



