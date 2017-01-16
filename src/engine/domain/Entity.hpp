//
// Created by wouter on 12/12/16.
//

#ifndef MINOR_VIDYA_ENTITY_H
#define MINOR_VIDYA_ENTITY_H

#include "CoordinateDouble.hpp"
#include "../ImageTypes.hpp"
#include "../interface/Updatable.hpp"
#include "../raycasting/AnimatedTexture.hpp"

namespace Engine {
    class Entity : public Updatable {

    public:
        // TODO: Currently an Entity supports one animation, we might want to support multiple animations.
        Entity(AnimatedTexture* animated_texture, CoordinateDouble position);
        virtual ~Entity();

        virtual void update(int delta_time) override;

        CoordinateDouble& get_position();
        ImageBuffer& get_texture();
        int get_texture_width();
        int get_texture_height();

    private:
        CoordinateDouble _position;
        AnimatedTexture* _animated_texture;
    };
}


#endif //MINOR_VIDYA_ENTITY_H
