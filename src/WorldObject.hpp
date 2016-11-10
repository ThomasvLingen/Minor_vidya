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

public:
	virtual void update() = 0;

	virtual PointOfView& get_pov() = 0;
	virtual TileObject* get_tile(int x, int y) = 0; //TODO: int x/y too coordinate double?

};

#endif // !WORLDOBJECT_HPP

