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

    World::~World()
    {
        for ( auto entity : this->_entities ) {
            delete entity;
        }
    }

    vector<Entity*>& World::get_entities()
    {
        return this->_entities;
    }
}