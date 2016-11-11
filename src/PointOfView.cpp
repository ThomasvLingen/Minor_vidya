//
// Created by mafn on 11/2/16.
//

#include "PointOfView.hpp"

namespace Engine {

    PointOfView::PointOfView(CoordinateDouble position, RaycastingVector direction, RaycastingVector camera_plane)
    : _position(position)
    , _direction(direction)
    , _camera_plane(camera_plane)
    {

    }

    PointOfView::~PointOfView()
    {

    }

    CoordinateDouble &PointOfView::get_position()
    {
        return this->_position;
    }

    RaycastingVector &PointOfView::get_direction()
    {
        return this->_direction;
    }

    RaycastingVector &PointOfView::get_camera_plane()
    {
        return this->_camera_plane;
    }
}
