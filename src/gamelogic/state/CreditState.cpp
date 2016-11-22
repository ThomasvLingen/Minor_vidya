//
// Created by sander on 11/17/16.
//

#include "CreditState.hpp"
#include "MenuState.hpp"

namespace State {

    CreditState::CreditState(Game& context)
    : IGameState(context)
    {

    }

    void CreditState::update(int time_since_last_update) {
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
                        break;
                    default:
                        break;
                }
            }
        }

        this->_context.SDL_facade.clear_screen();
        this->_context.SDL_facade.draw_image("res/creditscreen.bmp" , CoordinateDouble{0,0});
        this->_context.SDL_facade.draw_text("Vidya Game is made by:", FontType::alterebro_pixel, this->_color, {300, 50});
        this->_context.SDL_facade.draw_text("- Thomas van Lingen:", FontType::alterebro_pixel, this->_color, {340, 80});
        this->_context.SDL_facade.draw_text("- Jorg de Bont", FontType::alterebro_pixel, this->_color, {340, 110});
        this->_context.SDL_facade.draw_text("- Wouter van Geel", FontType::alterebro_pixel, this->_color, {340, 140});
        this->_context.SDL_facade.draw_text("- Sander van Geel", FontType::alterebro_pixel, this->_color, {340, 170});
        this->_context.SDL_facade.draw_text("- Martijn Frielink", FontType::alterebro_pixel, this->_color, {340, 200});
        this->_context.SDL_facade.draw_text("- Joost van Rijsinge", FontType::alterebro_pixel, this->_color, {340, 230});
        this->_context.SDL_facade.draw_text("- Jelmer van der Schoot", FontType::alterebro_pixel, this->_color, {340, 260});
        this->_context.SDL_facade.render_buffer();
    }
}