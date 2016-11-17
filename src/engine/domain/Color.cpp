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
                this->r_value = (uint8_t)(this->r_value / 2),
                this->g_value = (uint8_t)(this->g_value / 2),
                this->b_value = (uint8_t)(this->b_value / 2)
        };
    };
}



