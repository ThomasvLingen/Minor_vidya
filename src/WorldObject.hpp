#ifndef WORLDOBJECT_HPP
#define WORLDOBJECT_HPP

#include "TileObject.hpp"
#include "PointOfView.hpp"
#include <vector>

using std::vector;
using Engine::PointOfView;

class WorldObject{

private:
	vector<vector<TileObject*>> _field;
	PointOfView _point_of_view;

public:
	WorldObject(vector<vector<TileObject*>> field);
	virtual ~WorldObject();

	void update();

	PointOfView& get_pov();
	TileObject* get_tile(int x, int y);

};

#endif // !WORLDOBJECT_HPP

