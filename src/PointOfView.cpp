//
// Created by mafn on 11/2/16.
//

#include "PointOfView.hpp"

namespace Engine {

    PointOfView::PointOfView(DoubleCoordinate position, Vector direction, Vector camera_plane)
    : _position(position)
    , _direction(direction)
    , _camera_plane(camera_plane)
    {
        
    }

    PointOfView::~PointOfView()
    {

    }

    DoubleCoordinate &Engine::PointOfView::get_position()
    {
        return this->_position;
    }

    Vector &Engine::PointOfView::get_direction()
    {
        return this->_direction;
    }

    Vector &Engine::PointOfView::get_camera_plane()
    {
        return this->_camera_plane;
    }
}
