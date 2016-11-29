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
#include "KeyStrokes.hpp"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"


namespace Engine {
    using std::string;
    using std::map;
    using std::vector;
    using std::pair;
    using std::function;
    using std::find;
    using std::cout;
    using std::endl;


    enum class FontType {alterebro_pixel, alterebro_pixel_plus};
    typedef vector<Uint32> ImageBuffer;
    typedef map<int, ImageBuffer*> TextureMap;

    class SDLFacade {
    private:
        PressedKeys _keys_down;

        map<FontType, TTF_Font*> _fonts;

        map<SDL_Keycode, Key> _possible_keys = {
            {SDLK_w, Key::W},
            {SDLK_a, Key::A},
            {SDLK_s, Key::S},
            {SDLK_d, Key::D},
            {SDLK_e, Key::E},
            {SDLK_q, Key::Q},
            {SDLK_ESCAPE, Key::ESC},
            {SDLK_RETURN, Key::ENTER}
        };

        SDL_Window* _window = nullptr;
        SDL_Surface* _screen_surface = nullptr;
        SDL_Renderer* _renderer = nullptr;
        SDL_Texture* _screen_buffer = nullptr;
        Uint32* _screen_buffer_pixels = nullptr;

        int _width;
        int _height;

        function<void()> _quit_callback;

    public:
        SDLFacade(const function<void()>& callback_func);
        virtual ~SDLFacade();

        bool init();

        PressedKeys get_keys() const;
        void handle_sdl_events();

        void clear_screen(); //draws the background
        void draw_line(const CoordinateInt& line_start, const CoordinateInt& line_end, const Color& color);
        bool draw_text(const string& text, const FontType& font, const Color& color,
                       const CoordinateInt& position) const;
        void draw_image(const std::string path, const CoordinateDouble& coordinates);
        void draw_rect(const CoordinateDouble& rect_start, const int width, const int height, const Color& color);
        void update_screen_buffer();
        void render_buffer() const;

        void lock_screen_buffer();
        void draw_pixel_screen_buffer(const CoordinateInt& position, Uint32 pixel);
        void unlock_screen_buffer();

        void set_height(const int& screen_height);
        void set_width(const int& screen_width);
        int get_height() const;
        int get_width() const;

        void delay_millis(const int millis) const;
        int get_ticks() const;

        void play_music(const string path);
        void play_sound_effect(const string path);
        void stop_music() const;

        TextureMap get_tileset_buffers(const string& path, const int tile_width, const int tile_height, const int amount_of_tiles);

    private:
        void _handle_key_pressed_event(SDL_Keycode key);
        void _handle_key_released_event(SDL_Keycode key);
        void _handle_window_event(SDL_Event* event);

        bool _init_window();
        bool _init_renderer();
        bool _init_screen_buffer();
        bool _init_fonts();
        bool _load_font(const string& path, const FontType& font_type, uint8_t size);
        ImageBuffer* get_image_buffer(SDL_Surface* tileset, const CoordinateInt& position, const int tile_width, const int tile_height);

        const int _frequency = 22050;
        const Uint16 _audio_format = MIX_DEFAULT_FORMAT;
        const int _channels = 2;
        const int _chunksize = 4096;
        Mix_Music* _music = NULL;
        Mix_Chunk* _sound_effect = NULL;
    };
}


#endif //MINOR_VIDYA_SDLFACADE_HPP
