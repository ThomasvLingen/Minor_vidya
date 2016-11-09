//
// Created by waseland on 11/7/16.
//

#ifndef MINOR_VIDYA_TILE_HPP
#define MINOR_VIDYA_TILE_HPP

#include "../TileObject.hpp"
#include <vector>
#include <map>
#include "../Color.hpp"

// index for neighbour TileObject
#define to_up_neighbour_index 0
#define to_down_neighbour_index 1
#define to_left_neighbour_index 2
#define to_right_neighbour_index 3

using std::vector;
using std::string;
using std::map;

class Tile : public TileObject {

public:
    enum Direction { up_tile, down_tile, left_tile, right_tile };

private:
    bool _wall;
    Color _color;
    const int _width = 1;		// TODO: implement width value
    const int _length = 1;		// TODO: implement height value
    vector<TileObject*> _neighbour_tiles;
    map<Direction, int> _direction_to_num_map = {
            {Direction::up_tile, to_up_neighbour_index},
            {Direction::down_tile, to_down_neighbour_index},
            {Direction::left_tile, to_left_neighbour_index},
            {Direction::right_tile, to_right_neighbour_index},

    };


public:
    Tile();
    virtual ~Tile();
    void update();

    void set_wall(bool has_wall);
    void set_color(Color color);

    void set_tile_neighbour(TileObject * tile, Direction direction);

    TileObject* get_tile_neighbour(Direction direction);

    bool is_wall();
    Color get_color();


};


#endif //MINOR_VIDYA_TILE_HPP
