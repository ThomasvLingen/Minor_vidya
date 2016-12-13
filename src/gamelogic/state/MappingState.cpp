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
    , _action_is_selected(false)
    {
        MenuOption resume_game {
                {150,100},
                "Resume gaem",
                [] (GameLogic::Game& game) {
                    game.set_new_state(std::make_shared<RunState>(game));
                }
        };

        MenuOption quit_game {
                {150,140},
                "Quit to menutos",
                [] (GameLogic::Game& game) {
                    game.set_new_state(std::make_shared<MenuState>(game));
                }
        };

        this->_menu.add_options({resume_game, quit_game});
        this->_menu.set_escape_option(resume_game);

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

        if (this->_action_is_selected) {
            this->_context.control_mapper.handle_input(keys);
            if (keys.keys_released.size() > 0) {
                this->_context.control_mapper.set_new_combination(this->_selected_action, keys.keys_released.at(0));
                this->_action_is_selected = false;
                this->_menu.clear_options();
                this->_add_menu_options();
            }
        } else {
            this->_collection.handle_input(keys);
        }

        this->_collection.draw();

        this->_context.SDL_facade.render_buffer();
    }

    void MappingState::_set_action(Action action)
    {
        if (!this->_action_is_selected) {
            this->_selected_action = action;
            this->_action_is_selected = true;
        }
    }

    void MappingState::_add_menu_options()
    {
        MenuOption quit_game {
                {150,440},
                "Quit to menu",
                [] (GameLogic::Game& game) {
                    game.set_new_state(std::make_shared<MenuState>(game));
                }
        };

        int x = 150;
        int y = 70;
        const int row_height = 30;
        for (auto action : this->_context.control_mapper.get_editable_actions()) {
            MenuOption action_option = MenuOption(
                    {x,y},
                    this->_context.control_mapper.get_action_description(action)
                    + "   >   "
                    +  this->_context.control_mapper.get_key_description(this->_context.control_mapper.get_key_by_action(action)),
                    [this, action] (Game& game) {
                        UNUSED(game);
                        this->_set_action(action);
                    }
            );
            this->_menu.add_option(action_option);
            y+= row_height;
        }

        this->_menu.add_option(quit_game);
        this->_menu.set_escape_option(quit_game);
    }
}