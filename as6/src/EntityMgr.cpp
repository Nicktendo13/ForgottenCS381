/*
 * EntityMgr.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include <EntityMgr.h>
#include <Engine.h>

EntityMgr::EntityMgr(Engine *eng): Mgr(eng){
	player = 0;

}

EntityMgr::~EntityMgr(){

}

void EntityMgr::CreatePlayer(Ogre::Vector3 pos){
	Player* p;
	p =new Player(engine, pos);
	p->Init();
	player = p;

}

void EntityMgr::Tick(float dt){
	player->Tick(dt);
}
