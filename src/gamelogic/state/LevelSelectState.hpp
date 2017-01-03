//
// Created by mafn on 1/3/17.
//

#ifndef MINOR_VIDYA_LEVELSELECTSTATE_HPP
#define MINOR_VIDYA_LEVELSELECTSTATE_HPP

#include "IGameState.hpp"
#include "Menu.hpp"

namespace State {
    class LevelSelectState : public IGameState {
    public:
        LevelSelectState(Game& context);

        virtual void update(int time_since_last_update) override;
    private:

        Engine::Collection _collection;
        Menu _menu;

        Color _title_text_color {255,255,255};

        void _init_menu();
    };
}


#endif //MINOR_VIDYA_LEVELSELECTSTATE_HPP
