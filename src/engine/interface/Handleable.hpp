//
// Created by jazula on 11/21/16.
//

#ifndef MINOR_VIDYA_HANDABLE_HPP
#define MINOR_VIDYA_HANDABLE_HPP


#include "../KeyStrokes.hpp"
namespace Engine {
    class Handleable {
    public:
        virtual void handle_input(::Engine::PressedKeys& keys) = 0;
    };
}

#endif //MINOR_VIDYA_HANDABLE_HPP
