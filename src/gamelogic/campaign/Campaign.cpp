//
// Created by mafn on 1/3/17.
//

#include "Campaign.hpp"

namespace GameLogic {

    Campaign::Campaign()
    {
        this->_init_maps();
    }

    void Campaign::_init_maps()
    {
        this->_levels.push_back(CampaignMap("res/TestMap.tmx"));
        this->_levels.push_back(CampaignMap("res/Fields.tmx"));

        // Unlock the first level
        this->_levels[0].unlocked = true;
    }

    vector<CampaignMap>& Campaign::get_levels()
    {
        return this->_levels;
    }
}