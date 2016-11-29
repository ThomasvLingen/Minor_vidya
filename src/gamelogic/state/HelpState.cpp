//
// Created by sander on 11/18/16.
//

#include "HelpState.hpp"
#include "MenuState.hpp"

namespace State {

    HelpState::HelpState(Game& context)
    : IGameState(context)
    {

    }

    void HelpState::update(int time_since_last_update)
    {
        this->_context.SDL_facade.handle_sdl_events();

        PressedKeys keys = this->_context.SDL_facade.get_keys();

        if (this->_timeSinceLastPress <= 20) { //TODO: TO SDL ticks
            this->_timeSinceLastPress++;
        }
        if (this->_timeSinceLastPress > 20) {
            for (auto key : keys) {
                switch (key) {
                    case Key::ESC:
                        this->_context.set_new_state(std::make_shared<MenuState>(this->_context));
                        this->_timeSinceLastPress  = 0;
                        break;
                    default:
                        break;
                }
            }
        }

        this->_context.SDL_facade.clear_screen();
        this->_context.SDL_facade.draw_image(VIDYA_RUNPATH + "res/helpscreen.bmp" , {0,0});
        // TODO: This is retarded and should be refactored
        this->_context.SDL_facade.draw_text("Controls for Vidya Game", FontType::alterebro_pixel, this->_color, {120, 50});
        this->_context.SDL_facade.draw_text("Movement Forward:   W", FontType::alterebro_pixel, this->_color, {160, 80});
        this->_context.SDL_facade.draw_text("Movement Backward:  S", FontType::alterebro_pixel, this->_color, {160, 110});
        this->_context.SDL_facade.draw_text("Movement Left:         A", FontType::alterebro_pixel, this->_color, {160, 140});
        this->_context.SDL_facade.draw_text("Movement Right:        D", FontType::alterebro_pixel, this->_color, {160, 170});
        this->_context.SDL_facade.draw_text("Rotate Left:             Q", FontType::alterebro_pixel, this->_color, {160, 200});
        this->_context.SDL_facade.draw_text("Rotate Right:            E", FontType::alterebro_pixel, this->_color, {160, 230});
        this->_context.SDL_facade.draw_text("Select:                    Enter", FontType::alterebro_pixel, this->_color, {160, 260});
        this->_context.SDL_facade.draw_text("Back:                       ESC", FontType::alterebro_pixel, this->_color, {160, 290});
        this->_context.SDL_facade.render_buffer();
    }
}