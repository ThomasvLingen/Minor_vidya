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
        for (auto const& action_key_pair : this->_mapping_info)
        {
            if (std::find(input.keys_down.begin(), input.keys_down.end(), action_key_pair.second) != input.keys_down.end()) {
                //action key found in keys_down
                this->_input_actions.actions_on.push_back(action_key_pair.first);
                //input_actions.actions_on.push_back(action_key_pair.first);
            }

            if (std::find(input.keys_released.begin(), input.keys_released.end(), action_key_pair.second) != input.keys_released.end()) {
                //action key found in keys_released
                //input_actions.actions_off.push_back(action_key_pair.first);
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
        this->_mapping_info[Action::MENU_UP] = Key::ARROW_UP;
        this->_mapping_info[Action::MENU_DOWN] = Key::ARROW_DOWN;
        this->_mapping_info[Action::MENU_BACK] = Key::ESC;
        this->_mapping_info[Action::MENU_SELECT] = Key::ENTER;
        this->_mapping_info[Action::ACTION_INTERACT] = Key::E;
        //this->_mapping_info[Action::ACTION_USE] = Key::SPACE;
        this->_mapping_info[Action::MOVE_BACKWARD] = Key::ARROW_DOWN;
        this->_mapping_info[Action::MOVE_FORWARD] = Key::ARROW_UP;
        this->_mapping_info[Action::MOVE_LEFT] = Key::A;
        this->_mapping_info[Action::MOVE_RIGHT] = Key::D;
        this->_mapping_info[Action::ROTATE_LEFT] = Key::ARROW_LEFT;
        this->_mapping_info[Action::ROTATE_RIGHT] = Key::ARROW_RIGHT;
        this->_mapping_info[Action::PAUSE_GAME] = Key::ESC;
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
        this->_action_descriptions[Action::ACTION_INTERACT] = "Interact";
        this->_action_descriptions[Action::MOVE_BACKWARD] = "Move backward";
        this->_action_descriptions[Action::MOVE_FORWARD] = "Move forward";
        this->_action_descriptions[Action::MOVE_LEFT] = "Move left";
        this->_action_descriptions[Action::MOVE_RIGHT] = "Move right";
        this->_action_descriptions[Action::ROTATE_LEFT] = "Rotate left";
        this->_action_descriptions[Action::ROTATE_RIGHT] = "Rotate right";
        this->_action_descriptions[Action::PAUSE_GAME] = "Pause game";
    }

    void ControlMapper::_init_key_descriptions()
    {
        this->_key_descriptions[Key::A] = "A";
        this->_key_descriptions[Key::B] = "B";
        this->_key_descriptions[Key::C] = "C";
        this->_key_descriptions[Key::D] = "D";
        this->_key_descriptions[Key::E] = "E";
        this->_key_descriptions[Key::F] = "F";
        this->_key_descriptions[Key::G] = "G";
        this->_key_descriptions[Key::H] = "H";
        this->_key_descriptions[Key::I] = "I";
        this->_key_descriptions[Key::J] = "J";
        this->_key_descriptions[Key::K] = "K";
        this->_key_descriptions[Key::L] = "L";
        this->_key_descriptions[Key::M] = "M";
        this->_key_descriptions[Key::N] = "N";
        this->_key_descriptions[Key::O] = "O";
        this->_key_descriptions[Key::P] = "P";
        this->_key_descriptions[Key::Q] = "Q";
        this->_key_descriptions[Key::R] = "R";
        this->_key_descriptions[Key::S] = "S";
        this->_key_descriptions[Key::T] = "T";
        this->_key_descriptions[Key::U] = "U";
        this->_key_descriptions[Key::V] = "V";
        this->_key_descriptions[Key::W] = "W";
        this->_key_descriptions[Key::X] = "X";
        this->_key_descriptions[Key::Y] = "Y";
        this->_key_descriptions[Key::Z] = "Z";
        this->_key_descriptions[Key::NUMBER_1] = "1";
        this->_key_descriptions[Key::NUMBER_2] = "2";
        this->_key_descriptions[Key::NUMBER_3] = "3";
        this->_key_descriptions[Key::NUMBER_4] = "4";
        this->_key_descriptions[Key::NUMBER_5] = "5";
        this->_key_descriptions[Key::NUMBER_6] = "6";
        this->_key_descriptions[Key::NUMBER_7] = "7";
        this->_key_descriptions[Key::NUMBER_8] = "8";
        this->_key_descriptions[Key::NUMBER_9] = "9";
        this->_key_descriptions[Key::NUMBER_0] = "0";
        this->_key_descriptions[Key::ESC] = "Esc";
        this->_key_descriptions[Key::SPACE] = "Space";
        this->_key_descriptions[Key::ENTER] = "Enter";
        this->_key_descriptions[Key::ARROW_UP] = "Arrow up";
        this->_key_descriptions[Key::ARROW_DOWN] = "Arrow down";
        this->_key_descriptions[Key::ARROW_LEFT] = "Arrow left";
        this->_key_descriptions[Key::ARROW_RIGHT] = "Arrow right";
    }

    map<Key, string>& ControlMapper::get_key_descriptions()
    {
        return this->_key_descriptions;
    }

    map<Action, string>& ControlMapper::get_action_descriptions()
    {
        return this->_action_descriptions;
    }
}