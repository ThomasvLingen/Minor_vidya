//
// Created by wouter on 12/12/16.
//

#include "Entity.hpp"

namespace Engine{

    Entity::Entity(ImageBuffer* image_buffer, CoordinateInt* position)
    : _position(position)
    , _image_buffer(image_buffer)
    {

    }

    Entity::~Entity()
    {
        delete _position;
        delete _image_buffer;
    }

    CoordinateInt* Entity::get_position()
    {
        return _position;
    }

    ImageBuffer* Entity::get_image_buffer()
    {
        return _image_buffer;
    }
}
