#ifndef WORLDOBJECT_HPP
#define WORLDOBJECT_HPP

#include "TileObject.hpp"
#include "PointOfView.hpp"
#include "CoordinateDouble.hpp"
#include <vector>

using std::vector;
using Engine::PointOfView;
using Engine::CoordinateDouble;

class WorldObject{

private:
	//vector<vector<TileObject*>> _field;
	//PointOfView _point_of_view;

public:
	WorldObject();
	virtual ~WorldObject();

	void update();

	virtual PointOfView& get_pov() = 0;
	virtual TileObject* get_tile(int x, int y) = 0;

};

#endif // !WORLDOBJECT_HPP

