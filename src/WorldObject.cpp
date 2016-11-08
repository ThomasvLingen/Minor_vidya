#include "WorldObject.hpp"


namespace Engine {
    WorldObject::WorldObject(vector<vector<TileObject*>> field)
        : _field(field)
        , _point_of_view(CoordinateDouble{2 , 10}, RaycastingVector{-1 , 0}, RaycastingVector{0 , 0.66})
    {
    }

    WorldObject::~WorldObject()
    {
    }

    void WorldObject::update()
    {
        // TODO: Implement this
    }

    PointOfView & WorldObject::get_pov()
    {
        return this->_point_of_view;
    }

    TileObject * WorldObject::get_tile(int x, int y)
    {
        try {
            return this->_field[y][x];
        }
        catch (const std::exception&) {
            return nullptr;
        }
    }
}
