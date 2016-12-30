/*
** trouve_b
*/

#include <mutex>
#include <iostream>
#include "World.hh"

using namespace client;

World::World(std::mutex *mmut, GameUIInterface *ngame) {
    world_mut = mmut;
    gameui = ngame;
    turn = 0;
}

World::~World() {
    std::map<ide_t, Entity *>::iterator it;

    it = entitys.begin();
    while (it != entitys.end()) {
      gameui->deleteEntity(entitys.at(it->first));
      delete it->second;
      ++it;
    }
}

void World::spawnEntity(ide_t nid, pos_t pos, typeide_t idtype, UIevent_t nevent, tick nturn) {
    world_mut->lock();
    //std::cout << "t=<" << nturn << "> Spawn entity (" << nid << ") type : " << idtype << " : [" << pos.first << ":"
          //    << pos.second << "]" << std::endl;
    worldEvents.push_back(std::pair<tick, WorldEvent>(nturn, WorldEvent(nid, pos, idtype, nturn, nevent)));
    std::list<std::pair<tick, WorldEvent> >::iterator it;
    it = worldEvents.begin();
    while (it != worldEvents.end()) {
      //  std::cout << "t=" << it->first << " id=" << it->second.id << " eventid=" << it->second.eventtype << std::endl;
        ++it;
    }
    world_mut->unlock();
}

void World::moveEntity(vec_t vec, pos_t pos, tick nturn, ide_t nid, UIevent_t nevent) {
    world_mut->lock();
//    std::cout << "t=<" << nturn << "> move entity (" << nid << ") : [" << pos.first << ":" << pos.second << "] vec: ["
  //            << vec.first klkklknl<< ":" << vec.second << "]" << std::endl;
    worldEvents.push_back(std::pair<tick, WorldEvent>(nturn, WorldEvent(nid, vec, pos, nturn, nevent)));
    std::list<std::pair<tick, WorldEvent> >::iterator it;
    it = worldEvents.begin();
    world_mut->unlock();
}

void World::updateEntity(int hp, tick nturn, ide_t nid, UIevent_t nevent) {
    world_mut->lock();
    //std::cout << "t=<" << nturn << "> update entity (" << nid << ") : " << hp << std::endl;
    worldEvents.push_back(std::pair<tick, WorldEvent>(nturn, WorldEvent(nid, hp, nturn, nevent)));
    world_mut->unlock();
}

void World::deleteEntity(ide_t nid, tick nturn, UIevent_t nevent) {
    world_mut->lock();
    //std::cout << "t=<" << nturn << "> delete entity (" << nid << ")" << std::endl;
    worldEvents.push_back(std::pair<tick, WorldEvent>(nturn, WorldEvent(nid, nturn, nevent)));
    world_mut->unlock();
}

tick World::getTick() const {
    return (turn);
}

void World::applyTurn() {
    std::map<ide_t, Entity *>::iterator it;
    std::list<std::pair<tick, WorldEvent> >::iterator itEv;
    Entity *ent;
    pos_t pos;

    itEv = worldEvents.begin();
    //world_mut->lock();
    while (itEv != worldEvents.end()) {
        //std::cout << "event for id : " << itEv->second.id << " event : " << itEv->second.eventtype << std::endl;
        if (itEv->first < turn) {
            if (itEv->second.eventtype == SPAWN && (entitys.find(itEv->second.id) == entitys.end())) {
                ent = new Entity(itEv->second.id, itEv->second.type, itEv->second.pos, itEv->first);
                pos = ent->getPos();
                entitys.insert(std::pair<ide_t, Entity *>(itEv->second.id, ent));
                gameui->addEntity(getEntityById(itEv->second.id));
            } else if (itEv->second.eventtype == UPDATE && (entitys.find(itEv->second.id) != entitys.end())) {
                //std::cout << "update" << std::endl;
                ent = entitys.at(itEv->second.id);
                pos = ent->getPos();
                ent->updateEntity(itEv->second.hp);
            } else if (itEv->second.eventtype == MOVE && (entitys.find(itEv->second.id) != entitys.end())) {
                //std::cout << "move" << std::endl;
                ent = entitys.at(itEv->second.id);
                pos = ent->getPos();
                ent->moveEntity(itEv->second.vec, itEv->second.pos, itEv->second.turn);
            } else if (itEv->second.eventtype == DELETE && (entitys.find(itEv->second.id) != entitys.end())) {
                gameui->deleteEntity(entitys.at(itEv->second.id));
                ent = entitys.at(itEv->second.id);
                pos = ent->getPos();
                entitys.erase(itEv->second.id);
                delete ent;
            }
            //UIevents.push_back(std::pair<UIevent_t, pos_t>(itEv->second.UIevent, pos));
            worldEvents.erase(itEv);
            itEv = worldEvents.begin();
        }
        ++itEv;
    }
    //world_mut->unlock();
    it = entitys.begin();
    while (it != entitys.end()) {
        it->second->applyVec(it->second->getVec(), turn);
        ++it;
    }
    ++turn;
}

Entity *World::getEntityById(ide_t nid) {
    if (entitys.find(nid) != entitys.end()) { //TODO
        return (entitys.at(nid));
    }
}

std::map<ide_t, Entity *> World::getEntitys() {
    return (entitys);
}

std::vector<std::pair<UIevent_t, pos_t> > World::getEvents() {
    std::vector<std::pair<UIevent_t, pos_t> > retVec;

    retVec = UIevents;
    UIevents.clear();
    UIevents.reserve(RESERVE_UIEVENTS);
    return (retVec);
}
