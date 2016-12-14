//
// Created by sander on 11/17/16.
//

#ifndef MINOR_VIDYA_RUNSTATE_HPP
#define MINOR_VIDYA_RUNSTATE_HPP

#include "IGameState.hpp"
#include "../Game.hpp"
#include "../../engine/SDLFacade.hpp"
#include "../../engine/FPScounter.hpp"
#include "../HUD.hpp"

namespace GameLogic {
    class Game;
}

namespace State {
    using Engine::Keys;
    using Engine::Key;
    using GameLogic::Game;
    using GameLogic::HUD;

    class RunState : public IGameState {

    public:
        RunState(Game& context);
        void update(int time_since_last_update) override;
        void set_ticks_set_off(int ticks);

    private:
        int _timeSinceLastPress = 0;
        Engine::FPScounter _fps;
        HUD _hud;
    };
}

#endif //MINOR_VIDYA_RUNSTATE_HPP
