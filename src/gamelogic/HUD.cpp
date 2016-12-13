//
// Created by sander on 12/12/16.
//

#include "HUD.hpp"

namespace GameLogic {

    HUD::HUD(SDLFacade& _SDL_facade, Player& player)
    : Drawable(_SDL_facade)
    , _player(player)
    , _start_time(0)
    {
    }
    
    int HUD::get_current_time() {
        return this->_current_time * 1000;
    }

    int HUD::get_current_time() {
        return this->_current_time * 1000;
    }

    void HUD::set_ticks_set_off(int ticks) {
        this->_start_time = ticks;
    }

    void HUD::_draw_health(int health) {

        // draw amount of health
        string health_amount;
        if(health < 10){
            health_amount = "0";
        }
        health_amount += std::to_string(health);
        _SDL_facade.draw_text(health_amount, FontType::alterebro_pixel, Color{255, 38, 70}, {222, 430});

        // draw amount of blocks
        int amount_of_blocks = 10;
        int set_off = 62;
        int health_not_round = 0;
        if(health % 8 > 0) {
            health_not_round = 1;
        }


        for (int j = 0; j < ((health / 8 ) + health_not_round); ++j) {        // round up
            amount_of_blocks--;                   // for each lighter block we do not need an extra block
            set_off = 62 + (j * 14);
            _SDL_facade.draw_rect({set_off, 433}, 12, 24, {255, 38, 70});
        }

        if(set_off != 62){
            set_off += 14;
        }

        for (int i = 10 - amount_of_blocks; i < 10; ++i) {
            set_off = 62 + (i * 14);
            _SDL_facade.draw_rect({set_off, 433}, 12, 24, {121, 41, 52});
        }

    }

    void HUD::draw(){
        _SDL_facade.draw_image(VIDYA_RUNPATH + "res/HUD.bmp", {0, 410});

        //draw HP
        this->_draw_health(_player.get_health());

        // draw time
        _SDL_facade.draw_text(this->_time_to_string(this->_current_time), FontType::alterebro_pixel, Color{53, 194, 222}, {390, 430});

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