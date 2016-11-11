//
// Created by wouter on 11/7/16.
//
#include "Color.hpp"
namespace Engine {
    Color Color::reduce_intensity() {
        uint8_t temp_r_value = this->r_value / 2;
        uint8_t temp_g_value = this->g_value / 2;
        uint8_t temp_b_value = this->b_value / 2;

        Color return_color = {
                .r_value = temp_r_value,
                .g_value = temp_g_value,
                .b_value = temp_b_value
        };

        return return_color;
    };
}



