/*
 * InputMgr.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: sushil
 */
#include<cfloat>

#include <Engine.h>
#include <GfxMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>
#include <GameMgr.h>
#include <UiMgr.h>

InputMgr::InputMgr(Engine *engine) : Mgr(engine), OIS::KeyListener(), OIS::MouseListener() {

	this->mInputMgr = 0;
	this->mKeyboard = 0;
	this->mMouse = 0;
	this->keyboardTimer = keyTime;
	deltaDesiredSpeed = 10.0f;
	deltaDesiredHeading = 10.0f;
	deltaDesiredAltitude = 20;
	this->selectionDistanceSquaredThreshold = 10000;
}

InputMgr::~InputMgr() {

}

void InputMgr::Init(){

	  OIS::ParamList pl;
	  size_t windowHandle = 0;
	  std::ostringstream windowHandleStr;

	  engine->gfxMgr->mWindow->getCustomAttribute("WINDOW", &windowHandle);
	  windowHandleStr << windowHandle;
	  pl.insert(std::make_pair(std::string("WINDOW"), windowHandleStr.str()));
	  // insert the following lines right before calling mInputSystem = OIS::InputManager::createInputSystem( paramList );
		#if defined OIS_WIN32_PLATFORM
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
		pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
		pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
		#elif defined OIS_LINUX_PLATFORM
		pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
		pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
		//pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
		pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
		#endif

	  mInputMgr = OIS::InputManager::createInputSystem(pl);

	  mKeyboard = static_cast<OIS::Keyboard*>(
	    mInputMgr->createInputObject(OIS::OISKeyboard, true));
	  mMouse = static_cast<OIS::Mouse*>(
	    mInputMgr->createInputObject(OIS::OISMouse, true));

	  int left, top;
	  unsigned int width, height, depth;

	  engine->gfxMgr->mWindow->getMetrics(width, height, depth, left, top);
	  const OIS::MouseState &ms = mMouse->getMouseState();
	  ms.width = width;
	  ms.height = height;
	  mMouse->setEventCallback(this);
	  mKeyboard->setEventCallback(this);

}



void InputMgr::Stop(){
	if(mInputMgr){
		mInputMgr->destroyInputObject(mMouse);
		mInputMgr->destroyInputObject(mKeyboard);

		OIS::InputManager::destroyInputSystem(mInputMgr);
		mInputMgr = 0;
   	}
}

void InputMgr::Tick(float dt){

	mKeyboard->capture();
	if(mKeyboard->isKeyDown(OIS::KC_ESCAPE)){
		engine->keepRunning = false;
	}
	mMouse->capture();
//	mTrayMgr->frameRenderingQueued(fe);

	UpdateCamera(dt);
	UpdateVelocityAndSelection(dt);

}

void InputMgr::UpdateCamera(float dt){
	float move = 400.0f;
	float rotate = 0.1f;

	 Ogre::Vector3 dirVec = Ogre::Vector3::ZERO;

	  if (mKeyboard->isKeyDown(OIS::KC_W))
	    dirVec.z -= move;

	  if (mKeyboard->isKeyDown(OIS::KC_S))
	    dirVec.z += move;

	  if (mKeyboard->isKeyDown(OIS::KC_E))
	    dirVec.y += move;

	  if (mKeyboard->isKeyDown(OIS::KC_F))
	    dirVec.y -= move;

	  if (mKeyboard->isKeyDown(OIS::KC_A))
	  {
	    if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
		      engine->gameMgr->cameraNode->yaw(Ogre::Degree(5 * rotate));
	    else
	      dirVec.x -= move;
	  }

	  if (mKeyboard->isKeyDown(OIS::KC_D))
	  {
	    if (mKeyboard->isKeyDown(OIS::KC_LSHIFT))
	      engine->gameMgr->cameraNode->yaw(Ogre::Degree(-5 * rotate));
	    else
	      dirVec.x += move;
	  }

	  engine->gameMgr->cameraNode->translate(dirVec * dt, Ogre::Node::TS_LOCAL);
}

void InputMgr::UpdateVelocityAndSelection(float dt){
	keyboardTimer -= dt;

	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_UP)){
		keyboardTimer = keyTime;
		engine->entityMgr->player->position.z -= deltaDesiredSpeed;
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_DOWN)){
		keyboardTimer = keyTime;
		engine->entityMgr->player->position.z += deltaDesiredSpeed;
	}

	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_LEFT)){
		keyboardTimer = keyTime;
		engine->entityMgr->player->position.x -= deltaDesiredSpeed;
	//turn left is decreasing degrees, turn right is increasing degrees because increasing degrees gives us the +ive Z axis
	}
	if((keyboardTimer < 0) && mKeyboard->isKeyDown(OIS::KC_RIGHT)){
		keyboardTimer = keyTime;
		engine->entityMgr->player->position.x += deltaDesiredSpeed;
	}

}

void InputMgr::LoadLevel(){

}

bool InputMgr::keyPressed(const OIS::KeyEvent& ke){
	return true;
}

bool InputMgr::keyReleased(const OIS::KeyEvent& ke){
	return true;
}

bool InputMgr::mouseMoved(const OIS::MouseEvent& me){
    if (engine->uiMgr->mTrayMgr->injectMouseMove(me)) return true;
	return true;
}

bool InputMgr::mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID mid){
	std::cout << "Mouse pressed" << std::endl;
    if (engine->uiMgr->mTrayMgr->injectMouseDown(me, mid)) return true;
	if(OIS::MB_Left == mid){
		std::cout << "Left mouse press" << std::endl;
	}

	return true;
}

bool InputMgr::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID mid){
    if (engine->uiMgr->mTrayMgr->injectMouseUp(me, mid)) return true;
	return true;
}




