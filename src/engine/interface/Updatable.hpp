//
// Created by jazula on 11/18/16.
//

#ifndef MINOR_VIDYA_UPDATABLE_HPP
#define MINOR_VIDYA_UPDATABLE_HPP

namespace Engine {
    class Updatable {
    public:
        virtual void update(int delta_time) = 0;
    };
}

#endif //MINOR_VIDYA_UPDATABLE_HPP
