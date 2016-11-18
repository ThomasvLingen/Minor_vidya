//
// Created by sander on 11/17/16.
//

#include "PauseState.hpp"
#include "../Game.hpp"
using State::PauseState;

namespace State {

    PauseState::PauseState(){

    }

    PauseState::~PauseState() {

    }

    void PauseState::update(GameLogic::Game& game) {
        game._SDL_facade.handle_sdl_events();
        game._raycasting_engine.handle_input();
        if(timeSinceLastPress <= 15){ //TODO: TO SDL ticks
            timeSinceLastPress++;
        }
        if(timeSinceLastPress >= 15) {
            PressedKeys keys = game._SDL_facade.get_keys();
            for (auto key : keys) {
                switch (key) {
                    case Key::W:
                        if(selected != 1){
                            selected--;
                            timeSinceLastPress = 0;
                        }
                        break;
                    case Key::S:
                        if(selected != 2){
                            selected++;
                            timeSinceLastPress = 0;
                        }
                        break;
                    case Key::ESC:
                        game.set_new_state(game.get_run_state());
                        timeSinceLastPress = 0;
                        break;
                    case Key::ENTER:
                        if(selected == 1){
                            game.set_new_state(game.get_run_state());
                            timeSinceLastPress = 0;
                        }
                        else if(selected == 2) {
                            game.set_new_state(game.get_menu_state());
                            timeSinceLastPress = 0;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        game._SDL_facade.clear_screen();
        Color color{255,255,255};
        game._SDL_facade.draw_text("Game Paused", FontType::alterebro_pixel_plus, color, CoordinateDouble{50, 15});
        game._SDL_facade.draw_text("Resume game", FontType::alterebro_pixel, color, CoordinateDouble{150,100});
        game._SDL_facade.draw_text("Quit to menu", FontType::alterebro_pixel, color, CoordinateDouble{150,140});
        if(selected == 1){
            game._SDL_facade.draw_rect(CoordinateDouble{120,106}, 15, 15, color);
        }
        else if(selected == 2){
            game._SDL_facade.draw_rect(CoordinateDouble{120,146}, 15, 15, color);
        }

        game._SDL_facade.render_buffer();
    }
}