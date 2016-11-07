//
// Created by wouter on 11/1/16.
//
#include <cstdint>

struct Color {
    uint8_t r_value;
    uint8_t g_value;
    uint8_t b_value;

    Color reduce_intensity();
};

