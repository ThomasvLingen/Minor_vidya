//
// Created by mafn on 1/3/17.
//

#include "CampaignMap.hpp"
#include "../rapidXML/RapidXMLAdapter.hpp"

namespace GameLogic {
    CampaignMap::CampaignMap(std::string tmx_path)
    : tmx_source_path(tmx_path)
    , unlocked(false)
    {
        RapidXMLAdapter tmx_level;
        tmx_level.setup_document(tmx_path);
        this->name = tmx_level.get_map_name();
    }

    /// \brief This operator assumes that there are no 2 maps with the same tmx_source_path.
    /// \return Wheter or not 2 CampaignMaps are the same
    bool CampaignMap::operator==(const CampaignMap& other)
    {
        return this->tmx_source_path == other.tmx_source_path;
    }
}
