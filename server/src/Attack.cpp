//
// Created by greg on 02/12/2016.
//

#include "Attack.hh"

Server::Attack::Attack(const std::string &soundFile, const std::string &sprite, Server::AEntity::damagePoint_t damage,
                       uint16_t recharge, uint16_t nbHits) : soundFile(soundFile), sprite(sprite), damage(damage),
                                                             recharge(recharge), nbHits(nbHits) {}

std::ostream &Server::operator<<(std::ostream &os, const Server::Attack &attack) {
    os << "soundFile: " << attack.soundFile << " sprite: " << attack.sprite << " damage: " << attack.damage
       << " recharge: " << attack.recharge << " nbHits: " << attack.nbHits;
    return os;
}
