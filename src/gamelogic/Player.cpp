//
// Created by waseland on 11/7/16.
//

#include "Player.hpp"

Player::Player(DoubleCoordinate position)
: PointOfView(position, Engine::RaycastingVector{-1 , 0}, Engine::RaycastingVector{0 , 0.66})
{

}

Player::~Player()
{

}

DoubleCoordinate &Engine::PointOfView::get_position()
{
    return this->_position;
}

RaycastingVector &Engine::PointOfView::get_direction()
{
    return this->_direction;
}

RaycastingVector &Engine::PointOfView::get_camera_plane()
{
    return this->_camera_plane;
}