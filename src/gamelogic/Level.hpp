//
// Created by waseland on 11/7/16.
//

#ifndef MINOR_VIDYA_LEVEL_HPP
#define MINOR_VIDYA_LEVEL_HPP

#include "../WorldObject.hpp"
#include "../TileObject.hpp"
#include "Tile.hpp"
#include "Player.hpp"
#include <vector>

using std::vector;
using Engine::CoordinateDouble;

class Level : public WorldObject {

private:
    vector<vector<Tile*>> _field; //TODO create a typedef for this
    CoordinateDouble _spawnpoint;
    Player* _player; //TODO smart pointers?
    /*
     * WorldParser
     *      ->
     *          field = GetLevel(string levelcode);
     *          tileset = GetLevelTileSet(string levelcode);
     */

public:
    Level(vector<vector<Tile*>> field);

    virtual ~Level();

    void update() override;

    void set_player(Player* player);

    TileObject* get_tile(int x, int y) override;

    CoordinateDouble get_spawnpoint();

    PointOfView& get_pov() override;


};

#endif //MINOR_VIDYA_LEVEL_HPP
