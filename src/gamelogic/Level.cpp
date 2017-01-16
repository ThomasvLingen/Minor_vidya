//
// Created by waseland on 11/7/16.
//

#include "Level.hpp"
#include "Player.hpp"

namespace GameLogic {

    using std::vector;

    Level::Level(Player& player, TileMap field, CoordinateDouble spawnpoint, Engine::SPTR_AssetsManager assets)
    : World(assets)
    , _field(field)
    , _spawnpoint(spawnpoint)
    , _player(player)
    , entity_factory(*assets)
    {
    }

    Level::Level(Player& player, Engine::SPTR_AssetsManager assets)
    : World(assets)
    , _player(player)
    , entity_factory(*assets)
    {
    }

    Level::Level(const Level& obj)
    : World(obj.assets)
    , _field(obj._field)
    , _spawnpoint(obj._spawnpoint)
    , _player(obj._player)
    , entity_factory(obj.entity_factory) // This is a copy!
    {
    }

    Level::~Level()
    {
        for (auto row : this->_field) {
            for (Tile* tile : row) {
                delete tile;
            }
        }
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

        for (auto& entity : this->get_entities()) {
            entity->update(delta_time);
        }

        this->_player.update(delta_time);
    }

    CoordinateDouble Level::get_spawnpoint()
    {
        return this->_spawnpoint;
    }

    TileObject* Level::get_tile(CoordinateInt coordinate)
    {
        return this->_field[coordinate.x][coordinate.y];
    }

    Tile* Level::get_tile_in_level(CoordinateInt coordinate)
    {
        return this->_field[coordinate.x][coordinate.y];
    }

    PointOfView& Level::get_pov()
    {
        return this->_player;
    }

    Player& Level::get_player()
    {
        return this->_player;
    }

    void Level::handle_input(Engine::Input keys)
    {
        this->_player.handleInput(keys);
    }

    void Level::set_spawnpoint(CoordinateDouble coordinate)
    {
        this->_spawnpoint = coordinate;
    }

    void Level::set_field( TileMap field)
    {
        this->_field = field;
    }

    TileMap Level::get_field()
    {
        return this->_field;
    }

    void Level::set_level_over()
    {
        this->_level_won = true;
    }

    bool Level::is_level_over()
    {
        return this->_level_won;
    }

    Entity* Level::get_entity(int x, int y)
    {
        for (Entity* entity : this->_entities) {
            CoordinateDouble position = entity->get_position();
            if ((int)position.x == x && (int)position.y == y) {
                return entity;
            }
        }
        return nullptr;
    }

    bool Level::has_entity(int x, int y)
    {
        for (Entity* entity : this->_entities) {
            CoordinateDouble position = entity->get_position();
            if ((int) position.x == x && (int) position.y == y) {
                return true;
            }
        }
        return false;
    }

    void Level::kill_entity(int x, int y)
    {
        for ( auto it = this->_entities.begin(); it != this->_entities.end(); ) {
            CoordinateDouble position = (*it)->get_position();
            if ((int)position.x == x && (int)position.y == y) {
                delete * it;
                it = this->_entities.erase(it);
            } else {
                ++it;
            }
        }
    }

}