
#include "EnemyFactory.hpp"
#include "Soldier.hpp"

namespace GameLogic {

    EnemyFactory::EnemyFactory(AssetsManager& assets)
    : _assets(assets)
    {
        this->register_enemy<Soldier>("soldier");
    }

    Enemy* EnemyFactory::create_enemy(string name, CoordinateDouble position, vector<CoordinateDouble> idle_route )
    {
        // Throws an exception if the name cannot be found
        return this->_map.at(name)(position, idle_route);
    }

    bool EnemyFactory::knows_enemy(string name)
    {
        return this->_map.find(name) != this->_map.end();
    }
}