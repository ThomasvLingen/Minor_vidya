#ifndef WORLDOBJECT_HPP
#define WORLDOBJECT_HPP

#include "TileObject.hpp"
#include "PointOfView.hpp"
#include "../KeyStrokes.hpp"
#include "../AssetsManager.hpp"

namespace Engine {
    using Engine::PointOfView;
    class World {

    public:
        World(SPTR_AssetsManager assets);                            // We now have to explicitly declare this since other def constructors are deleted
        World(const World& obj) = delete;            // Copy constructor for a base class has to be deleted (slicing)
        World& operator=(const World& obj) = delete; // Copy assignment for a base class has to be deleted (slicing)

        SPTR_AssetsManager assets;

        virtual void update(int delta_time) = 0;

        virtual PointOfView& get_pov() = 0;
        virtual TileObject* get_tile(int x, int y) = 0; //TODO: int x/y too coordinate double?
        virtual void handle_input(PressedKeys keys) = 0;

    };
}

#endif // !WORLDOBJECT_HPP