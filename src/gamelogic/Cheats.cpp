//
// Created by mafn on 1/16/17.
//

#include "Cheats.hpp"
#include <algorithm>

namespace GameLogic {

    Cheats::Cheats(Game& context)
    : _context(context)
    {

    }

    void Cheats::handle_input(Input& keys)
    {
        if (std::find(keys.keys_down.begin(), keys.keys_down.end(), Key::L) != keys.keys_down.end()) {
            this->_insta_win();
        }

        if (std::find(keys.keys_down.begin(), keys.keys_down.end(), Key::K) != keys.keys_down.end()) {
            this->_substract_health();
        }
    }

    void Cheats::_insta_win()
    {
        this->_context.get_level()->set_level_over();
    }

    void Cheats::_substract_health()
    {
        this->_context.get_level()->get_player().current_health -= this->_health_substraction;
    }
}