//
// Created by sander on 11/17/16.
//

#include "LoadState.hpp"

namespace State {

    void LoadState::update(Game& game, int time_since_last_update) {
        game.SDL_facade.handle_sdl_events();

        game.SDL_facade.clear_screen();
        game.SDL_facade.draw_rect(CoordinateDouble{0,0}, 640, 480, Color{0,0,0});

        this->_loading_screen_time = this->_loading_screen_time + 2; //TODO: To ticks

        game.SDL_facade.draw_text("Level Name Here", FontType::alterebro_pixel, this->_color, CoordinateDouble{500,15});

        // TODO: This is ugly and stupid
        if (this->_loading_screen_time < 150) {
            game.SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, this->_color, CoordinateDouble{255,150});
            game.SDL_facade.draw_image("res/loading_bar/loading_bar_1.bmp", CoordinateDouble{220, 220});
            game.SDL_facade.draw_text("Finding Files...", FontType::alterebro_pixel, this->_color, CoordinateDouble{265,260});
        }
        else if (this->_loading_screen_time < 300) {
            game.SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, this->_color, CoordinateDouble{255,150});
            game.SDL_facade.draw_image("res/loading_bar/loading_bar_2.bmp", CoordinateDouble{220, 220});
            game.SDL_facade.draw_text("Casting Rays...", FontType::alterebro_pixel, this->_color, CoordinateDouble{265,260});
        }
        else if (this->_loading_screen_time < 450) {
            game.SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, this->_color, CoordinateDouble{255,150});
            game.SDL_facade.draw_image("res/loading_bar/loading_bar_3.bmp", CoordinateDouble{220, 220});
            game.SDL_facade.draw_text("Calculating Edges...", FontType::alterebro_pixel, this->_color, CoordinateDouble{245,260});
        }
        else if (this->_loading_screen_time < 600) {
            game.SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, this->_color, CoordinateDouble{255,150});
            game.SDL_facade.draw_image("res/loading_bar/loading_bar_4.bmp", CoordinateDouble{220, 220});
            game.SDL_facade.draw_text("Doing other stuff...", FontType::alterebro_pixel, this->_color, CoordinateDouble{245,260});
        }
        else if (this->_loading_screen_time < 750) {
            game.SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, this->_color, CoordinateDouble{255,150});
            game.SDL_facade.draw_image("res/loading_bar/loading_bar_5.bmp", CoordinateDouble{220, 220});
            game.SDL_facade.draw_text("Placing Player...", FontType::alterebro_pixel, this->_color, CoordinateDouble{260,260});
        }
        else if (this->_loading_screen_time < 900) {
            game.SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, this->_color, CoordinateDouble{255,150});
            game.SDL_facade.draw_image("res/loading_bar/loading_bar_6.bmp", CoordinateDouble{220, 220});
            game.SDL_facade.draw_text("Increasing movement speed...", FontType::alterebro_pixel, this->_color, CoordinateDouble{203,260});
        }
        else if (this->_loading_screen_time < 1050) {
            game.SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, this->_color, CoordinateDouble{255,150});
            game.SDL_facade.draw_image("res/loading_bar/loading_bar_7.bmp", CoordinateDouble{220, 220});
            game.SDL_facade.draw_text("Making textures...", FontType::alterebro_pixel, this->_color, CoordinateDouble{247,260});
        }
        else if (this->_loading_screen_time < 1200) {
            game.SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, this->_color, CoordinateDouble{255,150});
            game.SDL_facade.draw_image("res/loading_bar/loading_bar_6.bmp", CoordinateDouble{220, 220});
            game.SDL_facade.draw_text("Destroying textures...", FontType::alterebro_pixel, this->_color, CoordinateDouble{232,260});
        }
        else if (this->_loading_screen_time < 1350) {
            game.SDL_facade.draw_text("Loading...", FontType::alterebro_pixel_plus, this->_color, CoordinateDouble{255,150});
            game.SDL_facade.draw_image("res/loading_bar/loading_bar_8.bmp", CoordinateDouble{220, 220});
            game.SDL_facade.draw_text("Overloading!!!", FontType::alterebro_pixel, this->_color, CoordinateDouble{265,260});
        }
        else if (this->_loading_screen_time < 1450) {
            game.SDL_facade.draw_text("Done Loading!", FontType::alterebro_pixel_plus, this->_color, CoordinateDouble{220,150});
        }
        else {
            this->_loading_screen_time = 0;
            // game.set_new_state(std::make_shared<RunState>());
        }

        game.SDL_facade.render_buffer();
    }
}