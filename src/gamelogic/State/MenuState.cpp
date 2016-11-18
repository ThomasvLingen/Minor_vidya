//
// Created by sander on 11/17/16.
//

#include "MenuState.hpp"
#include "../Game.hpp"
using State::MenuState;

namespace State {

    MenuState::MenuState(){

    }

    MenuState::~MenuState(){

    }

    void MenuState::update(GameLogic::Game& game) {
        game._SDL_facade.handle_sdl_events();
        game._raycasting_engine.handle_input();
        PressedKeys keys = game._SDL_facade.get_keys();
        if(timeSinceLastPress <= 20){ //TODO: TO SDL ticks
            timeSinceLastPress++;
        }
        if(timeSinceLastPress > 20){
            for(auto key : keys){
                switch (key) {
                    case Key::W :
                        if(selected != 1){
                            selected--;
                            timeSinceLastPress = 0;
                        }
                        break;
                    case Key::S :
                        if(selected != 3){
                            selected++;
                            timeSinceLastPress = 0;
                        }
                        break;
                    case Key::ESC:
                        game.set_new_state(game.get_start_up_state());
                        timeSinceLastPress = 0;
                        break;
                    case Key::ENTER:
                        if(selected == 1){
                            game.set_new_state(game.get_load_state());
                            timeSinceLastPress = 0;
                        }
                        else if(selected == 2){
                            game.set_new_state(game.get_help_state());
                            timeSinceLastPress = 0;
                        }
                        else if(selected == 3){
                            game.set_new_state(game.get_credit_state());
                            timeSinceLastPress = 0;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        game._SDL_facade.clear_screen();
        game._SDL_facade.draw_image("res/menuscreen.bmp", CoordinateDouble{0,0});
        Color color{255,255,255};
        game._SDL_facade.draw_text("Vidya Game", FontType::alterebro_pixel, color, CoordinateDouble{20,20});
        game._SDL_facade.draw_text("Start Game", FontType::alterebro_pixel, color, CoordinateDouble{150,100});
        game._SDL_facade.draw_text("Help", FontType::alterebro_pixel, color, CoordinateDouble{150,140});
        game._SDL_facade.draw_text("Credits", FontType::alterebro_pixel, color, CoordinateDouble{150,180});


        if(selected == 1){
            game._SDL_facade.draw_rect(CoordinateDouble{120,106}, 15, 15, color);
        }
        else if(selected == 2){
            game._SDL_facade.draw_rect(CoordinateDouble{120,146}, 15, 15, color);
        }
        else if(selected == 3){
            game._SDL_facade.draw_rect(CoordinateDouble{120,186}, 15, 15, color);
        }
        game._SDL_facade.render_buffer();
    }
}