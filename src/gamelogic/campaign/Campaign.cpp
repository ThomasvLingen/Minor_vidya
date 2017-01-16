//
// Created by mafn on 1/3/17.
//

#include <algorithm>
#include "Campaign.hpp"
#include "../exceptions/MapExceptions.hpp"

namespace GameLogic {

    Campaign::Campaign()
    {
        this->_init_maps();
    }

    void Campaign::_init_maps()
    {
        this->_levels.push_back(CampaignMap("res/tutorial.tmx"));
        this->_levels.push_back(CampaignMap("res/TestMap.tmx"));
        this->_levels.push_back(CampaignMap("res/Fields.tmx"));
        this->_levels.push_back(CampaignMap("res/Bunker.tmx"));

        // Unlock the first level
        this->_levels[0].unlocked = true;
    }

    vector<CampaignMap>& Campaign::get_levels()
    {
        return this->_levels;
    }

    CampaignMap& Campaign::get_next_level(CampaignMap& map_to_find_next_of)
    {
        vector<CampaignMap>::iterator map_it = std::find(this->_levels.begin(), this->_levels.end(), map_to_find_next_of);

        if (map_it != this->_levels.end()) {
            vector<CampaignMap>::iterator next_level_it = std::next(map_it);

            if (next_level_it != this->_levels.end()) {
                return *next_level_it;
            }
        }

        throw Exceptions::NoNextMapExcepion();
    }
}