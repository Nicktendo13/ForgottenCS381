/*
 * Aspect.cpp
 *
 *  Created on: Feb 7, 2018
 *      Author: sushil
 */

#include<Aspect.h>
#include <Player.h>  //Aspect includes Player.h


Aspect::Aspect(Player *p){
	player = p;
}

Aspect::~Aspect(){

}

void Aspect::Tick(float dt){

}




Renderable::Renderable(Player* p):Aspect(p){

}

Renderable::~Renderable(){

}

void Renderable::Tick(float dt){
//do something;
	player->sceneNode->setPosition(player->position); //now ogre should render the sceneNode at the new position...
	player->sceneNode->resetOrientation(); // yaw is cumulative, so set current y-rotation to 0

}

