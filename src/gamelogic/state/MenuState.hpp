//
// Created by sander on 11/17/16.
//

#ifndef MINOR_VIDYA_MENUSTATE_HPP
#define MINOR_VIDYA_MENUSTATE_HPP

#include "IGameState.hpp"
#include "../Game.hpp"
#include "../../engine/SDLFacade.hpp"
#include "Menu.hpp"

namespace GameLogic {
    class Game;
}

namespace State {
    using Engine::SDLFacade;
    using Engine::CoordinateDouble;
    using Engine::Color;
    using Engine::FontType;
    using Engine::Keys;
    using Engine::Key;
    using std::vector;
    using std::string;

    class MenuState : public IGameState {

    public:
        MenuState(Game& context);

        void update(int time_since_last_update) override;

    private:
        Menu _menu;
        Color _color{255,255,255};

    };
}

#endif //MINOR_VIDYA_MENUSTATE_HPP
