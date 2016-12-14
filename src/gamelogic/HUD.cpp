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


    void HUD::set_start_tick(int ticks) {
        this->_start_time = ticks;
    }

    int HUD::_calculate_health_blocks(int health) {
        return (int) ceil((double)health / (this->_total_health / this->_amount_health_blocks));
    }

    void HUD::_draw_health_text(int health) {
        string health_amount;
        if(health < this->_amount_health_blocks){
            health_amount = "0";
        }
        health_amount += std::to_string(health);
        _SDL_facade.draw_text(health_amount, FontType::alterebro_pixel, this->_health_text_color, this->_health_text_pos);
    }

    void HUD::_draw_health_blocks(int health) {
        int amount_of_blocks = this->_amount_health_blocks;
        int set_off = 62;

        for (int j = 0; j < this->_calculate_health_blocks(health); ++j) {
            amount_of_blocks--;                   // for each lighter block we do not need an extra block
            set_off = 62 + (j * (this->_health_block_width + 2)); // 2 is spacing
            _SDL_facade.draw_rect({set_off, 433}, this->_health_block_width, this->_health_block_height, this->_health_block_full);
        }

        if(set_off != 62){
            set_off += this->_health_block_width + 2;
        }

        for (int i = this->_amount_health_blocks - amount_of_blocks; i < this->_amount_health_blocks; ++i) {
            set_off = 62 + (i * (this->_health_block_width + 2)); // 2 is spacing
            _SDL_facade.draw_rect({set_off, 433}, this->_health_block_width, this->_health_block_height, this->_health_block_empty);
        }

    }

    void HUD::_draw_face() {
        if(this->_current_time % 4 > 1){
            _SDL_facade.draw_image(VIDYA_RUNPATH + "res/look_front.bmp", this->_character_head_pos);
        } else if(this->_current_time % 3 > 1){
            _SDL_facade.draw_image(VIDYA_RUNPATH + "res/look_left.bmp", this->_character_head_pos);
        } else if(this->_current_time % 2 > 1){
            _SDL_facade.draw_image(VIDYA_RUNPATH + "res/look_front.bmp", this->_character_head_pos);
        } else {
            _SDL_facade.draw_image(VIDYA_RUNPATH + "res/look_right.bmp", this->_character_head_pos);
        }
    }

    void HUD::draw(){
        //draw HUD
        _SDL_facade.draw_image(VIDYA_RUNPATH + "res/HUDv2.bmp", this->_HUD_pos);

        //draw HP
        this->_draw_health_text(_player.get_health());
        this->_draw_health_blocks(_player.get_health());

        // draw time
        _SDL_facade.draw_text(this->_time_to_string(this->_current_time), FontType::alterebro_pixel, this->_time_color, this->_time_pos);

        // draw face
        this->_draw_face();

        // draw items
        //TODO inplement items
    }

    void HUD::update(int delta_time){
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