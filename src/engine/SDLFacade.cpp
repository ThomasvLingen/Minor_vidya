//
// Created by martijn on 11/1/16.
//

#include "SDLFacade.hpp"

namespace Engine {

    /// \brief Constructor of the class
    ///
    /// The given callback function will be saved. This function will be called on Quit-event
    /// \param callback_func The function that needs to be called on quit
    SDLFacade::SDLFacade(const function<void()>& callback_func )
    : _quit_callback(callback_func)
    {

    }

    /// \brief Destructor of the class
    SDLFacade::~SDLFacade()
    {
        SDL_FreeSurface(this->_screenSurface);
        SDL_DestroyRenderer(this->_renderer);
        SDL_DestroyWindow(this->_window);

        for (auto font : this->_fonts) {
            TTF_CloseFont(font.second);
        }

        SDL_Quit();
    }

    /// \brief Initialiser for all class instance variables
    ///
    /// This method will initialize:
    /// * SDL
    /// * TTF
    ///
    /// This method calls the following functions:
    /// * _init_window()
    /// * _init_renderer()
    /// * _init_fonts()
    ///
    /// \return This function returns True if everything was successfully initialized, ohterwise it returns False
    bool SDLFacade::init()
    {
        // Init SDL
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
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

    /// \brief Initialiser for the _renderer (SDL_Renderer)
    ///
    /// \return This function returns True if the _renderer was successfully initialized, ohterwise it returns False
    bool SDLFacade::_init_renderer()
    {
        // Attempt to make a software renderer
        this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_SOFTWARE);
        if (this->_renderer != nullptr) {
            //std::cout << "Warning: could not use hardware acceleration --> SDL_Renderer uses software rendering" << std::endl;
            return true;
        } else {
            //std::cout << "Something went wrong while making a renderer! : " + SDL_GetError() << std::endl;
            SDL_DestroyRenderer(this->_renderer);
            return false;
        }
    }

    /// \brief Initialiser for the _window (SDL_Window)
    ///
    /// \return This function returns True if the _window was successfully initialized, ohterwise it returns False
    bool SDLFacade::_init_window()
    {
        this->_window = SDL_CreateWindow("Vidya game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500,
                                   500, SDL_WINDOW_SHOWN);
        if (this->_window != nullptr) {
            this->_screenSurface = SDL_GetWindowSurface(this->_window);
            return true;
        } else {
            //std::cout << "Something went wrong while making a window! : " + SDL_GetError() << std::endl;
            SDL_DestroyWindow(this->_window);
            return false;
        }
    }

    /// \brief Draws a rectangle on the whole screen
    void SDLFacade::clear_screen()
    {
        // Draw background
        SDL_FillRect(_screenSurface, NULL, SDL_MapRGB(_screenSurface->format, 0x00, 0x00, 0x00));
    }

    /// \brief Draws a line
    ///
    /// A line will be drawn between the given coordinates. The color is set first, secondly the line is being drawn.
    ///
    /// \param line_start The first coordinate
    /// \param line_end The second coordinate
    /// \param color The color of the line. The color class comes from the engine
    void SDLFacade::draw_line(const CoordinateDouble& line_start, const CoordinateDouble& line_end, const Color& color)
    {
        SDL_SetRenderDrawColor(this->_renderer, color.r_value, color.g_value, color.b_value, 255);
        SDL_RenderDrawLine(this->_renderer, line_start.x, line_start.y, line_end.x, line_end.y);
    }

    /// \brief Updates the window
    void SDLFacade::render_buffer() const
    {
        // Update window surface
        SDL_UpdateWindowSurface(this->_window);
    }

