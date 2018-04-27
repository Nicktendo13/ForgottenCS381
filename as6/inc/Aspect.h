#ifndef __Aspect_h_
#define __Aspect_h_

#include<OgreVector3.h>

class Player;

class Aspect
{
public:
  Aspect(Player* player);
  virtual ~Aspect();

  Player* player;

  virtual void Tick(float dt);


protected:

};



class Renderable : Aspect
{
public:
	Renderable(Player* player);
	~Renderable();

	void Tick(float dt);
};


#endif // #ifndef __Aspect_h_
