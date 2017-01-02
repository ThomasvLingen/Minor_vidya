//
// Created by mafn on 1/2/17.
//

#ifndef MINOR_VIDYA_ENTITYFACTORY_HPP
#define MINOR_VIDYA_ENTITYFACTORY_HPP

#include <functional>

#include "../../engine/domain/Entity.hpp"
#include "../../engine/AssetsManager.hpp"
#include "../../engine/domain/CoordinateDouble.hpp"

namespace GameLogic {

    using std::function;
    using std::string;
    using std::map;

    using Engine::Entity;
    using Engine::CoordinateDouble;
    using Engine::AssetsManager;

    typedef function<Entity*(CoordinateDouble)> EntityCreator;
    typedef map<string, EntityCreator> EntityFactoryMap;

    class EntityFactory {
    public:
        EntityFactory(AssetsManager& assets);

        Entity* create_entity(string name, CoordinateDouble position);
        bool knows_entity(string name);

        template <class T>
        void register_entity(string name)
        {
            this->_map[name] = [this] (CoordinateDouble position)
            {
                return new T(this->_assets, position);
            };
        }
    private:
        EntityFactoryMap _map;
        AssetsManager& _assets;
    };
}


#endif //MINOR_VIDYA_ENTITYFACTORY_HPP
