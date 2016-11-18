//
// Created by sander on 11/17/16.
//

#include "CreditState.hpp"

using State::CreditState;

namespace State {

    CreditState::CreditState()
    {

    }

    CreditState::~CreditState() {

    }

    void CreditState::update(GameLogic::Game& game) {
        PressedKeys keys = game._SDL_facade.get_keys();
        if(timeSinceLastPress <= 20){ //TODO: TO SDL ticks
            timeSinceLastPress++;
        }
        if(timeSinceLastPress > 20){
            for(auto key : keys){
                switch (key) {

                }
            }
        }


        Color color{255,255,255};
        game._SDL_facade.draw_image("res/creditscreen.bmp" , CoordinateDouble{0,0});
        game._SDL_facade.draw_text("Vidya Game is made by:", FontType::alterebro_pixel, color, CoordinateDouble{300, 50});
        game._SDL_facade.draw_text("- Thomas Pannekoek:", FontType::alterebro_pixel, color, CoordinateDouble{340, 80});
        game._SDL_facade.draw_text("- Jorg de Bont", FontType::alterebro_pixel, color, CoordinateDouble{340, 110});
        game._SDL_facade.draw_text("- Wouter van Geel", FontType::alterebro_pixel, color, CoordinateDouble{340, 140});
        game._SDL_facade.draw_text("- Sander van Geel", FontType::alterebro_pixel, color, CoordinateDouble{340, 170});
        game._SDL_facade.draw_text("- Martijn Frielink", FontType::alterebro_pixel, color, CoordinateDouble{340, 200});
        game._SDL_facade.draw_text("- Joost van Rijsinge", FontType::alterebro_pixel, color, CoordinateDouble{340, 230});
        game._SDL_facade.draw_text("- Jelmer van der Schoot", FontType::alterebro_pixel, color, CoordinateDouble{340, 260});

    }
}