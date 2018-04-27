/*
 * Collectable.cpp
 *
 *  Created on: Apr 27, 2018
 *      Author: djia
 */

#include <GfxMgr.h>

#include <Collectable.h>

Collectable::Collectable(Engine *engine, Ogre::Vector3 pos ){

	this->engine = engine;

	meshfilename = "sphere.mesh";
	position = pos;

	ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshfilename);
	sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(pos);
	sceneNode->attachObject(ogreEntity);

}

Collectable::~Collectable(){

}

void Collectable::Init(){

	ogreEntity = engine->gfxMgr->mSceneMgr->createEntity(meshfilename);
	sceneNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(position);
	sceneNode->attachObject(ogreEntity);
}



//-------------------------------------------------------------------------------------------------------------------------------










