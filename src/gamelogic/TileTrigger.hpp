//
// Created by waseland on 12/12/16.
//

#ifndef MINOR_VIDYA_TILETRIGGER_HPP
#define MINOR_VIDYA_TILETRIGGER_HPP

#include <functional>

namespace GameLogic {

    using std::function;

    class Level;

    class TileTrigger {

    public:
        TileTrigger(function<void(Level&)> event);
        virtual ~TileTrigger();
        void make_call(Level& world);

    private:
        function<void(Level&)> _event;
    };
}


#endif //MINOR_VIDYA_TILETRIGGER_HPP
