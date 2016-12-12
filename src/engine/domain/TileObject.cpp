#include "TileObject.hpp"
#include "../../util/UnusedMacro.hpp"
#include "../../gamelogic/exceptions/InvalidTextureException.hpp"


namespace Engine {
    TileObject::TileObject(ImageBuffer* texture)
    : _texture(texture)
    {
    }

    TileObject::~TileObject()
    {
        if(_tiletrigger != nullptr){
            delete _tiletrigger;
        }
    }

    /// \brief update all objects in this particular tile.
    void TileObject::update(int delta_time)
    {
        UNUSED(delta_time)
        // TODO: Implement this
    }

    void TileObject::set_wall(bool has_wall)
    {
        this->_wall = has_wall;
    }

    bool TileObject::is_wall()
    {
        return this->_wall;
    }

    ImageBuffer* TileObject::get_texture()
    {
        if(this->_texture == nullptr){
            throw Exceptions::InvalidTextureException();
        } else {
            return this->_texture;
        }

    }

    void TileObject::set_texture(ImageBuffer* texture)
    {
        this->_texture = texture;
    }
}
