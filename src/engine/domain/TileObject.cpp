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
        for(auto it : this->_step_on_tiletriggers){
            delete it;
        }
        for(auto it : this->_action_tiletriggers){
            delete it;
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
        if (this->_texture == nullptr){
            throw Exceptions::InvalidTextureException();
        } else {
            return this->_texture;
        }

    }

    void TileObject::set_texture(ImageBuffer* texture)
    {
        this->_texture = texture;
    }

    vector<TileTrigger *> TileObject::get_action_tiletriggers()
    {
        return this->_action_tiletriggers;
    }

    void TileObject::add_action_tiletrigger(TileTrigger* tiletrigger)
    {
        this->_action_tiletriggers.push_back(tiletrigger);
    }

    vector<TileTrigger *> TileObject::get_step_on_tiletriggers()
    {
        return this->_step_on_tiletriggers;
    }

    void TileObject::add_step_on_tiletrigger(TileTrigger* tiletrigger)
    {
        this->_step_on_tiletriggers.push_back(tiletrigger);
    }
}
