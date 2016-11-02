//
// Created by mafn on 11/2/16.
//

#ifndef MINOR_VIDYA_POINTOFVIEW_HPP
#define MINOR_VIDYA_POINTOFVIEW_HPP

#include "DoubleCoordinate.hpp"
#include "Vector.hpp"

namespace Engine {
    class PointOfView {
    public:

        PointOfView(DoubleCoordinate position, Vector direction, Vector camera_plane);
        virtual ~PointOfView();

        DoubleCoordinate& get_position();
        Vector& get_direction();
        Vector& get_camera_plane();

    private:
        DoubleCoordinate _position;
        Vector _direction;
        Vector _camera_plane;
    };
}


#endif //MINOR_VIDYA_POINTOFVIEW_HPP
