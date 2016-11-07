//
// Created by martijn on 11/1/16.
//

#ifndef MINOR_VIDYA_SDLFACADE_HPP
#define MINOR_VIDYA_SDLFACADE_HPP

#include <string>
#include <iostream>
#include <map>
#include <vector>

#include "Color.hpp"
#include "RayCastingTypes.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using std::string;
using std::map;
using std::vector;
using std::cout;
using std::endl;
using Engine::CoordinateDouble;


enum FontType {verdana, roman, alterebro_pixel};
enum Key {W, A, S, D};

typedef std::vector<Key> PressedKeys;

class SDLFacade {

    private:
        PressedKeys _keys_down;

        map<FontType, TTF_Font *> _fonts;
        map<SDL_Keycode, Key> _possible_keys;
        SDL_Window* _window = nullptr;
        SDL_Surface* _screenSurface = nullptr;
        SDL_Renderer* _renderer = nullptr;

    public:
        SDLFacade();

        virtual ~SDLFacade();

        bool init();

        void clear_screen(); //draws the background

        void draw_line(const CoordinateDouble &position1, const CoordinateDouble &position2, const Color &color);

        void render_buffer() const;

        void handle_sdl_events();

        PressedKeys get_keys() const;

        bool draw_text(const string &text, const FontType &font, const Color &color, const CoordinateDouble &position) const;

        void set_height(const int &screen_height, const int &screen_width);

        int get_height() const;

        void set_width(const int &screen_height, const int &screen_width);

        int get_width() const;

    private:
        void _handle_quit_event();
        void _handle_key_event();
        bool _init_window();
        bool _init_renderer();
        bool _init_fonts();
        bool _load_font(const string &path, const FontType &font_type, uint8_t size);

};

#endif //MINOR_VIDYA_SDLFACADE_HPP
