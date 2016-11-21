//
// Created by jazula on 11/21/16.
//

#ifndef MINOR_VIDYA_COLLECTION_HPP
#define MINOR_VIDYA_COLLECTION_HPP

#include "Drawable.hpp"
#include "Handleable.hpp"
#include "Updatable.hpp"
#include <vector>

namespace Engine {
    using std::vector;

    class Collection {
    public:
        void draw();
        void handle_input(PressedKeys& keys);
        void update(int delta_time);

        void add_drawable(Drawable* to_add);
        void add_handleable(Handleable* to_add);
        void add_updatable(Updatable* to_add);

    private:
        vector<Drawable*> _drawables;
        vector<Handleable*> _handleables;
        vector<Updatable*> _updatables;
    };
}


#endif //MINOR_VIDYA_COLLECTION_HPP
