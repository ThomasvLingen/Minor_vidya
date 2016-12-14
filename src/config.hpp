//
// Created by mafn on 11/18/16.
//

#ifndef MINOR_VIDYA_CONFIG_HPP
#define MINOR_VIDYA_CONFIG_HPP

#include <string>

namespace Config {
    using std::string;

    const int FPS = 60;
    const int FRAME_DURATION = 1000/FPS;

    const string GAME_WINDOW_TITLE = "Vidya Gaem";
    const string LOAD_AD_PATH = "res/advertisement.bmp";


    // Warning: This not only triggers the use of VSYNC but also the use of hardware rendering.
    const bool USE_VSYNC = true; // TODO: We probably want to make this editable through some settings menu
}

#endif //MINOR_VIDYA_CONFIG_HPP
