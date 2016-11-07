//
// Created by waseland on 11/7/16.
//

#ifndef MINOR_VIDYA_LEVEL_HPP
#define MINOR_VIDYA_LEVEL_HPP

#include "../WorldObject.hpp"
#include "../TileObject.hpp"
#include "../PointOfView.hpp"
#include "../DoubleCoordinate.hpp"
#include <vector>

using std::vector;
using Engine::PointOfView;
using Engine::DoubleCoordinate;

class Level : public WorldObject{

private:
    vector<vector<TileObject*>> _field;
    PointOfView _point_of_view;
    DoubleCoordinate _spawnpoint;

    /*
     * WorldParser
     *      ->
     *          field = GetLevel(string levelcode);
     *          tileset = GetLevelTileSet(string levelcode);
     */

public:
    Level(vector<vector<TileObject*>> field);
    virtual ~Level();

    void update();

    PointOfView & get_pov();
    TileObject* get_tile(int x, int y);
    DoubleCoordinate get_spawnpoint();


};

#endif //MINOR_VIDYA_LEVEL_HPP
