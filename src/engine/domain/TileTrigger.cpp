//
// Created by waseland on 12/12/16.
//

#include <iostream>
#include "TileTrigger.hpp"

namespace Engine {
    TileTrigger::TileTrigger(bool step_on, function<void(World&)> event)
    : _event(event)
    , _step_on(step_on)
    {

    }

    TileTrigger::~TileTrigger()
    {

    }

    void TileTrigger::make_call(World &world)
    {
        this->_event(world);
    }

    bool TileTrigger::is_step_on_trigger()
    {
        return this->_step_on;
    }
}

