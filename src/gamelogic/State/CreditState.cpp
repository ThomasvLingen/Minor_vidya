//
// Created by sander on 11/17/16.
//

#include "CreditState.hpp"
#include "MenuState.hpp"

namespace State {

    void CreditState::update(GameLogic::Game& game, int time_since_last_update) {
        game.SDL_facade.handle_sdl_events();
        PressedKeys keys = game.SDL_facade.get_keys();
        if(this->_timeSinceLastPress <= 20){ //TODO: TO SDL ticks
            this->_timeSinceLastPress++;
        }
        if(this->_timeSinceLastPress > 20){
            for(auto key : keys){
                switch (key) {
                    case Key::ESC:
                        game.set_new_state(std::make_shared<MenuState>());
                        break;
                    default:
                        break;
                }
            }
        }

        game.SDL_facade.clear_screen();
        game.SDL_facade.draw_image("res/creditscreen.bmp" , CoordinateDouble{0,0});
        game.SDL_facade.draw_text("Vidya Game is made by:", FontType::alterebro_pixel, this->_color, CoordinateDouble{300, 50});
        game.SDL_facade.draw_text("- Thomas van Lingen:", FontType::alterebro_pixel, this->_color, CoordinateDouble{340, 80});
        game.SDL_facade.draw_text("- Jorg de Bont", FontType::alterebro_pixel, this->_color, CoordinateDouble{340, 110});
        game.SDL_facade.draw_text("- Wouter van Geel", FontType::alterebro_pixel, this->_color, CoordinateDouble{340, 140});
        game.SDL_facade.draw_text("- Sander van Geel", FontType::alterebro_pixel, this->_color, CoordinateDouble{340, 170});
        game.SDL_facade.draw_text("- Martijn Frielink", FontType::alterebro_pixel, this->_color, CoordinateDouble{340, 200});
        game.SDL_facade.draw_text("- Joost van Rijsinge", FontType::alterebro_pixel, this->_color, CoordinateDouble{340, 230});
        game.SDL_facade.draw_text("- Jelmer van der Schoot", FontType::alterebro_pixel, this->_color, CoordinateDouble{340, 260});
        game.SDL_facade.render_buffer();
    }
}