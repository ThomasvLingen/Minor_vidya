//
// Created by waseland on 11/7/16.
//

#ifndef MINOR_VIDYA_TILE_HPP
#define MINOR_VIDYA_TILE_HPP

#include "../engine/domain/TileObject.hpp"
#include <vector>
#include "TileTrigger.hpp"

namespace GameLogic {

    using Engine::ImageBuffer;
    using std::vector;

    class Tile : public Engine::TileObject {

    public:
        Tile(ImageBuffer* texture);
        ~Tile();

        void update(int delta_time) override;

        vector<TileTrigger*> get_step_on_tiletriggers();
        vector<TileTrigger*> get_action_tiletriggers();

        void add_step_on_tiletrigger(TileTrigger*);
        void add_action_tiletrigger(TileTrigger*);

    private:
        vector<TileTrigger*> _step_on_tiletriggers;
        vector<TileTrigger*> _action_tiletriggers;
    };
}


#endif //MINOR_VIDYA_TILE_HPP
