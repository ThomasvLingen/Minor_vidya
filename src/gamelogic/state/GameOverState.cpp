//
// Created by jazula on 1/16/17.
//

#include "GameOverState.hpp"
#include "../../util/UnusedMacro.hpp"
#include "MenuState.hpp"
#include "RunState.hpp"
#include "LoadState.hpp"

namespace State {

    GameOverState::GameOverState(Game& context)
    : IGameState(context)
    , _menu(this->_context.SDL_facade, this->_context)
    {
        MenuOption continue_game {
            {250,100},
            "Restart",
            [] (GameLogic::Game& game) {
                game.set_new_state(std::make_shared<LoadState>(game));
            }
        };

        MenuOption quit_game {
            {250,140},
            "Quit to menu",
            [] (GameLogic::Game& game) {
                game.set_new_state(std::make_shared<MenuState>(game));
            }
        };

        this->_menu.add_options({continue_game, quit_game});
        this->_menu.set_escape_option(quit_game);

        this->_collection.add_drawable(&this->_menu);
        this->_collection.add_handleable(&this->_menu);
    }

    void GameOverState::update(int time_since_last_update)
    {
        UNUSED(time_since_last_update);
        this->_context.SDL_facade.clear_screen();


        this->_context.SDL_facade.draw_image("res/gameover.bmp" , {0,0});
        this->_context.SDL_facade.draw_text("Gaem Over", FontType::alterebro_pixel_medium, this->_color, {225, 15});

        this->_context.SDL_facade.handle_sdl_events();

        Input keys = this->_context.SDL_facade.get_input();

        this->_collection.handle_input(keys);
        this->_collection.draw();

        this->_context.SDL_facade.render_buffer();
    }

}