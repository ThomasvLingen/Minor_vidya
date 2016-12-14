//
// Created by martijn on 12/13/16.
//

#include "MappingState.hpp"
#include "MenuState.hpp"
#include "RunState.hpp"
#include "../../util/UnusedMacro.hpp"

namespace State {

    MappingState::MappingState(Game& context)
            : IGameState(context)
            , _menu(this->_context.SDL_facade, this->_context)
    {
        _init_key_descriptions();
        _init_action_descriptions();
        _action_is_selected = false;

        this->_add_menu_options();

        this->_collection.add_drawable(&this->_menu);
        this->_collection.add_handleable(&this->_menu);
    }

    void MappingState::update(int time_since_last_update) {
        UNUSED(time_since_last_update)
        this->_context.SDL_facade.clear_screen();

        this->_context.SDL_facade.draw_rect({0,0}, this->_context.SDL_facade.get_width(), this->_context.SDL_facade.get_height(),{0,0,0});

        this->_context.SDL_facade.draw_text("Mapping of controls", FontType::alterebro_pixel_plus, this->_color, {50, 15});

        this->_context.SDL_facade.handle_sdl_events();

        Input keys = this->_context.SDL_facade.get_input();

        if(_action_is_selected){
            this->_context.control_mapper->handle_input(keys);
            if(keys.keys_released.size() > 0) {
                this->_context.control_mapper->set_new_combination(_selected_action, keys.keys_released.at(0));
                _action_is_selected = false;
                this->_menu.clear_options();
                this->_add_menu_options();
            }
        }


        this->_collection.handle_input(keys);
        this->_collection.draw();

        this->_context.SDL_facade.render_buffer();
    }

    void MappingState::_set_action(Action action)
    {
        if(!_action_is_selected){
            _selected_action = action;
            _action_is_selected = true;
        }
    }

    void MappingState::_add_menu_options()
    {
        MenuOption quit_game {
                {150,440},
                "Quit to menu",
                [=] (GameLogic::Game& game) {
                    game.set_new_state(std::make_shared<MenuState>(game));
                }
        };

        int x = 150;
        int y = 70;
        int row_height = 30;
        for(auto action_description_pair : _action_descriptions){
            MenuOption action_option = MenuOption(
                    {x,y},
                    this->_get_action_description(action_description_pair.first)
                    + "   >   "
                    +  this->_get_key_description(this->_context.control_mapper->get_key_by_action(action_description_pair.first)),
                    [=] (Game& game) {
                        UNUSED(game);
                        this->_set_action(action_description_pair.first);
                    }
            );
            this->_menu.add_option(action_option);
            y+= row_height;
        }

        this->_menu.add_options({quit_game});
        this->_menu.set_escape_option(quit_game);
    }

    string MappingState::_get_action_description(Action action)
    {
        return this->_action_descriptions[action];
    }

    string MappingState::_get_key_description(Key key)
    {
        return this->_key_descriptions[key];
    }

    void MappingState::_init_action_descriptions()
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

    void MappingState::_init_key_descriptions()
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
}