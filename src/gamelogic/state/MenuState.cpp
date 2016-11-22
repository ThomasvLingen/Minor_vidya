//
// Created by sander on 11/17/16.
//

#include "MenuState.hpp"
#include "StartUpState.hpp"
#include "LoadState.hpp"
#include "HelpState.hpp"
#include "CreditState.hpp"

namespace State {

    MenuState::MenuState(Game& context)
    : IGameState(context)
    , _menu(this->_context.SDL_facade, this->_context)
    {
        MenuOption start_game {
            {150,100}, //coordinates
            "Start Game", //text
            [] (Game& game) { //callback
                 game.set_new_state(std::make_shared<LoadState>(game));
            }
        };

        MenuOption help {
            {150,140}, //coordinates
            "Help", //text
            [] (Game& game) { //callback
                 game.set_new_state(std::make_shared<HelpState>(game));
            }
        };

        MenuOption credits{
            {150,180}, //coordinates
            "Credits", //text
            [] (Game& game) { //callback
                 game.set_new_state(std::make_shared<CreditState>(game));
            }
        };

        MenuOption quit {
            {150,220}, //coordinates
            "Quit Game", //text
            [] (Game& game) { //callback
                game.running = false;
            }
        };

        this->_menu.add_options( //add options to menu
            {start_game, help, credits, quit}
        );

        this->_menu.set_selected(0);
        this->_menu.set_escape_option(quit);
        this->_collection.add_drawable(&this->_menu);
        this->_collection.add_handleable(&this->_menu);
    }

    void MenuState::update(int time_since_last_update) {
        this->_context.SDL_facade.clear_screen();

        this->_context.SDL_facade.draw_image(
            "res/menuscreen.bmp",
            CoordinateDouble{0,0}
        );

        this->_context.SDL_facade.draw_text(
            "Vidya Gaem",
            FontType::alterebro_pixel,
            this->_color,
            {20,20}
        );

        this->_context.SDL_facade.handle_sdl_events();
        PressedKeys keys = this->_context.SDL_facade.get_keys();
        this->_collection.handle_input(keys);
        this->_collection.draw();

        this->_context.SDL_facade.render_buffer();
    }
}