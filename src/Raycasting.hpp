//
// Created by mafn on 11/1/16.
//

#ifndef MINOR_VIDYA_RAYCASTING_HPP
#define MINOR_VIDYA_RAYCASTING_HPP

#include <cmath>

namespace Engine {
    class Raycasting {
    public:
        Raycasting(/* Either pass a world or create it in the constructor */);
        virtual ~Raycasting();

        void handle_input(/* Input data type from SDL facade */);
        void update(int delta_time);
        void draw();


    private:
        // Reference (of smart pointer) naar een world
        // Reference (of smart pointer) naar de SDLAdapter / facade
    };
}


#endif //MINOR_VIDYA_RAYCASTING_HPP
