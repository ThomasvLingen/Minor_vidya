//
// Created by martijn on 11/1/16.
//

#include "SDLFacade.hpp"

SDLFacade::SDLFacade(const function<void()>& callback_func )
: _quit_callback(callback_func)
{

}

SDLFacade::~SDLFacade() {
    //todo
    SDL_DestroyWindow(_window);
    SDL_FreeSurface(_screenSurface);
    SDL_DestroyRenderer(_renderer);

    for(auto font : this->_fonts){
        TTF_CloseFont(font.second);
    }
}

bool SDLFacade::init() {

    // Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING < 0)) {
        //std::cout <<  "Something went wrong while initting: " + SDL_GetError() << std::endl;
        return false;
    }

    // Init SDL_TTF
    if (TTF_Init() < 0) {
        //std::cout << "Something went wrong while initting SDL_TTF!" + TTF_GetError() << std::endl;
    };

    // Init window
    //std::cout << "initializing window" << std::endl;
    if (!this->_init_window()) {
        return false;
    }

    //std::cout << "initializing renderer" << std::endl;
    if (!this->_init_renderer()) {
        return false;
    }

    if (!this->_init_fonts()) {
        std::cout << "Your fonts could not be initted" << std::endl;
        return false;
    }

    //std::cout << "initialization done" << std::endl;
    return true;
}

bool SDLFacade::_init_renderer()
{
    // Attempt to make a software renderer
    this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_SOFTWARE);
    if (this->_renderer != nullptr) {
        //std::cout << "Warning: could not use hardware acceleration --> SDL_Renderer uses software rendering" << std::endl;
        return true;
    } else {
        //std::cout << "Something went wrong while making a renderer! : " + SDL_GetError() << std::endl;
        SDL_DestroyRenderer(_renderer);
        return false;
    }
}

bool SDLFacade::_init_window() {
    _window = SDL_CreateWindow("Vidya game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500,
                              500, SDL_WINDOW_SHOWN);
    if(_window != nullptr) {
        _screenSurface = SDL_GetWindowSurface(_window);
        return true;
    } else {
        //std::cout << "Something went wrong while making a window! : " + SDL_GetError() << std::endl;
        SDL_DestroyWindow(_window);
        return false;
    }
}

void SDLFacade::clear_screen() {
    // Draw background
    SDL_FillRect(_screenSurface, NULL, SDL_MapRGB(_screenSurface->format, 0x00, 0x00, 0x00));
}

void SDLFacade::draw_line(const CoordinateDouble &position1, const CoordinateDouble &position2, const Color &color) {

    SDL_SetRenderDrawColor(_renderer, color.r_value, color.g_value, color.b_value, 255);
    SDL_RenderDrawLine(_renderer, position1.x, position1.y, position2.x, position2.y);

}

void SDLFacade::render_buffer() const {
    //todo
    // Update window surface
    SDL_UpdateWindowSurface(_window);
}

void SDLFacade::handle_sdl_events() {
    SDL_Event event;

    while(SDL_PollEvent(&event) != 0){
        switch(event.type){
            case SDL_KEYDOWN:
                _handle_key_pressed_event(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                _handle_key_released_event(event.key.keysym.sym);
                break;
            case SDL_QUIT:
                _quit_callback();
                break;
            case SDL_WINDOWEVENT:
                _handle_window_event(&event);
                break;
            default:
                break;
        }
    }
}

PressedKeys SDLFacade::get_keys() const {
    //todo
    return this->_keys_down;
}

bool SDLFacade::draw_text(const string &text, const FontType &font, const Color &color, const CoordinateDouble &position) const {
    SDL_Color render_color = { color.r_value, color.g_value, color.b_value, 255 };
    TTF_Font* render_font = nullptr;
    SDL_Surface* text_surface = nullptr;
    SDL_Texture* text_texture = nullptr;

    try{
        render_font = _fonts.at(font);

        text_surface = TTF_RenderText_Solid(render_font, text.c_str(), render_color);
        text_texture = SDL_CreateTextureFromSurface(_renderer, text_surface);
        SDL_Rect text_rect;
        text_rect.x = position.x;
        text_rect.y = position.y;
        text_rect.w = text_surface->w;
        text_rect.h = text_surface->h;

        SDL_RenderCopy(this->_renderer, text_texture, nullptr, &text_rect);
        SDL_FreeSurface(text_surface);

        return true;
    } catch (int exception){
        TTF_CloseFont(render_font);
        SDL_FreeSurface(text_surface);
        SDL_DestroyTexture(text_texture);
        return false;
    }
}

void SDLFacade::set_height(const int &screen_height) {
    this->_height = screen_height;
}

int SDLFacade::get_height() const {
    return this->_height;
}

void SDLFacade::set_width(const int &screen_width) {
    this->_width = screen_width;
}

int SDLFacade::get_width() const {
    return this->_width;
}

bool SDLFacade::_init_fonts(){
    if(!_load_font("res/alterebro_pixel.ttf", FontType::alterebro_pixel, 30)){
        return false;
    }

    return true;
}

bool SDLFacade::_load_font(const string &path, const FontType &font_type, uint8_t size) {
    TTF_Font* new_font = TTF_OpenFont(path.c_str(), size);

    if (new_font == nullptr) {
        cout << "Could not open " << path << " " << TTF_GetError() << endl;
        return false;
    } else {
        _fonts[font_type] = new_font;
        return true;
    }
}

void SDLFacade::_handle_key_pressed_event(SDL_Keycode key) {
    map<SDL_Keycode, Key>::iterator it;
    it = this->_possible_keys.find(key);

    // Check if SDL_Keycode needs to be handled
    if(it != this->_possible_keys.end()){
        vector<Key>::iterator it_pressed;
        it_pressed = find(this->_keys_down.begin(), this->_keys_down.end(), it->second);

        if(it_pressed == _keys_down.end()){
            this->_keys_down.push_back(it->second);
        }
    }
}

void SDLFacade::_handle_key_released_event(SDL_Keycode key) {
    map<SDL_Keycode, Key>::iterator it_possible;
    it_possible = _possible_keys.find(key);

    // Check if SDL_Keycode needs to be handled
    if(it_possible != _possible_keys.end()){
        vector<Key>::iterator it_down;
        it_down = find(this->_keys_down.begin(), this->_keys_down.end(), it_possible->second);

        // Check if released key is in _keys_down
        if(it_down != _keys_down.end()){
            _keys_down.erase(it_down);
        }
    }
}

void SDLFacade::_handle_window_event(SDL_Event* event){
    switch(event->window.event){
        case SDL_WINDOWEVENT_RESIZED:
            this->_width = event->window.data1;
            this->_height = event->window.data2;
            break;
        default:
            break;
    }
}