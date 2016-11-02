#ifndef TILEOBJECT_HPP
#define TILEOBJECT_HPP

#include <vector>
#include <map>
#include "Color.hpp"

// index for neighbour TileObject
#define to_up_neighbour_index 0
#define to_down_neighbour_index 1
#define to_left_neighbour_index 2
#define to_right_neighbour_index 3

using std::vector;
using std::string;
using std::map;

class TileObject{

public:
	enum Direction { up_tile, down_tile, left_tile, right_tile };	// direction for set_tile

private:
	bool _wall;
	Color _color;
	const int _width = 1;		// TODO: implement width value
	const int _length = 1;		// TODO: implement height value
	vector<TileObject*> _neighbour_tiles;
	map<Direction, int> _direction_to_num_map;

public:

	TileObject();
	virtual ~TileObject();
	void update();

	void set_wall(bool has_wall);
	void set_color(Color color);

	void set_tile_neighbour(TileObject* tile, Direction direction);
	
	TileObject* get_tile_neighbour(Direction direction);

	bool is_wall();
	Color get_color();
	
};


#endif // !TILEOBJECT_HPP



