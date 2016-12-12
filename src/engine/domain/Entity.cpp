//
// Created by wouter on 12/12/16.
//

#include "Entity.hpp"

namespace Engine{

    CoordinateInt* Entity::get_position()
    {
        return _position;
    }

    ImageBuffer* Entity::get_image_buffer()
    {
        return _image_buffer;
    }
}
