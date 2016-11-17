#include "gamelogic/Game.hpp"
#define SDL_main main

using GameLogic::Game;

int main()
{
    Game game;
    game.run();
    return 0;
}
