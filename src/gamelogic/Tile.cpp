//
// Created by waseland on 11/7/16.
//

#include "Tile.hpp"
#include "../util/UnusedMacro.hpp"

namespace GameLogic {

    Tile::Tile(ImageBuffer* texture)
    : TileObject(texture)
    {

    }

    Tile::~Tile()
    {
        for(auto it : this->_step_on_tiletriggers){
            delete it;
        }
        for(auto it : this->_action_tiletriggers){
            delete it;
        }
    }

    void Tile::update(int delta_time)
    {
        UNUSED(delta_time)
        //TODO implement
    }

    vector<TileTrigger *> Tile::get_action_tiletriggers()
    {
        return this->_action_tiletriggers;
    }

    void Tile::add_action_tiletrigger(TileTrigger* tiletrigger)
    {
        this->_action_tiletriggers.push_back(tiletrigger);
    }

    vector<TileTrigger *> Tile::get_step_on_tiletriggers()
    {
        return this->_step_on_tiletriggers;
    }

    void Tile::add_step_on_tiletrigger(TileTrigger* tiletrigger)
    {
        this->_step_on_tiletriggers.push_back(tiletrigger);
    }
}