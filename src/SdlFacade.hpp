//
// Created by martijn on 11/1/16.
//

#ifndef MINOR_VIDYA_SDLFACADE_HPP
#define MINOR_VIDYA_SDLFACADE_HPP

#include <string>
#include <map>
#include <vector>

#include "color.hpp"

using std::string;
using std::map;
using std::vector;


enum FontType {verdana, roman};
enum Key {W, A, S, D};

typedef std::vector<Key> PressedKeys;

class SdlFacade {

    private:
        PressedKeys _keys_down;

        map<FontType, TTF_Font *> _fonts;
        map<SDL_Keycode *, Key> _possible_keys;

    public:
        SdlFacade();

        virtual ~SdlFacade();

        void init();

        void draw_line(double x1, double y1, double x2, double y2, Color color);

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

};

#endif //MINOR_VIDYA_SDLFACADE_HPP
