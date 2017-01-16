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
#include <iostream>
#include <fstream>

using std::ofstream;
using std::ifstream;

namespace GameLogic {
    class Game;
}

struct highscore {
    int score;
    std::string name;
};

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
    using std::map;
    using std::stoi;
    using std::to_string;

    class HighscoreState : public IGameState {

    public:
        HighscoreState(Game& context);
        void update(int time_since_last_update) override;
        void add_score(int time, string name);

    private:
        Color _color{255,255,255};
        FontType _font{FontType::alterebro_pixel};
        int _start_pos_x_names {200};
        int _start_pos_x_scores {400};
        int _start_pos_y {50};
        int _step_size_y {30};
        vector<highscore> _scores;

        void _read_from_file();
        void _write_to_file();
        void _sort_list();
    };
}

#endif //MINOR_VIDYA_HIGHSCORESTATE_HPP
