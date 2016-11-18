//
// Created by martijn on 11/1/16.
//

#ifndef MINOR_VIDYA_SDLFACADE_HPP
#define MINOR_VIDYA_SDLFACADE_HPP

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <algorithm>

#include "domain/Color.hpp"
#include "raycasting/RayCastingTypes.hpp"
#include "domain/CoordinateDouble.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"


namespace Engine {
    using std::string;
    using std::map;
    using std::vector;
    using std::pair;
    using std::function;
    using std::find;
    using std::cout;
    using std::endl;


    enum FontType {verdana, roman, alterebro_pixel};
    enum Key {W, A, S, D, ESC};

    typedef std::vector<Key> PressedKeys;

    class SDLFacade {
    private:
        PressedKeys _keys_down;

        map<FontType, TTF_Font*> _fonts;

        map<SDL_Keycode, Key> _possible_keys = {
            {SDLK_w, W},
            {SDLK_a, A},
            {SDLK_s, S},
            {SDLK_d, D},
            {SDLK_ESCAPE, ESC}
        };

        SDL_Window* _window = nullptr;
        SDL_Surface* _screenSurface = nullptr;
        SDL_Renderer* _renderer = nullptr;

        int _width;
        int _height;

        function<void()> _quit_callback;

    public:
        SDLFacade(const function<void()>& callback_func);

        virtual ~SDLFacade();

        bool init();

        void clear_screen(); //draws the background

        void draw_line(const CoordinateDouble& line_start, const CoordinateDouble& line_end, const Color& color);

        void render_buffer() const;

        void handle_sdl_events();

        PressedKeys get_keys() const;

        bool draw_text(const string& text, const FontType& font, const Color& color,
                       const CoordinateDouble& position) const;

        void set_height(const int& screen_height);

        int get_height() const;

        void set_width(const int& screen_width);

        int get_width() const;

        int get_ticks() const;

        void delay_millis(const int millis) const;

        vector<Uint32> get_image_buffer(const string& path);

    private:
        void _handle_key_pressed_event(SDL_Keycode key);
        void _handle_key_released_event(SDL_Keycode key);
        void _handle_window_event(SDL_Event* event);

        bool _init_window();
        bool _init_renderer();
        bool _init_fonts();
        bool _load_font(const string& path, const FontType& font_type, uint8_t size);
    };
}


#endif //MINOR_VIDYA_SDLFACADE_HPP
