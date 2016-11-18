//
// Created by jazula on 11/18/16.
//

#ifndef MINOR_VIDYA_FPSCOUNTER_HPP
#define MINOR_VIDYA_FPSCOUNTER_HPP

#include "interface/Drawable.hpp"
#include "interface/Updatable.hpp"
#include <vector>
#include <string>

namespace Engine {
    using std::vector;
    using std::string;

    class FPScounter : public Drawable, public Updatable {
    public:
        FPScounter(SDLFacade& _SDL_facade);

        virtual void draw() override;

        virtual void update(int delta_time) override;

    private:
        vector<int> _FPS_values;
        int _current_FPS;

        const CoordinateInt _coord = {0,0};
        const Color _color = {255,255,255};
        const FontType _font = FontType::alterebro_pixel;

        void _update_FPS(int delta_time);
        int _avarage_FPS_vector();
        int _calulate_FPS(int delta_time);

        string _get_FPS_string();
    };
}
#endif //MINOR_VIDYA_FPSCOUNTER_HPP
