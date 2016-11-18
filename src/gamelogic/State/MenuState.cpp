//
// Created by sander on 11/17/16.
//

#include "MenuState.hpp"
#include "StartUpState.hpp"
#include "HelpState.hpp"
#include "LoadState.hpp"
#include "CreditState.hpp"

namespace State {

    void MenuState::update(GameLogic::Game& game, int time_since_last_update) {
        game.SDL_facade.handle_sdl_events();
        PressedKeys keys = game.SDL_facade.get_keys();
        if(this->_timeSinceLastPress <= 20){ //TODO: TO SDL ticks
            this->_timeSinceLastPress++;
        }
        if(this->_timeSinceLastPress > 20){
            for(auto key : keys){
                switch (key) {
                    case Key::W :
                        if(this->_selected != 1){
                            this->_selected--;
                            this->_timeSinceLastPress = 0;
                        }
                        break;
                    case Key::S :
                        if(_selected != 3){
                            this->_selected++;
                            this->_timeSinceLastPress = 0;
                        }
                        break;
                    case Key::ESC:
                        game.set_new_state(std::make_shared<StartUpState>());
                        break;
                    case Key::ENTER:
                        if(this->_selected == 1){
                            game.set_new_state(std::make_shared<LoadState>());
                        }
                        else if(this->_selected == 2){
                            game.set_new_state(std::make_shared<HelpState>());
                        }
                        else if(this->_selected == 3){
                            game.set_new_state(std::make_shared<CreditState>());
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        game.SDL_facade.clear_screen();
        game.SDL_facade.draw_image("res/menuscreen.bmp", CoordinateDouble{0,0});
        game.SDL_facade.draw_text("Vidya Game", FontType::alterebro_pixel, this->_color, CoordinateDouble{20,20});
        game.SDL_facade.draw_text("Start Game", FontType::alterebro_pixel, this->_color, CoordinateDouble{150,100});
        game.SDL_facade.draw_text("Help", FontType::alterebro_pixel, this->_color, CoordinateDouble{150,140});
        game.SDL_facade.draw_text("Credits", FontType::alterebro_pixel, this->_color, CoordinateDouble{150,180});


        if(this->_selected == 1){
            game.SDL_facade.draw_rect(CoordinateDouble{120,106}, 15, 15, _color);
        }
        else if(this->_selected == 2){
            game.SDL_facade.draw_rect(CoordinateDouble{120,146}, 15, 15, _color);
        }
        else if(this->_selected == 3){
            game.SDL_facade.draw_rect(CoordinateDouble{120,186}, 15, 15, _color);
        }
        game.SDL_facade.render_buffer();
    }
}