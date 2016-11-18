//
// Created by sander on 11/17/16.
//

#ifndef MINOR_VIDYA_IDRAWABLE_HPP
#define MINOR_VIDYA_IDRAWABLE_HPP

#include "SDLFacade.hpp"

namespace Engine {
    class Drawable {

    public:
        Drawable(SDLFacade& _SDL_facade);

        virtual void draw() = 0;     // pure virtual func

    private:
        SDLFacade& _SDL_facade;
    };
}
#endif //MINOR_VIDYA_IDRAWABLE_HPP
