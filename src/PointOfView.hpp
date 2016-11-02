//
// Created by mafn on 11/2/16.
//

#ifndef MINOR_VIDYA_POINTOFVIEW_HPP
#define MINOR_VIDYA_POINTOFVIEW_HPP

#include "DoubleCoordinate.hpp"
#include "RaycastingVector.hpp"

namespace Engine {
    class PointOfView {
    public:

        PointOfView(DoubleCoordinate position, RaycastingVector direction, RaycastingVector camera_plane);
        virtual ~PointOfView();

        DoubleCoordinate& get_position();
        RaycastingVector& get_direction();
        RaycastingVector& get_camera_plane();

    private:
        DoubleCoordinate _position;
        RaycastingVector _direction;
        RaycastingVector _camera_plane;
    };
}


#endif //MINOR_VIDYA_POINTOFVIEW_HPP
