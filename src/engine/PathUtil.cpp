//
// Created by mafn on 11/29/16.
//

#include <SDL2/SDL.h>
#include "PathUtil.hpp"

namespace Engine {
    string PathUtil::get_run_path()
    {
        static string run_path = "";

        if (run_path == "") {
            char* SDL_base_path = SDL_GetBasePath();
            run_path = string(SDL_base_path);
            SDL_free(SDL_base_path);
        }

        return run_path;
    }
}