    /// \brief Function that handles all relevant SDL_Event types
    ///
    /// Currently the function support the following event types:
    /// * KeyEvents
    /// * QuitEvent
    /// * WindowEvents
    ///     - Resize
    /// Each supported event type has its own handler (or callback)
    void SDLFacade::handle_sdl_events()
    {
        SDL_Event event;

        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    this->_handle_key_pressed_event(event.key.keysym.sym);
                    break;
                case SDL_KEYUP:
                    this->_handle_key_released_event(event.key.keysym.sym);
                    break;
                case SDL_QUIT:
                    this->_quit_callback();
                    break;
                case SDL_WINDOWEVENT:
                    this->_handle_window_event(&event);
                    break;
                default:
                    break;
            }
        }
    }

    PressedKeys SDLFacade::get_keys() const
    {
        //todo
        return this->_keys_down;
    }

    /// \brief Draws text
    ///
    /// This method will draw the given text in the desired color and font on the given coordinate
    ///
    /// \param text The text that needs to be drawn
    /// \param font The font in which the text needs to be drawn
    /// \param color The color in which the text needs to be drawn
    /// \param position The coordinate at which the text will be drawn
    ///
    /// \return This function returns True if text is successfully drawn, ohterwise it returns False
    bool SDLFacade::draw_text(const string& text, const FontType& font, const Color& color,
                              const CoordinateDouble& position) const
    {
        SDL_Color render_color = { color.r_value, color.g_value, color.b_value, 255 };
        TTF_Font* render_font = nullptr;
        SDL_Surface* text_surface = nullptr;
        SDL_Texture* text_texture = nullptr;

        try {
            render_font = this->_fonts.at(font);

            text_surface = TTF_RenderText_Solid(render_font, text.c_str(), render_color);
            text_texture = SDL_CreateTextureFromSurface(this->_renderer, text_surface);
            SDL_Rect text_rect;
            text_rect.x = position.x;
            text_rect.y = position.y;
            text_rect.w = text_surface->w;
            text_rect.h = text_surface->h;

            SDL_RenderCopy(this->_renderer, text_texture, nullptr, &text_rect);
            SDL_FreeSurface(text_surface);

            return true;
        } catch (int exception) {
            TTF_CloseFont(render_font);
            SDL_FreeSurface(text_surface);
            SDL_DestroyTexture(text_texture);
            return false;
        }
    }

    void SDLFacade::set_height(const int& screen_height)
    {
        this->_height = screen_height;
    }

    int SDLFacade::get_height() const
    {
        return this->_height;
    }

    void SDLFacade::set_width(const int& screen_width)
    {
        this->_width = screen_width;
    }

    int SDLFacade::get_width() const
    {
        return this->_width;
    }

    /// \brief Initialiser for all fonts
    ///
    /// \return This function returns True if all fonts are successfully initialised, ohterwise it returns False
    bool SDLFacade::_init_fonts()
    {
        //todo Needs to be expanded later on
        return _load_font("res/alterebro_pixel.ttf", FontType::alterebro_pixel, 30);
    }

    /// \brief Initialiser for one font
    ///
    /// \param path The path where the font is located
    /// \param font_type The enum which will be linked to the loaded font
    /// \param size The desired fontsize
    ///
    /// \return This function returns True if the font is successfully initialized, ohterwise it returns False
    bool SDLFacade::_load_font(const string& path, const FontType& font_type, uint8_t size)
    {
        TTF_Font* new_font = TTF_OpenFont(path.c_str(), size);

        if (new_font == nullptr) {
            cout << "Could not open " << path << " " << TTF_GetError() << endl;
            return false;
        } else {
            this->_fonts[font_type] = new_font;
            return true;
        }
    }

    /// \brief Function that handles a SDL_KEYDOWN event
    ///
    /// Supported keys will be handled and, if not already present, added to the _keys_down vector.
    void SDLFacade::_handle_key_pressed_event(SDL_Keycode key)
    {
        map<SDL_Keycode, Key>::iterator it;
        it = this->_possible_keys.find(key);

        // Check if SDL_Keycode needs to be handled
        if (it != this->_possible_keys.end()) {
            vector<Key>::iterator it_pressed;
            it_pressed = find(this->_keys_down.begin(), this->_keys_down.end(), it->second);

            if (it_pressed == _keys_down.end()) {
                this->_keys_down.push_back(it->second);
            }
        }
    }

    /// \brief Function that handles a SDL_KEYUP event
    ///
    /// Supported keys will be handled and, if present, removed from the _keys_down vector.
    void SDLFacade::_handle_key_released_event(SDL_Keycode key)
    {
        map<SDL_Keycode, Key>::iterator it_possible;
        it_possible = this->_possible_keys.find(key);

        // Check if SDL_Keycode needs to be handled
        if (it_possible != this->_possible_keys.end()) {
            vector<Key>::iterator it_down;
            it_down = find(this->_keys_down.begin(), this->_keys_down.end(), it_possible->second);

            // Check if released key is in _keys_down
            if (it_down != this->_keys_down.end()) {
                this->_keys_down.erase(it_down);
            }
        }
    }

    /// \brief Function that handles a SDL_WINDOWEVENT event
    ///
    /// Currently only handles SDL_WINDOWEVENT_RESIZED, setting the new width and height of the window.
    void SDLFacade::_handle_window_event(SDL_Event* event)
    {
        switch (event->window.event) {
            case SDL_WINDOWEVENT_RESIZED:
                this->_width = event->window.data1;
                this->_height = event->window.data2;
                break;
            default:
                break;
        }
    }

    int SDLFacade::get_ticks() const
    {
        return SDL_GetTicks();
    }

    void SDLFacade::delay_millis(const int millis) const
    {
        SDL_Delay((uint32_t)millis);
    }
}