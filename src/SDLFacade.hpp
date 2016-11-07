//
// Created by martijn on 11/1/16.
//

#ifndef MINOR_VIDYA_SDLFACADE_HPP
#define MINOR_VIDYA_SDLFACADE_HPP

#include <string>
#include <map>
#include <vector>
#include <functional>
#include <algorithm>

#include "Color.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

using std::string;
using std::map;
using std::vector;
using std::pair;
using std::function;
using std::find;

enum FontType {verdana, roman};
enum Key {W, A, S, D, ESC};

typedef std::vector<Key> PressedKeys;

class SDLFacade {

    private:
        PressedKeys _keys_down;

        map<FontType, TTF_Font *> _fonts;

        map<SDL_Keycode, Key> _possible_keys = {
                {SDLK_w, W},
                {SDLK_a, A},
                {SDLK_s, S},
                {SDLK_d, D},
                {SDLK_ESCAPE, ESC}
        };

        SDL_Window* window = NULL;
        SDL_Surface* screenSurface = NULL;
        SDL_Renderer* renderer = NULL;

        int _width;
        int _height;

        function<void()> _quit_callback;

    public:
        SDLFacade(const function<void()>& callback_func );

        virtual ~SDLFacade();

        bool init();

        void clear_screen(); //clears the surface

        void draw_line(const double &x1, const double &y1, const double &x2, const double &y2, const Color &color);

        void render_buffer() const;

        void handle_sdl_events();

        PressedKeys get_keys() const;

        void draw_text(string text, FontType font) const;

        void set_height(const int &screen_height);

        int get_height() const;

        void set_width(const int &screen_width);

        int get_width() const;

    private:
        void _handle_key_pressed_event(SDL_Keycode key);
        void _handle_key_released_event(SDL_Keycode key);
        void _handle_window_event(SDL_Event* event);

        bool init_window();
        bool init_renderer();
        void _init_possible_keys();


        uint32_t convert_color_struct();
};

#endif //MINOR_VIDYA_SDLFACADE_HPP
