//
// Created by mafn on 1/3/17.
//

#ifndef MINOR_VIDYA_CAMPAIGN_HPP
#define MINOR_VIDYA_CAMPAIGN_HPP

#include <vector>
#include "CampaignMap.hpp"

namespace GameLogic {

    using std::vector;

    class Campaign {
    public:
        Campaign();

        vector<CampaignMap>& get_levels();
    private:
        vector<CampaignMap> _levels;
        void _init_maps();
    };
}


#endif //MINOR_VIDYA_CAMPAIGN_HPP
