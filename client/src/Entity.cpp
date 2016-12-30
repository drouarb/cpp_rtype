/*
** trouve_b
*/

#include <iostream>
#include "Entity.hh"

using namespace client;

Entity::Entity() {
}

Entity::Entity(ide_t nid, typeide_t nidtype, pos_t npos, tick nturn) {
    pos = npos;
    posO = npos;
    id = nid;
    idtype = nidtype;
    vec = vec_t(0, 0);
    move.insert(std::pair<tick, moveData>(nturn, moveData(npos, vec_t(0, 0))));
    hp = 0;
    lastUpdate = 0;
}

Entity::~Entity() {
}

pos_t Entity::getPos() const { return pos; }

pos_t Entity::getOrigin() const { return posO; }

vec_t Entity::getVec() const { return vec; }

std::map<tick, moveData> Entity::getMove() const { return move; }

int Entity::getHp() const { return hp; }

ide_t Entity::getId() const { return id; }

typeide_t Entity::getTypeid() const { return idtype; }

void Entity::applyVec(vec_t nvec, tick tick) {
  pos.first += nvec.first;
  pos.second += nvec.second;
  vec.first = nvec.first;
  vec.second = nvec.second;
  lastUpdate = tick;
  //std::cout << "id : " << id << " vec = [" << nvec.first << ":" << nvec.second << "] pos : [" << pos.first << ":" << pos.second << "]" << std::endl;
}

void Entity::updateEntity(int nhp) {
    hp = nhp;
}

void Entity::moveEntity(vec_t nvec, pos_t npos, tick nturn) {
  /*std::map<tick, moveData>::iterator it;

    if ((it = move.find(nturn)) != move.end()) {
        std::cerr << "readaptation de move sur tick identique à faire" << std::endl;
        return;
    }
    it = move.begin();
    while (it != move.end())
    {
        std::cout << "DUMPid : " << id << " first : " << it->first << " second " << it->second.vec.first << ":" << it->second.vec.second << std::endl;
        ++it;
    }
    it = move.begin();
    while (it != move.end() && it->first > nturn)
        ++it;
    //++it;
    std::cout << "id : " << id << " mytick : " << it->first << " worldturn : " << nturn << "  vec : [" << nvec.first << ":" << nvec.second << "]" <<std::endl;
    if (it == move.end() || it->first < nturn) {
        if (it == move.end()) {
            std::cout << "id : " << id << " before" << std::endl;
            --it;
            correctBeforeVec(it, nvec, npos, nturn);
            vec = nvec;
            pos = npos;
            lastUpdate = nturn;
        } else {
            std::cout << "id : " << id << " middle" << std::endl;
            correctMiddleVec(it, &nvec, npos, nturn);
        }
        if (it->second.vec != nvec)
            move.insert(std::pair<tick, moveData>(nturn, moveData(npos, nvec)));
        recalcPos();
	}*/
  pos.first = npos.first;
  vec.first = nvec.first;
  pos.second = npos.second;
  vec.second = nvec.second;
}

void Entity::correctMiddleVec(std::map<tick, moveData>::iterator itO, vec_t *nvec, pos_t npos, tick nturn)
{
    std::map<tick, moveData>::iterator itA;

    itO->second.vec.first = (npos.first - itO->second.pos.first) / ((nturn - itO->first) + 1);
    itO->second.vec.second = (npos.second - itO->second.pos.second) / ((nturn - itO->first) + 1);
    itA = itO;
    ++itA;
    nvec->first = (itA->second.pos.first - npos.first) / ((itA->first - nturn) + 1);
    nvec->second = (itA->second.pos.second - npos.second) / ((itA->first - nturn) + 1);
}

void Entity::correctBeforeVec(std::map<tick, moveData>::iterator itO, vec_t nvec, pos_t npos, tick nturn) {
  itO->second.vec.first = (npos.first - itO->second.pos.first) / ((nturn - itO->first) + 1);
  itO->second.vec.second = (npos.second - itO->second.pos.second) / ((nturn - itO->first) + 1);
}

void Entity::recalcPos() {
    std::map<tick, moveData>::iterator it;
    std::map<tick, moveData>::iterator itnext;

    it = move.begin();
    pos.first = posO.first;
    pos.second = posO.second;
    itnext = it;
    ++itnext;
    while (itnext != move.end()) {
        pos.first += it->second.vec.first * (itnext->first - it->first);
        pos.second += it->second.vec.second * (itnext->first - it->first);
        ++it;
        ++itnext;
    }
}

void Entity::setVec(const vec_t &vec) {
    Entity::vec = vec;
}
