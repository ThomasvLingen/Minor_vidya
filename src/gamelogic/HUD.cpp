//
// Created by sander on 12/12/16.
//

#include "HUD.hpp"

namespace GameLogic {

    HUD::HUD(SDLFacade& _SDL_facade, Player* player)
    : Drawable(_SDL_facade)
    , _start_time(0)
    {
    }

    //TODO remove
    HUD::HUD(SDLFacade& _SDL_facade)
    : Drawable(_SDL_facade)
    , _start_time(0)
    {

    }

    int HUD::get_current_time() {
        return this->_current_time;
    }

    void HUD::set_ticks_set_off(int ticks) {
        this->_start_time = ticks;
    }

    void HUD::draw(){
        _SDL_facade.draw_rect(CoordinateDouble{0,400}, 640, 80, Color{139,69,19}); //background
        _SDL_facade.draw_rect(CoordinateDouble{0,400}, 640, 5, Color{160,82,45}); // upper boarder
        _SDL_facade.draw_rect(CoordinateDouble{160,400}, 5, 80, Color{160,82,45}); // vertical table boarder
        _SDL_facade.draw_rect(CoordinateDouble{320,400}, 5, 80, Color{160,82,45});
        _SDL_facade.draw_rect(CoordinateDouble{480,400}, 5, 80, Color{160,82,45});

        //draw HP
        _SDL_facade.draw_text("HP", FontType::alterebro_pixel, Color{0,0,0}, {60, 430});
        _SDL_facade.draw_text("100", FontType::alterebro_pixel, Color{0,0,0}, {60, 450}); //TODO get hp from player

        // draw time
        _SDL_facade.draw_text("Time", FontType::alterebro_pixel, Color{0,0,0}, {220, 430});
        _SDL_facade.draw_text(this->_time_to_string(this->_current_time), FontType::alterebro_pixel, Color{0,0,0}, {220, 450});
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