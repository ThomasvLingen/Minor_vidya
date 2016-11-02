//
// Created by martijn on 11/1/16.
//

#ifndef MINOR_VIDYA_SDLFACADE_HPP
#define MINOR_VIDYA_SDLFACADE_HPP

#include <string>
#include <map>
#include <vector>

#include "Color.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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
        SDL_Window* window = NULL;
        SDL_Surface* screenSurface = NULL;
        SDL_Renderer* renderer = NULL;

    public:
        SDLFacade();

        virtual ~SDLFacade();

        bool init();

        void clear_screen(); //clears the surface

        void draw_line(const double &x1, const double &y1, const double &x2, const double &y2, const Color &color);

        void render_buffer() const;

        void handle_sdl_events();

        PressedKeys get_keys() const;

        void draw_text(string text, FontType font) const;

        void set_height(const int &screen_height, const int &screen_width);

        int get_height() const;

        void set_width(const int &screen_height, const int &screen_width);

        int get_width() const;

    private:
        void _handle_quit_event();
        void _handle_key_event();
        bool init_window();
        bool init_renderer();

};

#endif //MINOR_VIDYA_SDLFACADE_HPP
