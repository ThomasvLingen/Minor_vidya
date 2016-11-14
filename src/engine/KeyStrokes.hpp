//
// Created by jazula on 11/14/16.
//

#ifndef MINOR_VIDYA_KEYSTROKES_HPP
#define MINOR_VIDYA_KEYSTROKES_HPP

#include <vector>

namespace Engine {
    using std::vector;

    enum Key {W, A, S, D, ESC};

    typedef std::vector<Key> PressedKeys;
}

#endif //MINOR_VIDYA_KEYSTROKES_HPP