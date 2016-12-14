//
// Created by waseland on 12/12/16.
//

#include "TileTrigger.hpp"

namespace GameLogic {
    TileTrigger::TileTrigger(function<void(Level&)> event)
    : _event(event)
    {

    }

    TileTrigger::~TileTrigger()
    {

    }

    void TileTrigger::make_call(Level& world)
    {
        this->_event(world);
    }
}

