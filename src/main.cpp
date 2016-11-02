#include "SDLFacade.hpp"

using Engine::CoordinateDouble;

int main()
{
    std::cout << "Hello world" << std::endl;

    SDLFacade sdlFacade = SDLFacade();
    if(sdlFacade.init()){
        std::cout << "Start" << std::endl;
        Color* color = new Color();
        while(true) {
            sdlFacade.clear_screen();
            CoordinateDouble position1 = CoordinateDouble();
            position1.x = 0;
            position1.y = 0;
            CoordinateDouble position2 = CoordinateDouble();
            position2.x = 200;
            position2.y = 500;
            Color color = Color();
            color.r_value = 70;
            color.g_value = 180;
            color.b_value = 20;
            sdlFacade.draw_line(position1, position2, color);

            Color text_color = Color();
            text_color.r_value = 260;
            text_color.g_value = 100;
            text_color.b_value = 300;

            CoordinateDouble text_position = CoordinateDouble();
            text_position.x = 20;
            text_position.y = 40;

            sdlFacade.draw_text("Dit is de fps counter", blue_highway_rg, text_color,text_position);
            sdlFacade.render_buffer();
            SDL_Delay(1000);
        }
    } else {
        std::cout << "Failed" << std::endl;
    }
    std::cin;

    return 0;
}

