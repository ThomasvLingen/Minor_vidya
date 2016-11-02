#ifndef TILEOBJECT_HPP
#define TILEOBJECT_HPP

#include <vector>
#include "Color.hpp"

#define up 0
#define down 1
#define left 2
#define right 3

using std::vector;
using std::string;

class TileObject
{
private:
	bool wall;
	const static int _width;
	const static int _length;
	vector<TileObject*> _neighbour_tiles;

public:
	TileObject();
	~TileObject();
	void update();

	void set_tile_up(TileObject* up_tile);
	void set_tile_down(TileObject* down_tile);
	void set_tile_left(TileObject* left_tile);
	void set_tile_right(TileObject* right_tile);

	TileObject* get_tile_up();
	TileObject* get_tile_down();
	TileObject* get_tile_left();
	TileObject* get_tile_right();

	bool get_is_wall();
	
};


#endif // !TILEOBJECT_HPP



