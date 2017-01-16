//
// Created by waseland on 12/7/16.
//

#ifndef MINOR_VIDYA_LEVELWINSTATE_HPP
#define MINOR_VIDYA_LEVELWINSTATE_HPP

#include "IGameState.hpp"
#include "../Game.hpp"
#include "../../engine/SDLFacade.hpp"
#include "Menu.hpp"

namespace GameLogic {
    class Game;
    class CampaignMap;
}

namespace State {
    using std::string;
    using Engine::SDLFacade;
    using Engine::CoordinateDouble;
    using Engine::Color;
    using Engine::FontType;
    using Engine::Keys;
    using Engine::Key;
    using GameLogic::Game;
    using GameLogic::CampaignMap;

    class LevelWinState : public IGameState {

    public:
        LevelWinState(Game& context);

        void update(int time_since_last_update) override;

    private:
        Menu _menu;
        Color _color{255,255,255};

        CampaignMap* _completed_map;
        bool _could_get_map = false;
        string _level_completed_text;
        string _level_time_text;
    };
}


#endif //MINOR_VIDYA_LEVELWINSTATE_HPP
