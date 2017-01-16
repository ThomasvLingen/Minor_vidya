//
// Created by wouter on 12/13/16.
//

#include "ControlMapper.hpp"

namespace GameLogic{

    ControlMapper::ControlMapper()
    {
        this->_init_mapping_info();
        this->_init_key_descriptions();
        this->_init_action_descriptions();
    }

    ControlMapper::~ControlMapper()
    {

    }

    void ControlMapper::handle_input(Input input)
    {
        this->_input_actions.actions_off.clear();
        this->_input_actions.actions_on.clear();
        for (auto const& action_key_pair : this->_mapping_info) {
            if (std::find(input.keys_down.begin(), input.keys_down.end(), action_key_pair.second) != input.keys_down.end()) {
                //action key found in keys_down
                this->_input_actions.actions_on.push_back(action_key_pair.first);
            }

            if (std::find(input.keys_released.begin(), input.keys_released.end(), action_key_pair.second) != input.keys_released.end()) {
                //action key found in keys_released
                this->_input_actions.actions_off.push_back(action_key_pair.first);
            }
        }
    }

    InputActions& ControlMapper::get_input_actions()
    {
        return this->_input_actions;
    }

    void ControlMapper::_init_mapping_info()
    {
        this->_mapping_info = {
            {Action::MENU_UP, Key::ARROW_UP},
            {Action::MENU_DOWN, Key::ARROW_DOWN},
            {Action::MENU_BACK, Key::ESC},
            {Action::MENU_SELECT,Key::ENTER},
            {Action::ACTION_INTERACT, Key::E},
            {Action::MOVE_BACKWARD, Key::ARROW_DOWN},
            {Action::MOVE_FORWARD, Key::ARROW_UP},
            {Action::MOVE_LEFT, Key::A},
            {Action::MOVE_RIGHT, Key::D},
            {Action::ROTATE_LEFT, Key::ARROW_LEFT},
            {Action::ROTATE_RIGHT, Key::ARROW_RIGHT},
            {Action::PAUSE_GAME, Key::ESC},
            {Action::ACTION_HURT, Key::K}
        };

        this->_editable_actions = {
            {Action::ACTION_INTERACT},
            {Action::MOVE_BACKWARD},
            {Action::MOVE_FORWARD},
            {Action::MOVE_LEFT},
            {Action::MOVE_RIGHT},
            {Action::ROTATE_LEFT},
            {Action::ROTATE_RIGHT},
            {Action::PAUSE_GAME},
            {Action::ACTION_HURT}
        };
    }

    Key ControlMapper::get_key_by_action(Action action)
    {
        return this->_mapping_info[action];
    }

    void ControlMapper::set_new_combination(Action action, Key key)
    {
        this->_mapping_info[action] = key;
    }

    string ControlMapper::get_action_description(Action action)
    {
        return this->_action_descriptions[action];
    }

    string ControlMapper::get_key_description(Key key)
    {
        return this->_key_descriptions[key];
    }

    void ControlMapper::_init_action_descriptions()
    {
        this->_action_descriptions = {
            {Action::ACTION_INTERACT, "Interact"},
            {Action::MOVE_BACKWARD, "Move backward"},
            {Action::MOVE_FORWARD, "Move forward"},
            {Action::MOVE_LEFT, "Move left"},
            {Action::MOVE_RIGHT, "Move right"},
            {Action::ROTATE_LEFT, "Rotate left"},
            {Action::ROTATE_RIGHT, "Rotate right"},
            {Action::PAUSE_GAME, "Pause game"},
            {Action::ACTION_USE, "Use item"},
            {Action::MENU_BACK, "Go back in menu"},
            {Action::MENU_SELECT, "Select menu option"},
            {Action::MENU_UP, "Go up in menu"},
            {Action::MENU_DOWN, "Go down in menu"},
            {Action::ACTION_HURT, "Hurt yourself"}
        };
    }

    void ControlMapper::_init_key_descriptions()
    {
        this->_key_descriptions = {
            {Key::A, "A"},
            {Key::B, "B"},
            {Key::C, "C"},
            {Key::D, "D"},
            {Key::E, "E"},
            {Key::F, "F"},
            {Key::G, "G"},
            {Key::H, "H"},
            {Key::I, "I"},
            {Key::J, "J"},
            {Key::K, "K"},
            {Key::L, "L"},
            {Key::M, "M"},
            {Key::N, "N"},
            {Key::O, "O"},
            {Key::P, "P"},
            {Key::Q, "Q"},
            {Key::R, "R"},
            {Key::S, "S"},
            {Key::T, "T"},
            {Key::U, "U"},
            {Key::V, "V"},
            {Key::W, "W"},
            {Key::X, "X"},
            {Key::Y, "Y"},
            {Key::Z, "Z"},
            {Key::NUMBER_1, "1"},
            {Key::NUMBER_2, "2"},
            {Key::NUMBER_3, "3"},
            {Key::NUMBER_4, "4"},
            {Key::NUMBER_5, "5"},
            {Key::NUMBER_6, "6"},
            {Key::NUMBER_7, "7"},
            {Key::NUMBER_8, "8"},
            {Key::NUMBER_9, "9"},
            {Key::NUMBER_0, "0"},
            {Key::ESC, "Esc"},
            {Key::SPACE, "Space"},
            {Key::ENTER, "Enter"},
            {Key::ARROW_UP, "Arrow up"},
            {Key::ARROW_DOWN, "Arrow down"},
            {Key::ARROW_LEFT, "Arrow left"},
            {Key::ARROW_RIGHT, "Arrow right"}
        };
    }

    vector<Action>& ControlMapper::get_editable_actions()
    {
        return this->_editable_actions;
    }

    map<Action, Key>& ControlMapper::get_all_actions()
    {
        return this->_mapping_info;
    }
}