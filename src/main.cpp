#include <iostream>
#include "engine/SDLFacade.hpp"
#include "gamelogic/Tile.hpp"
#include "gamelogic/Level.hpp"
#include "gamelogic/Game.hpp"

using GameLogic::Tile;
using GameLogic::Level;
using GameLogic::Player;
using GameLogic::Game;
using std::shared_ptr;

int main()
{
    std::vector<std::vector<int>> world = {
        {1,1,1,1},
        {1,0,0,1},
        {1,0,0,1},
        {1,1,1,1}
    };
    std::vector<std::vector<Tile*>> tiles;

    for(int i = 0; i < world.size(); i++){
        std::vector<Tile*>* vector = new std::vector<Tile*>;
        tiles.push_back(*vector);


        for(int j = 0; j < world.at(i).size(); j++){
            Tile* temp = new Tile();
            temp->set_wall((bool)world[i][j]);
            temp->set_color({255,0,0});
            tiles.at(i).push_back(temp);
        }
    }

    shared_ptr<Level> level { std::make_shared<Level>(Level(tiles)) };
    Player player({2.5,2.5});
    level->set_player(&player);

    Game gaem;
    gaem.set_level(level);
    gaem.run();



    return 0;
}

