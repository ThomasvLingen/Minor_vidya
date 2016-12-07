//
// Created by waseland on 12/7/16.
//

#include "LevelWinState.hpp"
#include "MenuState.hpp"
#include "RunState.hpp"

namespace State {

    LevelWinState::LevelWinState(Game& context)
            : IGameState(context)
            , _menu(this->_context.SDL_facade, this->_context)
    {
        MenuOption resume_game {
                {150,100},
                "Resume game",
                [] (GameLogic::Game& game) {
                    game.set_new_state(std::make_shared<RunState>(game));
                }
        };

        MenuOption quit_game {
                {150,140},
                "Quit to menu",
                [] (GameLogic::Game& game) {
                    game.set_new_state(std::make_shared<MenuState>(game));
                }
        };

        this->_menu.add_options({resume_game, quit_game});
        this->_menu.set_escape_option(resume_game);

        this->_collection.add_drawable(&this->_menu);
        this->_collection.add_handleable(&this->_menu);
    }

    void LevelWinState::update(int time_since_last_update) {
        // foo
        this->_context.SDL_facade.clear_screen();

        this->_context.SDL_facade.draw_text("Completed level + [Level Name]", FontType::alterebro_pixel_plus, this->_color, {50, 15});

        this->_context.SDL_facade.handle_sdl_events();

        PressedKeys keys = this->_context.SDL_facade.get_keys();

        this->_collection.handle_input(keys);
        this->_collection.draw();

        this->_context.SDL_facade.render_buffer();
    }
}