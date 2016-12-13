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
        MenuOption resume_game {
                {150,100},
                "Resume gaem",
                [] (GameLogic::Game& game) {
                    //game.set_new_state(std::make_shared<RunState>(game));
                }
        };

        MenuOption quit_game {
                {150,140},
                "Quit to menutos",
                [] (GameLogic::Game& game) {
                    //game.set_new_state(std::make_shared<MenuState>(game));
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

        this->_collection.handle_input(keys);
        this->_collection.draw();

        this->_context.SDL_facade.render_buffer();
    }
}