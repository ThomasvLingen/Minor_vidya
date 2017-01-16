//
// Created by sander on 1/16/17.
//

#ifndef MINOR_VIDYA_HIGHSCORESTATE_HPP
#define MINOR_VIDYA_HIGHSCORESTATE_HPP

#include "IGameState.hpp"
#include "IGameState.hpp"
#include "../Game.hpp"
#include "../../engine/SDLFacade.hpp"
#include "../../engine/PathUtil.hpp"
#include "MenuState.hpp"

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
    using GameLogic::Game;
    using std::string;
    using std::vector;
    using std::to_string;

    class HighscoreState : public IGameState {

    public:
        HighscoreState(Game& context);
        void update(int time_since_last_update) override;

    private:
        Color _color{255,255,255};
        FontType _font{FontType::alterebro_pixel};
        int _start_pos_x_names {150};
        int _start_pos_x_scores {300};
        int _start_pos_y {100};
        int _step_size_y {30};

    };
}

#endif //MINOR_VIDYA_HIGHSCORESTATE_HPP
