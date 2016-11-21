//
// Created by waseland on 11/7/16.
//

#ifndef MINOR_VIDYA_LEVEL_HPP
#define MINOR_VIDYA_LEVEL_HPP

#include "../engine/domain/WorldObject.hpp"
#include "../engine/domain/TileObject.hpp"
#include "Tile.hpp"
#include "../engine/domain/PointOfView.hpp"
#include <vector>
#include <memory>

namespace Engine {
    class AssetsManager;
}

namespace GameLogic {

    using std::vector;
    using Engine::CoordinateDouble;
    using Engine::TileObject;
    using Engine::PointOfView;
    using Engine::AssetsManager;
    using std::shared_ptr;

    class Player;

    class Level : public Engine::WorldObject {

    private:
        vector<vector<Tile*>> _field; //TODO create a typedef for this
        CoordinateDouble _spawnpoint;
        shared_ptr<Player> _player;

        /*
         * WorldParser
         *      ->
         *          field = GetLevel(string levelcode);
         *          tileset = GetLevelTileSet(string levelcode);
         */

    public:
        Level(vector<vector<Tile*>> field, AssetsManager* assets);
        Level(const Level& obj);

        void update(int delta_time) override;

        void set_player(shared_ptr<Player> player);

        TileObject* get_tile(int x, int y) override;

        CoordinateDouble get_spawnpoint();

        PointOfView& get_pov() override;

        void handle_input(Engine::PressedKeys keys) override;
    };

    typedef std::shared_ptr<Level> SPTR_Level;
}

#endif //MINOR_VIDYA_LEVEL_HPP
