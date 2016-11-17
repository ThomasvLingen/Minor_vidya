//
// Created by sander on 11/17/16.
//

#ifndef MINOR_VIDYA_IDRAWABLE_HPP
#define MINOR_VIDYA_IDRAWABLE_HPP

namespace Engine;

class IDrawable {

        public:
        IDrawable();
        ~IDrawable();

        virtual void draw() = 0;     // pure virtual func

};
#endif //MINOR_VIDYA_IDRAWABLE_HPP
