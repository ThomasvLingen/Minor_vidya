//
// Created by sander on 11/17/16.
//

#ifndef MINOR_VIDYA_CREDITSTATE_HPP
#define MINOR_VIDYA_CREDITSTATE_HPP

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
    using Engine::Key;
    using GameLogic::Game;
    using std::string;
    using std::vector;

    class CreditState : public IGameState {

    public:
        CreditState(Game& context);
        void update(int time_since_last_update) override;

    private:
        int _timeSinceLastPress = 0;
        Color _color{255,255,255};
        FontType _font{FontType::alterebro_pixel};
        int _start_pos_x {340};
        int _start_pos_y {50};
        int _step_size_y {30};
        vector<string> _text {
            "Vidya Game is made by:",
            "- Thomas van Lingen:",
            "- Jorg de Bont",
            "- Wouter van Geel",
            "- Sander van Geel",
            "- Martijn Frielink",
            "- Joost van Rijsinge",
            "- Jelmer van der Schoot"
        };

    };
}

#endif //MINOR_VIDYA_CREDITSTATE_HPP
