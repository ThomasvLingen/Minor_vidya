//
// Created by waseland on 11/7/16.
//

#ifndef MINOR_VIDYA_PLAYER_HPP
#define MINOR_VIDYA_PLAYER_HPP


#include "../PointOfView.hpp"
#include "../DoubleCoordinate.hpp"
#include "../RaycastingVector.hpp"

using namespace Engine;

class Player : public PointOfView{

public:
    Player(DoubleCoordinate position);
    virtual ~Player();

    DoubleCoordinate& get_position();
    RaycastingVector& get_direction();
    RaycastingVector& get_camera_plane();

private:
    DoubleCoordinate _position;
    RaycastingVector _direction;
    RaycastingVector _camera_plane;

    /*
     * int health
     * obj Inventory -> vector<items>
     * GrabItem();
     * PlaceItem();
     *
     */

};


#endif //MINOR_VIDYA_PLAYER_HPP
