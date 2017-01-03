//
// Created by mafn on 1/2/17.
//

#include "EntityFactory.hpp"
#include "Soldier.hpp"

namespace GameLogic {

    EntityFactory::EntityFactory(AssetsManager& assets)
    : _assets(assets)
    {
        this->register_entity<Soldier>("soldier");
    }

    Entity* EntityFactory::create_entity(string name, CoordinateDouble position)
    {
        // Throws an exception if the name cannot be found
        return this->_map.at(name)(position);
    }

    bool EntityFactory::knows_entity(string name)
    {
        return this->_map.find(name) != this->_map.end();
    }
}