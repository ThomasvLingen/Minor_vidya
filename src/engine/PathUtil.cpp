//
// Created by mafn on 11/29/16.
//

#include <SDL2/SDL.h>
#include "PathUtil.hpp"

namespace Engine {

    bool PathUtil::_initialised = false;
    string PathUtil::_run_path = "";

    void PathUtil::_init_run_path()
    {
        char* SDL_base_path = SDL_GetBasePath();
        PathUtil::_run_path = string(SDL_base_path);
        SDL_free(SDL_base_path);
    }

    string PathUtil::get_run_path()
    {
        if (!PathUtil::_initialised) {
            PathUtil::_init_run_path();
        }

        return PathUtil::_run_path;
    }
}
