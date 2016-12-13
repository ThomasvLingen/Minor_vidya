//
// Created by wouter on 12/12/16.
//

#ifndef MINOR_VIDYA_ENTITY_H
#define MINOR_VIDYA_ENTITY_H

#include "../raycasting/RayCastingTypes.hpp"
#include "../ImageTypes.hpp"

namespace Engine {
    class Entity {

    public:
        Entity(ImageBuffer& texture, CoordinateInt position);
        virtual ~Entity();
        CoordinateInt& get_position();
        ImageBuffer& get_texture();

    private:
        CoordinateInt _position;
        ImageBuffer& _texture;
    };
}


#endif //MINOR_VIDYA_ENTITY_H
