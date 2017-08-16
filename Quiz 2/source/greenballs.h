#ifndef __GREENBALLS_H__
#define __GREENBALLS_H__
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>

#include "game_obj.h"

class GREENBALL : public GAME_OBJ {
protected:
public:
	GREENBALL(SceneManager *a_SceneMgr);
	Vector3 direction;
	Vector3 currentPosition;
	Real angle;
	Real speed;
	Real actionPeriod;
	GAME_OBJ *mGreenballTarget;
	virtual void setWandering();
	virtual void setChasing();
	virtual void setEvading();
	virtual void setArrival();
	virtual void setAction(Ogre::String actionMode);
	virtual void update(const Ogre::FrameEvent& evt, Ogre::String actionType, GAME_OBJ *a_Target);

};

#endif