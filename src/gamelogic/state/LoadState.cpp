//
// Created by sander on 11/17/16.
//

#include "LoadState.hpp"
#include "RunState.hpp"
#include "MenuState.hpp"
#include "../../util/UnusedMacro.hpp"

namespace State {

    LoadState::LoadState(Game& context)
    : IGameState(context)
    {

    }
    
    void LoadState::update(int time_since_last_update) {
        UNUSED(time_since_last_update)
        this->_context.SDL_facade.handle_sdl_events();

        this->_context.SDL_facade.clear_screen();
        this->_context.SDL_facade.draw_rect({0,0}, 640, 480, Color{0,0,0});

        this->_loading_screen_time = this->_loading_screen_time + 2; //TODO: To ticks
        if (this->_loading_screen_time > this->_wait_time) {
            this->_loading_screen_time = 0;
            this->_current_index++;
        }

        this->_context.SDL_facade.draw_text(
            this->_load_text,
            this->_load_font,
            this->_color,
            this->_load_text_pos
        );
        this->_context.SDL_facade.draw_text(
            this->_text_image[this->_current_index].first,
            this->_text_font,
            this->_color,
            this->_text_pos
        );
        this->_context.SDL_facade.draw_image(
            VIDYA_RUNPATH + this->_text_image[this->_current_index].second,
            this->_loading_bar_pos
        );

        this->_context.SDL_facade.draw_text(
            "Level Name Here",
            this->_text_font,
            this->_color,
            {500,15}
        );

        this->_context.SDL_facade.render_buffer();

        if (this->_current_index >= 9) {
            if ( this->_context.load_Level(VIDYA_RUNPATH + "res/TestMap.tmx") ) { //TODO needs to come from a level selecter or campaign level loading or something
                this->_context.set_new_state( std::make_shared<RunState>( this->_context ) );
            }
            else {
                //TODO: notify user of failed map load.
                this->_context.set_new_state( std::make_shared<MenuState>( this->_context ) );
            }
        }
    }
}