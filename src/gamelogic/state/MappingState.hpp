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
    using std::map;
    using std::string;
    using GameLogic::Game;

    class MappingState : public IGameState {

        public:
            MappingState(Game& context);

            void update(int time_since_last_update) override;


        private:
            Menu _menu;
            Color _color{255,255,255};
            Action _selected_action;
            bool _action_is_selected;
            void _set_action(Action action);

            void _init_key_descriptions();
            void _init_action_descriptions();
            void _add_menu_options();

            map<Key, string> _key_descriptions;
            string _get_key_description(Key key);

            map<Action, string> _action_descriptions;
            string _get_action_description(Action action);
    };
}

#endif //MINOR_VIDYA_MAPPINGSTATE_HPP
