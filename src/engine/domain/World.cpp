//
// Created by mafn on 11/21/16.
//

#include "../SDLFacade.hpp"
#include "World.hpp"

namespace Engine {
    World::World(SPTR_AssetsManager assets)
    : assets(assets)
    {
    }

    vector<Entity*>& World::get_entities()
    {
        return this->_entities;
    }

    void World::add_entity( Entity entity )
    {
        this->_entities.push_back(new Entity(entity));
    }
}