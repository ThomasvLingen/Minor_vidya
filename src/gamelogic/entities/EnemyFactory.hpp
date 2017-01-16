//
// Created by mafn on 1/2/17.
//

#ifndef MINOR_VIDYA_ENEMYFACTORY_HPP
#define MINOR_VIDYA_ENEMYFACTORY_HPP

#include <functional>

#include "Enemy.hpp"
#include "../../engine/AssetsManager.hpp"
#include "../../engine/domain/CoordinateDouble.hpp"

namespace GameLogic {

    using std::function;
    using std::string;
    using std::map;

    using Engine::Entity;
    using Engine::CoordinateDouble;
    using Engine::AssetsManager;

    typedef function<Enemy*(CoordinateDouble, vector<CoordinateDouble>)> EnemyCreator;
    typedef map<string, EnemyCreator> EnemyFactoryMap;

    class EnemyFactory {
    public:
        EnemyFactory(AssetsManager& assets);

        Enemy* create_enemy(string name, CoordinateDouble position, vector<CoordinateDouble> idle_route );
        bool knows_enemy(string name);

        template <class T>
        void register_enemy(string name)
        {
            this->_map[name] = [this] (CoordinateDouble position, vector<CoordinateDouble> idle_route )
            {
                return new T(this->_assets, position, idle_route);
            };
        }
    private:
        EnemyFactoryMap _map;
        AssetsManager& _assets;
    };
}


#endif //MINOR_VIDYA_ENEMYFACTORY_HPP
