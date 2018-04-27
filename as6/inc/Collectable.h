/*
 * Collectable.h
 *
 *  Created on: Apr 27, 2018
 *      Author: djia
 */

#ifndef INC_COLLECTABLE_H_
#define INC_COLLECTABLE_H_

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <Aspect.h>

#include <Engine.h>

class Collectable
{
public:
  Collectable(Engine *engine, Ogre::Vector3 pos);
  virtual ~Collectable();

  Engine *engine;

  std::string meshfilename;
  Ogre::SceneNode* sceneNode;
  Ogre::Entity*    ogreEntity;

  Ogre::Vector3 position;

  void Init();

  void Tick(float dt);

protected:


};



#endif /* INC_COLLECTABLE_H_ */
