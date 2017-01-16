//
// Created by mafn on 1/3/17.
//

#ifndef MINOR_VIDYA_IETS_HPP
#define MINOR_VIDYA_IETS_HPP

#include <string>

namespace GameLogic {

    using std::string;

    class CampaignMap {
    public:
        CampaignMap(string tmx_path);

        string name;
        string tmx_source_path;
        bool unlocked;

        bool operator==(const CampaignMap& other);
    private:
    };
}


#endif //MINOR_VIDYA_IETS_HPP
