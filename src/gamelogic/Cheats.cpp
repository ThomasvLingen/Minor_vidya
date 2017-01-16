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
    }

    void Cheats::_insta_win()
    {
        this->_context.get_level()->set_level_over();
    }
}