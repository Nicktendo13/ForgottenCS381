/*
 * Player.h
 *
 *  Created on: Apr 27, 2018
 *      Author: djia
 */

#ifndef INC_PLAYER_H_
#define INC_PLAYER_H_

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <Aspect.h>

#include <Engine.h>

class Player
{
public:
  Player(Engine *engine, Ogre::Vector3 pos);
  virtual ~Player();

  Engine *engine;

  std::string meshfilename;
  Ogre::SceneNode* sceneNode;
  Ogre::Entity*    ogreEntity;

  Ogre::Vector3 position;
  float speed;

  std::vector<Aspect* > aspects;

  void Init();

  void Tick(float dt);

protected:


};



#endif /* INC_PLAYER_H_ */
