//
// Created by wouter on 12/12/16.
//

#include "Entity.hpp"
#include "../../gamelogic/exceptions/InvalidTextureException.hpp"

namespace Engine{

    Entity::Entity(AnimatedTexture* animated_texture, CoordinateDouble position)
    : _position(position)
    , _animated_texture(animated_texture)
    {

    }

    /// \brief Destructor of the class
    Entity::~Entity()
    {
        delete this->_animated_texture;
    }

    void Entity::update(int delta_time)
    {
        if (this->_animated_texture != nullptr) {
            this->_animated_texture->update(delta_time);
        }
    }

    /// \brief Getter for the position of the entity
    /// \return returns a CoordinateInt position
    CoordinateDouble& Entity::get_position()
    {
        return this->_position;
    }

    /// \brief Getter for the image buffer of the entity
    /// \return returns an ImageBuffer
    ImageBuffer& Entity::get_texture()
    {
        return this->_animated_texture->get_texture();
    }

    int Entity::get_texture_width()
    {
        return (int)this->_animated_texture->get_texture_width();
    }

    int Entity::get_texture_height()
    {
        return (int)this->_animated_texture->get_texture_height();
    }
}
