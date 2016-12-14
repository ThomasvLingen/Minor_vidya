//
// Created by wouter on 12/13/16.
//

#ifndef MINOR_VIDYA_CONTROLMAPPER_H
#define MINOR_VIDYA_CONTROLMAPPER_H

#include "../engine/SDLFacade.hpp"
#include "../engine/KeyStrokes.hpp"
#include <map>
#include <vector>

namespace GameLogic {
    using Engine::SDLFacade;
    using std::vector;
    using std::map;
    using Engine::Key;
    using Engine::Input;
    using std::string;

    enum class Action {
        MOVE_FORWARD, MOVE_BACKWARD, MOVE_LEFT, MOVE_RIGHT, ROTATE_LEFT, ROTATE_RIGHT, ACTION_INTERACT, ACTION_USE, MENU_UP, MENU_DOWN, MENU_SELECT, MENU_BACK, PAUSE_GAME
    };

    typedef vector<Action> Actions;

    struct InputActions {
        Actions actions_on;     //keys_down
        Actions actions_off;    //keys_released
    };

    class ControlMapper {
    public:
        ControlMapper();

        virtual ~ControlMapper();

        InputActions* get_input_actions();
        void handle_input(Input input);

        void set_new_combination(Action action, Key key);

        Key get_key_by_action(Action action);

        string get_key_description(Key key);
        string get_action_description(Action action);

        map<Key, string>& get_key_descriptions();
        map<Action, string>& get_action_descriptions();

    private:
        map<Action, Key> _mapping_info;
        InputActions* _input_actions;
        map<Key, string> _key_descriptions;
        map<Action, string> _action_descriptions;

        void _init_mapping_info();
        void _init_key_descriptions();
        void _init_action_descriptions();
    };
}

#endif //MINOR_VIDYA_CONTROLMAPPER_H
