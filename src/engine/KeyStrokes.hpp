//
// Created by jazula on 11/14/16.
//

#ifndef MINOR_VIDYA_KEYSTROKES_HPP
#define MINOR_VIDYA_KEYSTROKES_HPP

#include <vector>

namespace Engine {
    using std::vector;

    enum class Key {MOVE_FORWARD, MOVE_BACKWARDS, MOVE_RIGHT, MOVE_LEFT, ROTATE_LEFT, ROTATE_RIGHT, MENU_ENTER, MENU_UP,
            MENU_DOWN, PAUSE_GAME, ACTION_INTERACT};

    typedef vector<Key> Keys;

    struct Input {
        Keys keys_down;
        Keys keys_released;
    };
}

#endif //MINOR_VIDYA_KEYSTROKES_HPP
