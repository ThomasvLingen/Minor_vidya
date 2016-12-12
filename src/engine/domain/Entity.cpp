//
// Created by wouter on 12/12/16.
//

#include "Entity.hpp"

namespace Engine{

    /// \brief Constructor of the class
    ///
    /// \param image_buffer The texture of the entity which will be used to draw the entity
    Entity::Entity(ImageBuffer* image_buffer, CoordinateInt* position)
    : _position(position)
    , _image_buffer(image_buffer)
    {

    }

    /// \brief Destructor of the class
    Entity::~Entity()
    {
        delete _position;
        delete _image_buffer;
    }

    /// \brief Getter for the position of the entity
    /// \return returns a CoordinateInt position
    CoordinateInt* Entity::get_position()
    {
        return _position;
    }

    /// \brief Getter for the image buffer of the entity
    /// \return returns an ImageBuffer
    ImageBuffer* Entity::get_image_buffer()
    {
        return _image_buffer;
    }
}
