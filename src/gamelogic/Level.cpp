//
// Created by waseland on 11/7/16.
//

#include "Level.hpp"
#include "Player.hpp"

namespace GameLogic {

    using std::vector;

    Level::Level(vector<vector<Tile*>> field, AssetsManager* assets)
    : WorldObject(assets)
    , _field(field)
    {
    }

    /// \brief update every tile from this level
    void Level::update(int delta_time)
    {
        for (auto row : this->_field) {
            for (auto tile : row) {
                if (tile != nullptr) {
                    tile->update(delta_time);
                }
            }
        }

        this->_player->update(delta_time);
    }

    CoordinateDouble Level::get_spawnpoint()
    {
        return this->_spawnpoint;
    }

    TileObject* Level::get_tile(int x, int y)
    {
        return _field.at(x).at(y); //TODO: use at or []?
    }

    PointOfView& Level::get_pov()
    {
        return *(this->_player);
    }

    void Level::set_player(shared_ptr<Player> player)
    {
        this->_player = player;
    }

    void Level::handle_input(Engine::PressedKeys keys)
    {
        this->_player->handleInput(keys);
    }

    Level::Level(const Level& obj)
    : WorldObject(obj.assets)
    , _field(obj._field)
    , _spawnpoint(obj._spawnpoint)
    , _player(obj._player)
    {
    }
}