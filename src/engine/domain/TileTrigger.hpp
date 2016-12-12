//
// Created by waseland on 12/12/16.
//

#ifndef MINOR_VIDYA_TILETRIGGER_HPP
#define MINOR_VIDYA_TILETRIGGER_HPP

#include <functional>

using std::function;

namespace Engine {

    class World;

    class TileTrigger {

    public:

        TileTrigger(function<void(World&)> event);
        virtual ~TileTrigger();
        void make_call(World& world);

    private:
        function<void(World&)> _event;

    };
}


#endif //MINOR_VIDYA_TILETRIGGER_HPP
