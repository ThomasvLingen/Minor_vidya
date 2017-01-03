//
// Created by sander on 11/17/16.
//

#ifndef MINOR_VIDYA_LOADSTATE_HPP
#define MINOR_VIDYA_LOADSTATE_HPP

#include <string>
#include <vector>
#include <utility>
#include "IGameState.hpp"
#include "../Game.hpp"
#include "../../engine/SDLFacade.hpp"
#include "../../engine/PathUtil.hpp"
#include "../../engine/raycasting/RayCastingTypes.hpp"
#include "../../config.hpp"

namespace GameLogic {
    class Game;
}

namespace State {
    using Engine::SDLFacade;
    using Engine::CoordinateDouble;
    using Engine::Color;
    using Engine::FontType;
    using Engine::Keys;
    using Engine::Key;
    using GameLogic::Game;
    using GameLogic::CampaignMap;
    using std::string;
    using std::vector;
    using Engine::CoordinateInt;
    using std::pair;

    class LoadState : public IGameState {

    public:
        LoadState(Game& context, CampaignMap& map_to_load);
        void update(int time_since_last_update) override ;

    private:
        CampaignMap& map_to_load;

        int _loading_screen_time = 0;
        Color _color{255,255,255};

        FontType _load_font{FontType::alterebro_pixel_plus};
        string _load_text {"Loading..."};
        CoordinateInt _load_text_pos {255,50};

        FontType _text_font{FontType::alterebro_pixel};
        vector<pair<string,string>> _text_image {
            {"Finding Files...", "res/loading_bar/loading_bar_1.bmp"},
            {"Casting Rays...", "res/loading_bar/loading_bar_2.bmp"},
            {"Calculating Edges...", "res/loading_bar/loading_bar_3.bmp"},
            {"Doing other stuff...", "res/loading_bar/loading_bar_4.bmp"},
            {"Placing Player...", "res/loading_bar/loading_bar_5.bmp"},
            {"Increasing movement speed...", "res/loading_bar/loading_bar_6.bmp"},
            {"Making textures...", "res/loading_bar/loading_bar_7.bmp"},
            {"Destroying textures...", "res/loading_bar/loading_bar_6.bmp"},
            {"Overloading!!!", "res/loading_bar/loading_bar_8.bmp"},
            {"Done Loading!", "res/loading_bar/loading_bar_8.bmp"}
        };
        CoordinateInt _text_pos {220,160};
        CoordinateInt _loading_bar_pos {220, 120};

        CoordinateInt _advertisement_pos {320, 300};

        int _current_index {0};
        int _wait_time {30};
    };
}
#endif //MINOR_VIDYA_LOADSTATE_HPP
