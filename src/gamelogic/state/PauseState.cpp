//
// Created by sander on 11/17/16.
//

#include "PauseState.hpp"
#include "MenuState.hpp"
#include "RunState.hpp"

namespace State {

    PauseState::PauseState(Game& context)
    : IGameState(context)
    {
        auto option_1 = [] (GameLogic::Game& game) {
             game.set_new_state(std::make_shared<RunState>(game));
        };

        auto option_2 = [] (GameLogic::Game& game) {
            game.set_new_state(std::make_shared<MenuState>(game));
        };

        vector<CoordinateDouble> coordinates;
        coordinates.push_back({150,100});
        coordinates.push_back({150,140});

        vector<string> names;
        names.push_back("Resume game");
        names.push_back("Quit to menu");

        vector<std::function<void(GameLogic::Game&)>> callbacks;
        callbacks.push_back(option_1);
        callbacks.push_back(option_2);

        this->_menu = new Menu(coordinates, names, callbacks);
        this->_menu->set_selected(0);
    }

    PauseState::~PauseState()
    {
        delete this->_menu;
    }

    void PauseState::update(int time_since_last_update) {
        this->_context.SDL_facade.handle_sdl_events();
        if(this->_timeSinceLastPress <= 15){ //TODO: TO SDL ticks
            this->_timeSinceLastPress++;
        }
        if(this->_timeSinceLastPress >= 15) {
            PressedKeys keys = this->_context.SDL_facade.get_keys();
            for (auto key : keys) {
                switch (key) {
                    case Key::W:
                        this->_menu->set_previous();
                        break;
                    case Key::S:
                        this->_menu->set_next();
                        break;
                    case Key::ESC:
                        // this->_context.set_new_state(std::make_shared<RunState>());
                        this->_timeSinceLastPress = 0;
                        break;
                    case Key::ENTER:
                        this->_menu->get_selected()->callback(this->_context);
                        break;
                    default:
                        break;
                }
            }
        }
        this->_context.SDL_facade.clear_screen();
        this->_context.SDL_facade.draw_text("Game Paused", FontType::alterebro_pixel_plus, this->_color, CoordinateDouble{50, 15});
        for(auto option : _menu->menu_options){
            this->_context.SDL_facade.draw_text(option->name, FontType::alterebro_pixel, this->_color, option->coordinates);
        };
        this->_context.SDL_facade.draw_rect(CoordinateDouble{120,this->_menu->get_selected()->coordinates.y + 6}, 15, 15, _color);

        this->_context.SDL_facade.render_buffer();
    }
}