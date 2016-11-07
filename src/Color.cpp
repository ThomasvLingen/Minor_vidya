//
// Created by wouter on 11/7/16.
//
#include "Color.hpp"

Color Color::reduce_intensity() {
    this->r_value = this->r_value / 2;
    this->g_value = this->g_value / 2;
    this->b_value = this->b_value / 2;
    return this&;
};



