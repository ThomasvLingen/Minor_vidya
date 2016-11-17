//
// Created by wouter on 11/7/16.
//
#include "Color.hpp"
namespace Engine {

    /// \brief This function creates a color with half the values of the current object
    ///
    /// \return This function returns a color object
    Color Color::reduce_intensity()
    {
        return  {
                (uint8_t)(this->r_value / 2),
                (uint8_t)(this->g_value / 2),
                (uint8_t)(this->b_value / 2)
        };
    };
}



