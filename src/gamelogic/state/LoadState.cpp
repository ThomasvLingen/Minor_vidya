//
// Created by sander on 11/17/16.
//

#include "LoadState.hpp"
#include "RunState.hpp"
#include "MenuState.hpp"
#include "../../util/UnusedMacro.hpp"

namespace State {

    LoadState::LoadState(Game& context, CampaignMap& map)
    : IGameState(context)
    , map_to_load(map)
    {

    }
    
    void LoadState::update(int time_since_last_update) {
        UNUSED(time_since_last_update)
        this->_context.SDL_facade.handle_sdl_events();

        this->_context.SDL_facade.clear_screen();
        this->_context.SDL_facade.draw_rect({0,0}, 640, 480, Color{0,0,0});

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
            this->_text_image[this->_current_index].second,
            this->_loading_bar_pos
        );

        this->_context.SDL_facade.draw_text(
            this->map_to_load.name,
            this->_text_font,
            this->_color,
            {30,15}
        );

        int advertisement_x = this->_advertisement_pos.x - this->_context.SDL_facade.get_image_width(Config::LOAD_AD_PATH) / 2;
        this->_context.SDL_facade.draw_image(
            Config::LOAD_AD_PATH,
            CoordinateInt {
                advertisement_x,
                this->_advertisement_pos.y
            }
        );

        this->_context.SDL_facade.render_buffer();

        this->_loading_screen_time = this->_loading_screen_time + 2; //TODO: To ticks
        if (this->_loading_screen_time > this->_wait_time) {
            this->_loading_screen_time = 0;
            this->_current_index++;
        }

        if (this->_current_index >= (int)this->_text_image.size()) {
            if ( this->_context.load_Level(this->map_to_load.tmx_source_path) ) {
                this->_context.set_current_map(&this->map_to_load);
                this->_context.set_new_state( std::make_shared<RunState>( this->_context ) );
            }
            else {
                //TODO: notify user of failed map load.
                this->_context.set_new_state( std::make_shared<MenuState>( this->_context ) );
            }
        }
    }
}