//
// Created by mafn on 11/2/16.
//

#ifndef MINOR_VIDYA_POINTOFVIEW_HPP
#define MINOR_VIDYA_POINTOFVIEW_HPP

#include "CoordinateDouble.hpp"
#include "../raycasting/RaycastingVector.hpp"

namespace Engine {
    class PointOfView {
    public:
        PointOfView(CoordinateDouble position, RaycastingVector direction, RaycastingVector camera_plane);
        PointOfView(const PointOfView& obj) = delete;            // Copy constructor for a base class has to be deleted (slicing)
        PointOfView& operator=(const PointOfView& obj) = delete; // Copy assignment for a base class has to be deleted (slicing)

        CoordinateDouble& get_position();
        RaycastingVector& get_direction();
        RaycastingVector& get_camera_plane();

    protected:
        CoordinateDouble _position;
        RaycastingVector _direction;
        RaycastingVector _camera_plane;

    private:

    };
}


#endif //MINOR_VIDYA_POINTOFVIEW_HPP
