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
        CoordinateInt& get_position();
        ImageBuffer& get_image_buffer();

    private:
        CoordinateInt* _position;
        ImageBuffer* _image_buffer;
    };
}


#endif //MINOR_VIDYA_ENTITY_H
