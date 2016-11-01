//
// Created by mafn on 11/1/16.
//

#include "Raycasting.hpp"

namespace Engine {

    Raycasting::Raycasting()
    {

    }

    Raycasting::~Raycasting()
    {

    }

    void Raycasting::handle_input()
    {
        // Call world handle_input

        // If we need to do something on a keystroke, handle input ourselves
    }

    void Raycasting::update(int delta_time)
    {
        // Call world update
    }

    void Raycasting::draw()
    {
        // Draw the world through raycasting algorithms,
        // For this we need to get information from the world (Like the tile map
        // For this we also need the SDL_Facade to draw
    }
}
