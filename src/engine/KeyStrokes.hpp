//
// Created by jazula on 11/14/16.
//

#ifndef MINOR_VIDYA_KEYSTROKES_HPP
#define MINOR_VIDYA_KEYSTROKES_HPP

#include <vector>

namespace Engine {
    using std::vector;

    enum class Key {W, A, S, D, E, Q, ESC, ENTER, UP, DOWN, LEFT, RIGHT};

    typedef vector<Key> Keys;

    struct Input {
        Keys keys_down;
        Keys keys_released;
    };
}

#endif //MINOR_VIDYA_KEYSTROKES_HPP
