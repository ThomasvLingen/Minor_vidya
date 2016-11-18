//
// Created by sander on 11/18/16.
//

#include "HelpState.hpp"

using State::HelpState;

namespace State {

    HelpState::HelpState()
    {

    }

    HelpState::~HelpState()
    {

    }

    void HelpState::update(GameLogic::Game& game)
    {
        game._SDL_facade.handle_sdl_events();
        game._raycasting_engine.handle_input();
        PressedKeys keys = game._SDL_facade.get_keys();
        if(timeSinceLastPress <= 20){ //TODO: TO SDL ticks
            timeSinceLastPress++;
        }
        if(timeSinceLastPress > 20){
            for(auto key : keys){
                switch (key) {
                    case Key::ESC:
                        game.set_new_state(game.get_menu_state());
                        timeSinceLastPress  = 0;
                        break;
                    default:
                        break;
                }
            }
        }


        game._SDL_facade.clear_screen();
        Color color{255,255,255};
        game._SDL_facade.draw_image("res/helpscreen.bmp" , CoordinateDouble{0,0});
        game._SDL_facade.draw_text("Controls for Vidya Game", FontType::alterebro_pixel, color, CoordinateDouble{120, 50});
        game._SDL_facade.draw_text("Movement Forward:   W", FontType::alterebro_pixel, color, CoordinateDouble{160, 80});
        game._SDL_facade.draw_text("Movement Backward:  S", FontType::alterebro_pixel, color, CoordinateDouble{160, 110});
        game._SDL_facade.draw_text("Movement Left:         A", FontType::alterebro_pixel, color, CoordinateDouble{160, 140});
        game._SDL_facade.draw_text("Movement Right:        D", FontType::alterebro_pixel, color, CoordinateDouble{160, 170});
        game._SDL_facade.draw_text("Rotate Left:             Q", FontType::alterebro_pixel, color, CoordinateDouble{160, 200});
        game._SDL_facade.draw_text("Rotate Right:            E", FontType::alterebro_pixel, color, CoordinateDouble{160, 230});
        game._SDL_facade.draw_text("Select:                    Enter", FontType::alterebro_pixel, color, CoordinateDouble{160, 260});
        game._SDL_facade.draw_text("Back:                       ESC", FontType::alterebro_pixel, color, CoordinateDouble{160, 290});
        game._SDL_facade.render_buffer();
    }
}