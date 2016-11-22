//
// Created by sander on 11/18/16.
//

#include "HelpState.hpp"
#include "MenuState.hpp"

namespace State {

    void HelpState::update(Game& game, int time_since_last_update)
    {
        game.SDL_facade.handle_sdl_events();

        PressedKeys keys = game.SDL_facade.get_keys();

        if (this->_timeSinceLastPress <= 20) { //TODO: TO SDL ticks
            this->_timeSinceLastPress++;
        }
        if (this->_timeSinceLastPress > 20) {
            for (auto key : keys) {
                switch (key) {
                    case Key::ESC:
                        game.set_new_state(std::make_shared<MenuState>());
                        this->_timeSinceLastPress  = 0;
                        break;
                    default:
                        break;
                }
            }
        }

        game.SDL_facade.clear_screen();
        game.SDL_facade.draw_image("res/helpscreen.bmp" , CoordinateDouble{0,0});
        // TODO: This is retarded and should be refactored
        game.SDL_facade.draw_text("Controls for Vidya Game", FontType::alterebro_pixel, this->_color, CoordinateDouble{120, 50});
        game.SDL_facade.draw_text("Movement Forward:   W", FontType::alterebro_pixel, this->_color, CoordinateDouble{160, 80});
        game.SDL_facade.draw_text("Movement Backward:  S", FontType::alterebro_pixel, this->_color, CoordinateDouble{160, 110});
        game.SDL_facade.draw_text("Movement Left:         A", FontType::alterebro_pixel, this->_color, CoordinateDouble{160, 140});
        game.SDL_facade.draw_text("Movement Right:        D", FontType::alterebro_pixel, this->_color, CoordinateDouble{160, 170});
        game.SDL_facade.draw_text("Rotate Left:             Q", FontType::alterebro_pixel, this->_color, CoordinateDouble{160, 200});
        game.SDL_facade.draw_text("Rotate Right:            E", FontType::alterebro_pixel, this->_color, CoordinateDouble{160, 230});
        game.SDL_facade.draw_text("Select:                    Enter", FontType::alterebro_pixel, this->_color, CoordinateDouble{160, 260});
        game.SDL_facade.draw_text("Back:                       ESC", FontType::alterebro_pixel, this->_color, CoordinateDouble{160, 290});
        game.SDL_facade.render_buffer();
    }
}