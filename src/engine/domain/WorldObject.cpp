//
// Created by mafn on 11/21/16.
//

#include "../SDLFacade.hpp"
#include "WorldObject.hpp"

namespace Engine {
    WorldObject::WorldObject(AssetsManager* assets)
    : assets(assets)
    {
    }

    WorldObject::~WorldObject()
    {
        delete this->assets;
    }
}