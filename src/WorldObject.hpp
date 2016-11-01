#ifndef WORLDOBJECT_HPP
#define WORLDOBJECT_HPP

#include "PointOfView.hpp"
#include "TileObject.hpp"
#include <vector>

using std::vector;

class WorldObject
{

private:
	vector<vector<TileObject*>> _field;
	PointOfView _point_of_view;

public:
	WorldObject(vector<vector<TileObject*>> field);
	~WorldObject();

	void update();
	TileObject* get_tile(int x, int y);

};

#endif // !WORLDOBJECT_HPP

