//
// Created by mafn on 1/16/17.
//

#ifndef MINOR_VIDYA_CHEATS_HPP
#define MINOR_VIDYA_CHEATS_HPP

#include "../engine/interface/Handleable.hpp"
#include "Game.hpp"

namespace GameLogic {
    class Cheats : public Engine::Handleable {
    public:
        Cheats(Game& context);

        virtual void handle_input(Input& keys) override;

    private:
        Game& _context;

        void _insta_win();
    };
}


#endif //MINOR_VIDYA_CHEATS_HPP
