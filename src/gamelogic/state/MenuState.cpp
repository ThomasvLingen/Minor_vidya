//
// Created by sander on 11/17/16.
//

#include "MenuState.hpp"
#include "StartUpState.hpp"

namespace State {

    MenuState::MenuState()
    {
        auto option_1 = [] (GameLogic::Game& game) {
            // game.set_new_state(std::make_shared<LoadState>());
            std::cout << "Start game" << std::endl;
        };

        auto option_2 = [] (GameLogic::Game& game) {
            // game.set_new_state(std::make_shared<HelpState>());
            std::cout << "Help" << std::endl;
        };

        auto option_3 = [] (GameLogic::Game& game) {
            // game.set_new_state(std::make_shared<CreditState>());
            std::cout << "Credits" << std::endl;
        };

        auto option_4 = [] (GameLogic::Game& game) {
            game.running = false;
        };

        vector<CoordinateDouble> coordinates;
        coordinates.push_back({150,100});
        coordinates.push_back({150,140});
        coordinates.push_back({150,180});
        coordinates.push_back({150,220});

        vector<string> names;
        names.push_back("Start Game");
        names.push_back("Help");
        names.push_back("Credits");
        names.push_back("Quit Game");

        vector<std::function<void(GameLogic::Game&)>> callbacks;
        callbacks.push_back(option_1);
        callbacks.push_back(option_2);
        callbacks.push_back(option_3);
        callbacks.push_back(option_4);

        this->_menu = new Menu(coordinates, names, callbacks);
        this->_menu->set_selected(0);
    }

    MenuState::~MenuState(){
        delete this->_menu;
    }

    void MenuState::update(GameLogic::Game& game, int time_since_last_update) {
        game.SDL_facade.handle_sdl_events();

        PressedKeys keys = game.SDL_facade.get_keys();

        if (this->_timeSinceLastPress <= 20) { //TODO: TO SDL ticks
            this->_timeSinceLastPress++;
        }
        if (this->_timeSinceLastPress > 20) {
            for(auto key : keys){
                switch (key) {
                    case Key::W :
                        this->_menu->set_previous();
                        break;
                    case Key::S :
                        this->_menu->set_next();
                        break;
                    case Key::ESC:
                        game.set_new_state(std::make_shared<StartUpState>());
                        break;
                    case Key::ENTER:
                        _menu->get_selected()->callback(game);
                        break;
                    default:
                        break;
                }
                _timeSinceLastPress = 0;
            }
        }

        game.SDL_facade.clear_screen();
        game.SDL_facade.draw_image("res/menuscreen.bmp", CoordinateDouble{0,0});
        game.SDL_facade.draw_text("Vidya Gaem", FontType::alterebro_pixel, this->_color, CoordinateDouble{20,20});

        for (auto option : _menu->menu_options) {
            game.SDL_facade.draw_text(option->name, FontType::alterebro_pixel, this->_color, option->coordinates);
        }

        game.SDL_facade.draw_rect(CoordinateDouble{120, this->_menu->get_selected()->coordinates.y + 6}, 15, 15, _color);

        game.SDL_facade.render_buffer();
    }
}