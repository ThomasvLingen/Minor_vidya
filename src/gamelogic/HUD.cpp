//
// Created by sander on 12/12/16.
//

#include "HUD.hpp"
#include "../util/UnusedMacro.hpp"
#include "../util/StringUtil.hpp"

namespace GameLogic {

    HUD::HUD(SDLFacade& _SDL_facade, Player& player)
    : Drawable(_SDL_facade)
    , _player(player)
    {
    }

    int HUD::_calculate_health_blocks()
    {
        double health_per_block = this->_player.get_total_health() / this->_amount_health_blocks;
        return (int) ceil((double)this->_player.get_health() / health_per_block);
    }

    void HUD::_draw_health_text()
    {
        std::stringstream health_to_string_stream;
        health_to_string_stream << std::setfill('0') << std::setw(2) << this->_player.get_health(); // 2 is size of total health (string size)
        string health_to_string;
        health_to_string_stream >> health_to_string;

        this->_SDL_facade.draw_text(health_to_string, FontType::alterebro_pixel, this->_health_text_color, this->_health_text_pos);
    }

    void HUD::_draw_health_blocks()
    {
        int amount_of_blocks = this->_amount_health_blocks;
        int xpos_draw_block;

        for (int j = 0; j < this->_calculate_health_blocks(); ++j) {
            amount_of_blocks--;                   // for each lighter block we do not need an extra block
            xpos_draw_block = this->_set_off_health_bar + (j * (this->_health_block_width + this->_spacing_blocks));
            this->_SDL_facade.draw_rect({xpos_draw_block, this->_ypos_draw_block}, this->_health_block_width, this->_health_block_height, this->_health_block_full);
        }

        for (int i = this->_amount_health_blocks - amount_of_blocks; i < this->_amount_health_blocks; ++i) {
            xpos_draw_block = this->_set_off_health_bar + (i * (this->_health_block_width + this->_spacing_blocks)); // 2 is spacing
            this->_SDL_facade.draw_rect({xpos_draw_block, this->_ypos_draw_block}, this->_health_block_width, this->_health_block_height, this->_health_block_empty);
        }

    }

    void HUD::_draw_face()
    {
        if (this->_get_current_time() % 4 > 1) {
            this->_SDL_facade.draw_image(this->HUD_FACE_FRONT, this->_character_head_pos);
        } else if (this->_get_current_time() % 3 > 1) {
            this->_SDL_facade.draw_image(this->HUD_FACE_LEFT, this->_character_head_pos);
        } else {
            this->_SDL_facade.draw_image(this->HUD_FACE_RIGHT, this->_character_head_pos);
        }
    }

    void HUD::draw()
    {
        //draw HUD
        this->_SDL_facade.draw_image(this->HUD_PATH, this->_HUD_pos);

        //draw HP
        this->_draw_health_text();
        this->_draw_health_blocks();

        // draw time
        this->_SDL_facade.draw_text(
            StringUtil::time_to_string(
                this->_get_current_time()
            ),
            FontType::alterebro_pixel, this->_time_color,
            this->_time_pos
        );

        // draw face
        this->_draw_face();

        // draw items
        //TODO inplement items
    }

    void HUD::update(int delta_time)
    {
        UNUSED(delta_time)
    }

    int HUD::_get_current_time()
    {
        return this->_player.get_level()->in_game_ticks / 1000;
    }
}