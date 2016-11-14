//
// Created by waseland on 11/13/16.
//

#ifndef MINOR_VIDYA_VECTORUTIL_HPP
#define MINOR_VIDYA_VECTORUTIL_HPP

#include <cmath>

namespace GameLogic {

    class VectorUtil {
    public:
        VectorUtil();
        virtual ~VectorUtil();

        static void rotate_vector(double* vector_x, double* vector_y, double radians);
    };

}

#endif //MINOR_VIDYA_VECTORUTIL_HPP
