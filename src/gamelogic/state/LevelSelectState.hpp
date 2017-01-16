//
// Created by mafn on 1/3/17.
//

#ifndef MINOR_VIDYA_LEVELSELECTSTATE_HPP
#define MINOR_VIDYA_LEVELSELECTSTATE_HPP

#include <functional>

#include "IGameState.hpp"
#include "Menu.hpp"

namespace State {
    using GameLogic::CampaignMap;

    class LevelSelectState : public IGameState {
    public:
        LevelSelectState(Game& context);

        virtual void update(int time_since_last_update) override;
    private:

        Engine::Collection _collection;
        Menu _menu;

        Color _title_text_color {0xFF,0xFF,0xFF};
        Color _unlocked_color {0xFF, 0xFF, 0xFF};
        Color _locked_color {0xFF, 0, 0};

        Color _get_map_option_color(CampaignMap& map);
        std::function<void(GameLogic::Game&)> _get_map_option_callback(CampaignMap& map);

        void _init_menu();
    };
}


#endif //MINOR_VIDYA_LEVELSELECTSTATE_HPP
