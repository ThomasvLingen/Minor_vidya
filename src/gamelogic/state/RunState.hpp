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
#include "../Cheats.hpp"

namespace GameLogic {
    class Game;
}

namespace State {
    using GameLogic::Game;
    using GameLogic::HUD;
    using GameLogic::Cheats;

    class RunState : public IGameState {

    public:
        RunState(Game& context);
        void update(int time_since_last_update) override;

    private:
        bool _is_game_over();
        Engine::FPScounter _fps;
        HUD _hud;
        Cheats _cheats;
    };
}

#endif //MINOR_VIDYA_RUNSTATE_HPP
