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
#include "ImageTypes.hpp"
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


    enum class FontType {alterebro_pixel, alterebro_pixel_plus, alterebro_pixel_medium, alterebro_pixel_small};

    class SDLFacade {
    private:
        Input _input;

        map<FontType, TTF_Font*> _fonts;
        
        map<string, SDL_Texture*> _images;
        
        map<Key, SDL_Keycode > _possible_keys = {
            {Key::A,            SDLK_a},
            {Key::B,            SDLK_b},
            {Key::C,            SDLK_c},
            {Key::D,            SDLK_d},
            {Key::E,            SDLK_e},
            {Key::F,            SDLK_f},
            {Key::G,            SDLK_g},
            {Key::H,            SDLK_h},
            {Key::I,            SDLK_i},
            {Key::J,            SDLK_j},
            {Key::K,            SDLK_k},
            {Key::L,            SDLK_l},
            {Key::M,            SDLK_m},
            {Key::N,            SDLK_n},
            {Key::O,            SDLK_o},
            {Key::P,            SDLK_p},
            {Key::Q,            SDLK_q},
            {Key::R,            SDLK_r},
            {Key::S,            SDLK_s},
            {Key::T,            SDLK_t},
            {Key::U,            SDLK_u},
            {Key::V,            SDLK_v},
            {Key::W,            SDLK_w},
            {Key::X,            SDLK_x},
            {Key::Y,            SDLK_y},
            {Key::Z,            SDLK_z},
            {Key::NUMBER_0,     SDLK_0},
            {Key::NUMBER_1,     SDLK_1},
            {Key::NUMBER_2,     SDLK_2},
            {Key::NUMBER_3,     SDLK_3},
            {Key::NUMBER_4,     SDLK_4},
            {Key::NUMBER_5,     SDLK_5},
            {Key::NUMBER_6,     SDLK_6},
            {Key::NUMBER_7,     SDLK_7},
            {Key::NUMBER_8,     SDLK_8},
            {Key::NUMBER_9,     SDLK_9},
            {Key::ESC,          SDLK_ESCAPE},
            {Key::ENTER,        SDLK_RETURN},
            {Key::SPACE,        SDLK_SPACE},
            {Key::TAB,          SDLK_TAB},
            {Key::ARROW_UP,     SDLK_UP},
            {Key::ARROW_DOWN,   SDLK_DOWN},
            {Key::ARROW_LEFT,   SDLK_LEFT},
            {Key::ARROW_RIGHT,  SDLK_RIGHT}
        };

        SDL_Window* _window = nullptr;
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

        Input get_input() const;
        void handle_sdl_events();

        void clear_screen(); //draws the background
        void draw_line(const CoordinateInt& line_start, const CoordinateInt& line_end, const Color& color);
        bool draw_text(const string& text, const FontType& font, const Color& color,
                       const CoordinateInt& position) const;
        void draw_image(const std::string path, const CoordinateInt& coordinates);
        void draw_rect(const CoordinateInt& rect_start, const int width, const int height, const Color& color);
        void update_screen_buffer();
        void render_buffer() const;

        int get_image_width(const std::string path);

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
        void load_sound_effect(const string name, const string path);
        void play_sound_effect(const string name);
        void stop_music();

        TextureMap get_tileset_buffers(const string path, const int tile_width, const int tile_height, const int amount_of_tiles);
        vector<ImageBuffer*> load_animation(const string path, const size_t row, const size_t width, const size_t height, const size_t animation_frames);
        ImageBuffer* load_image_buffer(const string path);

    private:
        void _handle_key_pressed_event(SDL_Keycode key);
        void _handle_key_released_event(SDL_Keycode key);
        void _handle_window_event(SDL_Event* event);

        bool _is_image_in_map(string path);
        void _add_image_in_map(string path);

        bool _init_window();
        bool _init_renderer();
        bool _init_screen_buffer();
        bool _init_fonts();
        bool _load_font(const string& path, const FontType& font_type, uint8_t size);
        ImageBuffer* get_image_buffer(SDL_Surface* tileset, const CoordinateInt& position, const int tile_width, const int tile_height);

        string _get_absolute_path(const string path);

        static constexpr int _frequency = 44100;
        static constexpr Uint16 _audio_format = MIX_DEFAULT_FORMAT;
        static constexpr int _channels = 2;
        static constexpr int _chunksize = 1024;
        static constexpr int _fade_in_time = 750;
        static constexpr int _loop_forever = -1;
        static constexpr int _play_once = 0;
        static constexpr int _next_available_channel = -1;

        map<const string, Mix_Chunk*> _sound_effects;
        Mix_Music* _music = NULL;
        Mix_Chunk* _sound_effect = NULL;
    };
}


#endif //MINOR_VIDYA_SDLFACADE_HPP
