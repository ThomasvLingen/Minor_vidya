//
// Created by waseland on 12/12/16.
//

#include "TileTrigger.hpp"

namespace Engine {
    TileTrigger::TileTrigger(function<void(World&)>* event)
    : _event(event)
    {

    }

    TileTrigger::~TileTrigger()
    {

    }

    void TileTrigger::make_call(World &world)
    {
        (*this->_event)(world);
    }

}

