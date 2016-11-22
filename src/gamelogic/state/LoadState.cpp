//
// Created by sander on 11/17/16.
//

#include "LoadState.hpp"

namespace State {

    LoadState::LoadState(Game& context)
    : IGameState(context)
    {

    }
    
    void LoadState::update(int time_since_last_update) {
        this->_context.SDL_facade.handle_sdl_events();

        this->_context.SDL_facade.clear_screen();
        this->_context.SDL_facade.draw_rect(CoordinateDouble{0,0}, 640, 480, Color{0,0,0});

        this->_loading_screen_time = this->_loading_screen_time + 2; //TODO: To ticks

        this->_context.SDL_facade.draw_text("Level Name Here", FontType::alterebro_pixel, this->_color, CoordinateDouble{500,15});

        // TODO: This is ugly and stupid
        if (this->_loading_screen_time < 150) {
            this->_context.SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, this->_color, CoordinateDouble{255,150});
            this->_context.SDL_facade.draw_image("res/loading_bar/loading_bar_1.bmp", CoordinateDouble{220, 220});
            this->_context.SDL_facade.draw_text("Finding Files...", FontType::alterebro_pixel, this->_color, CoordinateDouble{265,260});
        }
        else if (this->_loading_screen_time < 300) {
            this->_context.SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, this->_color, CoordinateDouble{255,150});
            this->_context.SDL_facade.draw_image("res/loading_bar/loading_bar_2.bmp", CoordinateDouble{220, 220});
            this->_context.SDL_facade.draw_text("Casting Rays...", FontType::alterebro_pixel, this->_color, CoordinateDouble{265,260});
        }
        else if (this->_loading_screen_time < 450) {
            this->_context.SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, this->_color, CoordinateDouble{255,150});
            this->_context.SDL_facade.draw_image("res/loading_bar/loading_bar_3.bmp", CoordinateDouble{220, 220});
            this->_context.SDL_facade.draw_text("Calculating Edges...", FontType::alterebro_pixel, this->_color, CoordinateDouble{245,260});
        }
        else if (this->_loading_screen_time < 600) {
            this->_context.SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, this->_color, CoordinateDouble{255,150});
            this->_context.SDL_facade.draw_image("res/loading_bar/loading_bar_4.bmp", CoordinateDouble{220, 220});
            this->_context.SDL_facade.draw_text("Doing other stuff...", FontType::alterebro_pixel, this->_color, CoordinateDouble{245,260});
        }
        else if (this->_loading_screen_time < 750) {
            this->_context.SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, this->_color, CoordinateDouble{255,150});
            this->_context.SDL_facade.draw_image("res/loading_bar/loading_bar_5.bmp", CoordinateDouble{220, 220});
            this->_context.SDL_facade.draw_text("Placing Player...", FontType::alterebro_pixel, this->_color, CoordinateDouble{260,260});
        }
        else if (this->_loading_screen_time < 900) {
            this->_context.SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, this->_color, CoordinateDouble{255,150});
            this->_context.SDL_facade.draw_image("res/loading_bar/loading_bar_6.bmp", CoordinateDouble{220, 220});
            this->_context.SDL_facade.draw_text("Increasing movement speed...", FontType::alterebro_pixel, this->_color, CoordinateDouble{203,260});
        }
        else if (this->_loading_screen_time < 1050) {
            this->_context.SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, this->_color, CoordinateDouble{255,150});
            this->_context.SDL_facade.draw_image("res/loading_bar/loading_bar_7.bmp", CoordinateDouble{220, 220});
            this->_context.SDL_facade.draw_text("Making textures...", FontType::alterebro_pixel, this->_color, CoordinateDouble{247,260});
        }
        else if (this->_loading_screen_time < 1200) {
            this->_context.SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, this->_color, CoordinateDouble{255,150});
            this->_context.SDL_facade.draw_image("res/loading_bar/loading_bar_6.bmp", CoordinateDouble{220, 220});
            this->_context.SDL_facade.draw_text("Destroying textures...", FontType::alterebro_pixel, this->_color, CoordinateDouble{232,260});
        }
        else if (this->_loading_screen_time < 1350) {
            this->_context.SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, this->_color, CoordinateDouble{255,150});
            this->_context.SDL_facade.draw_image("res/loading_bar/loading_bar_8.bmp", CoordinateDouble{220, 220});
            this->_context.SDL_facade.draw_text("Overloading!!!", FontType::alterebro_pixel, this->_color, CoordinateDouble{265,260});
        }
        else if (this->_loading_screen_time < 1450) {
            this->_context.SDL_facade.draw_text("Done Loading!", FontType::alterebro_pixel_plus, this->_color, CoordinateDouble{220,150});
        }
        else {
            this->_loading_screen_time = 0;
            // this->_context.set_new_state(std::make_shared<RunState>(this->_context));
        }

        this->_context.SDL_facade.render_buffer();
    }
}