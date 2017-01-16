//
// Created by mafn on 11/2/16.
//

#ifndef MINOR_VIDYA_COORDINATE_HPP
#define MINOR_VIDYA_COORDINATE_HPP

namespace Engine {
    struct CoordinateDouble {
        double x;
        double y;

        CoordinateDouble operator-(const CoordinateDouble& other);
        CoordinateDouble operator+(const CoordinateDouble& other);
    };
}

#endif //MINOR_VIDYA_COORDINATE_HPP
