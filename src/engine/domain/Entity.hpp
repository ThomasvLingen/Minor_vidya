//
// Created by wouter on 12/12/16.
//

#ifndef MINOR_VIDYA_ENTITY_H
#define MINOR_VIDYA_ENTITY_H

#include "CoordinateDouble.hpp"
#include "../ImageTypes.hpp"

namespace Engine {
    class Entity {

    public:
        Entity(ImageBuffer& texture, CoordinateDouble position);
        virtual ~Entity();
        CoordinateDouble& get_position();
        ImageBuffer& get_texture();

    private:
        CoordinateDouble _position;
        ImageBuffer& _texture;
    };
}


#endif //MINOR_VIDYA_ENTITY_H
