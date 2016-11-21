//
// Created by mafn on 11/21/16.
//

#include "../SDLFacade.hpp"
#include "WorldObject.hpp"

namespace Engine {
    WorldObject::WorldObject(AssetsManager* assets)
    : assets(assets)
    {
        if (!this->assets->init()) {
            cout << "AssetsManager has not initted correctly." << endl;
        }
    }

    WorldObject::~WorldObject()
    {
        delete this->assets;
    }
}