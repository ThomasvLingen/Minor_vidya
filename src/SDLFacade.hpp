//
// Created by martijn on 11/1/16.
//

#ifndef MINOR_VIDYA_SDLFACADE_HPP
#define MINOR_VIDYA_SDLFACADE_HPP

#include <string>
#include <map>
#include <vector>

#include "Color.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

using std::string;
using std::map;
using std::vector;


enum FontType {verdana, roman};
enum Key {W, A, S, D};

typedef std::vector<Key> PressedKeys;

class SDLFacade {

    private:
        PressedKeys _keys_down;

        map<FontType, TTF_Font *> _fonts;
        map<SDL_Keycode, Key> _possible_keys;

    public:
        SDLFacade();

        virtual ~SDLFacade();

        void handle_sdl_events();

        PressedKeys get_keys() const;

        void draw_text(string text, FontType font) const;


    private:
        void _handle_quit_event();
        void _handle_key_event();

};

#endif //MINOR_VIDYA_SDLFACADE_HPP
