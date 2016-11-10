#include "WorldObject.hpp"


<<<<<<< HEAD
namespace Engine {
    WorldObject::WorldObject(vector<vector<TileObject*>> field)
    : _field(field)
    , _point_of_view(CoordinateDouble{2 , 10}, RaycastingVector{-1 , 0}, RaycastingVector{0 , 0.66})
    {
    }
=======
WorldObject::WorldObject()
//: _point_of_view(Engine::CoordinateDouble{2 , 10}, Engine::RaycastingVector{-1 , 0}, Engine::RaycastingVector{0 , 0.66})
{
}
>>>>>>> feat: Changed Game Classes

    WorldObject::~WorldObject()
    {
    }

    /// \brief update all objects in this WorldObject.
    void WorldObject::update()
    {
        // TODO: Implement this
    }

<<<<<<< HEAD
    PointOfView& WorldObject::get_pov()
    {
        return this->_point_of_view;
    }

    TileObject* WorldObject::get_tile(int x, int y)
    {
        try {
            return this->_field[y][x];
        }
        catch (const std::exception&) {
            return nullptr;
        }
    }
}
=======


>>>>>>> feat: Changed Game Classes
