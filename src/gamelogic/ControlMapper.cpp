//
// Created by wouter on 12/13/16.
//

#include "ControlMapper.hpp"

namespace GameLogic{

    ControlMapper::ControlMapper()
    : _input_actions(new InputActions())
    {
        this->_init_mapping_info();
    }

    ControlMapper::~ControlMapper()
    {
        delete this->_input_actions;
    }

    void ControlMapper::handle_input(Input input)
    {
        delete this->_input_actions;
        this->_input_actions = new InputActions();
        for (auto const& action_key_pair : _mapping_info)
        {
            if(std::find(input.keys_down.begin(), input.keys_down.end(), action_key_pair.second) != input.keys_down.end()) {
                //action key found in keys_down
                this->_input_actions->actions_on.push_back(action_key_pair.first);
                //input_actions.actions_on.push_back(action_key_pair.first);
            }

            if(std::find(input.keys_released.begin(), input.keys_released.end(), action_key_pair.second) != input.keys_released.end()) {
                //action key found in keys_released
                //input_actions.actions_off.push_back(action_key_pair.first);
                this->_input_actions->actions_off.push_back(action_key_pair.first);
            }
        }
    }

    InputActions* ControlMapper::get_input_actions()
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
        return _mapping_info[action];
    }

    void ControlMapper::set_new_combination(Action action, Key key)
    {
        this->_mapping_info[action] = key;
    }
}