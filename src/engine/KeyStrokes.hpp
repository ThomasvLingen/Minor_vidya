//
// Created by jazula on 11/14/16.
//

#ifndef MINOR_VIDYA_KEYSTROKES_HPP
#define MINOR_VIDYA_KEYSTROKES_HPP

#include <vector>

namespace Engine {
    using std::vector;

    enum class Key {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, ZERO, ONE, TWO, THREE, FOUR,
            FIVE, SIX, SEVEN, EIGHT, NINE, ESC, ENTER, UP, DOWN, LEFT, RIGHT};

    typedef vector<Key> Keys;

    struct Input {
        Keys keys_down;
        Keys keys_released;
    };
}

#endif //MINOR_VIDYA_KEYSTROKES_HPP
