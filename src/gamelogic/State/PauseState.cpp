//
// Created by sander on 11/17/16.
//

#include "PauseState.hpp"
#include "RunState.hpp"
#include "MenuState.hpp"

namespace State {

    void PauseState::update(GameLogic::Game& game, int time_since_last_update) {
        game.SDL_facade.handle_sdl_events();
        if(this->_timeSinceLastPress <= 15){ //TODO: TO SDL ticks
            this->_timeSinceLastPress++;
        }
        if(this->_timeSinceLastPress >= 15) {
            PressedKeys keys = game.SDL_facade.get_keys();
            for (auto key : keys) {
                switch (key) {
                    case Key::W:
                        if(this->_selected != 1){
                            this->_selected--;
                            this->_timeSinceLastPress = 0;
                        }
                        break;
                    case Key::S:
                        if(this->_selected != 2){
                            this->_selected++;
                            this->_timeSinceLastPress = 0;
                        }
                        break;
                    case Key::ESC:
                        game.set_new_state(std::make_shared<RunState>());
                        this->_timeSinceLastPress = 0;
                        break;
                    case Key::ENTER:
                        if(this->_selected == 1){
                            game.set_new_state(std::make_shared<RunState>());
                            this->_timeSinceLastPress = 0;
                        }
                        else if(this->_selected == 2) {
                            game.set_new_state(std::make_shared<MenuState>());
                            this->_timeSinceLastPress = 0;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        game.SDL_facade.clear_screen();
        game.SDL_facade.draw_text("Game Paused", FontType::alterebro_pixel_plus, this->_color, CoordinateDouble{50, 15});
        game.SDL_facade.draw_text("Resume game", FontType::alterebro_pixel, this->_color, CoordinateDouble{150,100});
        game.SDL_facade.draw_text("Quit to menu", FontType::alterebro_pixel, this->_color, CoordinateDouble{150,140});
        if(this->_selected == 1){
            game.SDL_facade.draw_rect(CoordinateDouble{120,106}, 15, 15, this->_color);
        }
        else if(this->_selected == 2){
            game.SDL_facade.draw_rect(CoordinateDouble{120,146}, 15, 15, this->_color);
        }

        game.SDL_facade.render_buffer();
    }
}