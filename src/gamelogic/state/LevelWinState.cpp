//
// Created by waseland on 12/7/16.
//

#include "LevelWinState.hpp"
#include "MenuState.hpp"
#include "RunState.hpp"
#include "../../util/UnusedMacro.hpp"

namespace State {

    LevelWinState::LevelWinState(Game& context)
    : IGameState(context)
    , _menu(this->_context.SDL_facade, this->_context)
    {
        MenuOption continue_game {
                {250,100},
                "Continue to next level",
                [] (GameLogic::Game& game) {
                    game.set_new_state(std::make_shared<RunState>(game)); //TODO: load next level
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

    void LevelWinState::update(int time_since_last_update) {
        UNUSED(time_since_last_update);
        this->_context.SDL_facade.clear_screen();

        this->_context.SDL_facade.draw_image(VIDYA_RUNPATH + "res/levelwin.bmp" , {0,0});
        this->_context.SDL_facade.draw_text("Completed level + [Level Name]", FontType::alterebro_pixel_medium, this->_color, {225, 15});

        this->_context.SDL_facade.draw_text("Time : [00:00]", FontType::alterebro_pixel_medium, this->_color, {225, 200}); //TODO: change this to real time

        this->_context.SDL_facade.handle_sdl_events();

        Input keys = this->_context.SDL_facade.get_input();

        this->_collection.handle_input(keys);
        this->_collection.draw();

        this->_context.SDL_facade.render_buffer();
    }
}