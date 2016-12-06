//
// Created by greg on 02/12/2016.
//

#include "Attack.hh"

server::Attack::Attack(const std::string &soundFile, const std::string &sprite, server::damage_t damage,
                       uint16_t recharge, uint16_t nbHits) : soundFile(soundFile), sprite(sprite), damage(damage),
                                                             recharge(recharge), nbHits(nbHits) {}

std::ostream &server::operator<<(std::ostream &os, const server::Attack &attack) {
    os << "soundFile: " << attack.soundFile << " sprite: " << attack.sprite << " damage: " << attack.damage
       << " recharge: " << attack.recharge << " nbHits: " << attack.nbHits;
    return os;
}
