#ifndef WORLDOBJECT_HPP
#define WORLDOBJECT_HPP

#include "TileObject.hpp"
#include "PointOfView.hpp"
#include "../KeyStrokes.hpp"

namespace Engine {
    using Engine::PointOfView;
    class WorldObject {

    public:
        virtual void update() = 0;

        virtual PointOfView& get_pov() = 0;
        virtual TileObject* get_tile(int x, int y) = 0; //TODO: int x/y too coordinate double?
        virtual void handle_input(PressedKeys keys) = 0;
    };
}

#endif // !WORLDOBJECT_HPP
