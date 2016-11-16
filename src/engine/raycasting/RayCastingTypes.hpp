//
// Created by jazula on 11/2/16.
//

#ifndef MINOR_VIDYA_RAYCASTINGTYPES_HPP
#define MINOR_VIDYA_RAYCASTINGTYPES_HPP

#include "RaycastingVector.hpp"

namespace Engine {
    enum class WallSide {x_wall, y_wall};

    struct RayStep {
        double side_distance;
        int step_size;
    };

    struct RaySteps {
        RayStep x;
        RayStep y;
    };

    struct DeltaDist {
        double x;
        double y;
    };

    struct CoordinateInt {
        int x;
        int y;
    };

    typedef RaycastingVector Direction;

    struct LineCords {
        int draw_start;
        int draw_end;
    };

    struct Wall {
        CoordinateInt cord;
        WallSide side;
    };
}

#endif //MINOR_VIDYA_RAYCASTINGTYPES_HPP
