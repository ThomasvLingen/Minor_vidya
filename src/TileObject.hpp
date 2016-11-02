#ifndef TILEOBJECT_HPP
#define TILEOBJECT_HPP

#include <vector>
#include "Color.hpp"

// index for neighbour TileObject
#define to_up_neighbour_index 0
#define to_down_neighbour_index 1
#define to_left_neighbour_index 2
#define to_right_neighbour_index 3

using std::vector;
using std::string;

class TileObject{

private:
	bool _wall;
	Color _color;
	const static int _width = 1;		// TODO: implement width value
	const static int _length = 1;		// TODO: implement height value
	vector<TileObject*> _neighbour_tiles;

public:
	TileObject();
	virtual ~TileObject();
	void update();

	void set_wall(bool has_wall);
	void set_color(Color color);

	void set_tile_up(TileObject* up_tile);
	void set_tile_down(TileObject* down_tile);
	void set_tile_left(TileObject* left_tile);
	void set_tile_right(TileObject* right_tile);

	TileObject* get_tile_up();
	TileObject* get_tile_down();
	TileObject* get_tile_left();
	TileObject* get_tile_right();

	bool is_wall();
	Color get_color();
	
};


#endif // !TILEOBJECT_HPP



