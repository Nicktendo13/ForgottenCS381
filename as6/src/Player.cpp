/*
 * Player.cpp
 *
 *  Created on: Apr 27, 2018
 *      Author: djia
 */

#include <GfxMgr.h>

#include<Player.h>

Player::Player(Engine *engine, Ogre::Vector3 pos ){

	this->engine = engine;

	meshfilename = "cube.mesh";
	position = pos;

	ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshfilename);
	sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(pos);
	sceneNode->attachObject(ogreEntity);
	speed = 20;

	Renderable * renderable = new Renderable(this);
	aspects.push_back((Aspect*)renderable);

}

Player::~Player(){

}

void Player::Init(){

	ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshfilename);
	sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
	sceneNode->attachObject(ogreEntity);
}

void Player::Tick(float dt){
	for(unsigned int i = 0; i < aspects.size(); i++){
		aspects[i]->Tick(dt);
	}
}

//-------------------------------------------------------------------------------------------------------------------------------






