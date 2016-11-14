//
// Created by waseland on 11/13/16.
//

#include "VectorUtil.hpp"

namespace GameLogic {

    VectorUtil::VectorUtil()
    {

    }
    VectorUtil::~VectorUtil()
    {

    }

    void VectorUtil::rotate_vector(double *x, double *y, double radians)
    {
        double old_x = *x;
        *x = *x * cos(radians) - *y * sin(radians);
        *y = old_x * sin(radians) + *y * cos(radians);
    }
}