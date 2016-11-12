//
// Created by waseland on 11/7/16.
//

#include "Player.hpp"

namespace GameLogic
{
    Player::Player(CoordinateDouble position)
    : PointOfView(position, Engine::RaycastingVector{-1, 0}, Engine::RaycastingVector{0, 0.66})
    {

    }

    Player::~Player()
    {

    }
}