//
// Created by jazula on 11/18/16.
//

#include "FPScounter.hpp"

namespace Engine {

    FPScounter::FPScounter(SDLFacade& _SDL_facade)
    : Drawable(_SDL_facade)
    {
    }

    void FPScounter::draw()
    {

        CoordinateDouble temp { //todo change this when drawtext takes a coordinate int
            this->_coord.x,
            this->_coord.y
        };
        this->_SDL_facade.draw_text(
            this->_get_FPS_string(),
            this->_font,
            this->_color,
            temp
        );
    }

    void FPScounter::update(int delta_time)
    {
        this->_update_FPS(delta_time);
    }

    void FPScounter::_update_FPS(int delta_time)
    {
        int FPS_this_frame = this->_calulate_FPS(delta_time);

        if(this->_FPS_values.size() >= 30){
            this->_current_FPS = _avarage_FPS_vector();
            this->_FPS_values.clear();
        }

        this->_FPS_values.push_back(FPS_this_frame);
    }

    int FPScounter::_avarage_FPS_vector()
    {
        int total = 0;

        for (auto value : this->_FPS_values){
            total += value;
        }

        return total / (int)this->_FPS_values.size();
    }

    int FPScounter::_calulate_FPS(int delta_time)
    {
        return 1000 / delta_time;
    }

    string FPScounter::_get_FPS_string()
    {
        return std::to_string(this->_current_FPS);
    }

}