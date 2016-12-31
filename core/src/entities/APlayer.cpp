//
// Created by lewis_e on 31/12/16.
//

#include "entities/APlayer.hh"

using namespace server;

score_t APlayer::getScore() const
{
    return (score);
}

void APlayer::modScore(score_t addition)
{
    score += addition;
}

APlayer::Power::Power(APlayer *player) : player(player)
{ }

void APlayer::Power::modScore(score_t addition)
{
    player->modScore(addition);
}

APlayer *APlayer::Power::getOwner() const
{
    return (player);
}
