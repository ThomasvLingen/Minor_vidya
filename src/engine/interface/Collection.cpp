//
// Created by jazula on 11/21/16.
//

#include "Collection.hpp"

namespace Engine {

    void Collection::draw()
    {
        for (auto& drawable : this->_drawables) {
            drawable.draw();
        }
    }

    void Collection::handle_input(::Engine::PressedKeys& keys)
    {
        for (auto& handleable : this->_handleables) {
            handleable.handle_input(keys);
        }
    }

    void Collection::update(int delta_time)
    {
        for (auto& updatable : this->_updatables) {
            updatable.update(delta_time);
        }
    }

    void Collection::add_drawable(Engine::Drawable& to_add)
    {
        this->_drawables.push_back(to_add);
    }

    void Collection::add_handleable(Engine::Handleable& to_add)
    {
        this->_handleables.push_back(to_add);
    }

    void Collection::add_updatable(Engine::Updatable& to_add)
    {
        this->_updatables.push_back(to_add);
    }
}
