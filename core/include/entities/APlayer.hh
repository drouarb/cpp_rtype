//
// Created by greg on 08/12/2016.
//

#ifndef CPP_RTYPE_IPLAYER_HH
#define CPP_RTYPE_IPLAYER_HH

#include "ADynamicObject.hh"

namespace server
{
    /**
     * \class APlayer
     * \brief Class to implements when you create a player
     * Do not forget to add (Aplayer *getInstance)();
     */
    class APlayer : public ADynamicObject
    {
    public:
        /**
         * \brief Tell the player 'attack' => this can lead to creation of new ADynamicObject (missile for example)
         * @param round Current round in the game
         */
        virtual void shoot(round_t round) = 0;
        /**
         * Move the player with specified vector
         * @param vectX Of how many should the player move on the X axis
         * @param vectY Of how many should the player move on the Y axis
         */
        virtual void move(speed_t vectX, speed_t vectY) = 0;
    };
}

#endif //CPP_RTYPE_IPLAYER_HH
