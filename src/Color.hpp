//
// Created by wouter on 11/1/16.
//

#ifndef MINOR_VIDYA_COLOR_HPP
#define MINOR_VIDYA_COLOR_HPP

struct Color{
    uint8_t r_value;
    uint8_t g_value;
    uint8_t b_value;

    Color reduce_intensity();
};

#endif /* MINOR_VIDYA_COLOR_HPP */