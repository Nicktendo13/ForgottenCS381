#ifndef __EntityMgr_h_
#define __EntityMgr_h_

#include <vector>
#include <Mgr.h>
#include <Player.h>


class EntityMgr: public Mgr {
public:
  EntityMgr(Engine *engine);
  virtual ~EntityMgr();

  Player* player;

  void CreatePlayer(Ogre::Vector3 pos);

  void Tick(float dt);


};

#endif // #ifndef __EntityMgr_h_
