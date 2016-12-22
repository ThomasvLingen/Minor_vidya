//
// Created by mafn on 12/13/16.
//

#include "CoordinateDouble.hpp"

namespace Engine {
    CoordinateDouble CoordinateDouble::operator-(const CoordinateDouble& other)
    {
        return CoordinateDouble {
            this->x - other.x,
            this->y - other.y
        };
    }

    CoordinateDouble CoordinateDouble::operator+( const CoordinateDouble& other )
    {
        return CoordinateDouble {
            this->x + other.x,
            this->y + other.y
        };
    }
}
