//
// Created by sander on 12/12/16.
//

#include "HUD.hpp"

namespace GameLogic {

    HUD::HUD(SDLFacade& _SDL_facade, Player& player)
    : Drawable(_SDL_facade)
    , _start_time(0)
    {
    }

    int HUD::get_current_time() {
        return this->_current_time * 1000;
    }

    void HUD::set_ticks_set_off(int ticks) {
        this->_start_time = ticks;
    }

    void HUD::draw(){
        _SDL_facade.draw_image(VIDYA_RUNPATH + "res/HUD.bmp", {0, 410});

        //draw HP
        //TODO get hp from player
        _SDL_facade.draw_text("80", FontType::alterebro_pixel, Color{0,0,0}, {222, 430});

        // draw time
        _SDL_facade.draw_text(this->_time_to_string(this->_current_time), FontType::alterebro_pixel, Color{0,0,0}, {390, 430});

        // draw items
        //TODO inplement items
    }

    void HUD::update(int delta_time){
        //TODO health reduce
        this->_current_time = this->_calculate_time(_SDL_facade.get_ticks() - _start_time);
    }

    int HUD::_calculate_time(int ticks){
        return (ticks / 1000);
    }

    string HUD::_time_to_string(int current_time){
        int seconds = current_time % 60;
        int minutes = current_time / 60;
        string output;
        output += std::to_string(minutes);
        output += " : ";
        if(seconds < 10){
            output += "0";
        }
        output += std::to_string(seconds);
        return output;
    }
}