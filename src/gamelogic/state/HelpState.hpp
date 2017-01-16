//
// Created by sander on 11/18/16.
//

#ifndef MINOR_VIDYA_HELPSTATE_HPP
#define MINOR_VIDYA_HELPSTATE_HPP

#include "IGameState.hpp"
#include "../Game.hpp"
#include "../../engine/SDLFacade.hpp"
#include "../../engine/PathUtil.hpp"
#include <string>
#include <vector>

namespace GameLogic {
    class Game;
}

namespace State {
    using Engine::SDLFacade;
    using Engine::CoordinateDouble;
    using Engine::Color;
    using Engine::FontType;
    using Engine::Keys;
    using Engine::Input;
    using Engine::Key;
    using GameLogic::Game;
    using std::string;
    using std::vector;

    class HelpState : public IGameState {

    public:
        HelpState(Game& context);
        void update(int time_since_last_update) override ;

    private:
        Color _color{255,255,255};
        FontType _font{FontType::alterebro_pixel};
        int _action_start_pos_x {100};
        int _key_start_pos_x {300};
        int _start_pos_y {80};
        int _step_size_y {30};
    };
}

#endif //MINOR_VIDYA_HELPSTATE_HPP
