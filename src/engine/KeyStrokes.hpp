//
// Created by jazula on 11/14/16.
//

#ifndef MINOR_VIDYA_KEYSTROKES_HPP
#define MINOR_VIDYA_KEYSTROKES_HPP

#include <vector>
#include <string>

namespace Engine {
    using std::vector;
    using std::string;

    enum class Key {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        ARROW_UP, ARROW_DOWN, ARROW_LEFT, ARROW_RIGHT, SPACE, ESC, ENTER, TAB,
        NUMBER_1, NUMBER_2, NUMBER_3, NUMBER_4, NUMBER_5, NUMBER_6, NUMBER_7, NUMBER_8, NUMBER_9, NUMBER_0};

    typedef vector<Key> Keys;

    struct Input {
        Keys keys_down;
        Keys keys_released;
    };
}

#endif //MINOR_VIDYA_KEYSTROKES_HPP
