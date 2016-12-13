//
// Created by martijn on 12/13/16.
//

#ifndef MINOR_VIDYA_MAPPINGSTATE_HPP
#define MINOR_VIDYA_MAPPINGSTATE_HPP

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
    using GameLogic::Game;

    class MappingState : public IGameState {

        public:
            MappingState(Game& context);

            void update(int time_since_last_update) override;

        private:
            Menu _menu;
            Color _color{255,255,255};
    };
}

#endif //MINOR_VIDYA_MAPPINGSTATE_HPP
