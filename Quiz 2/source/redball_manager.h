#ifndef __REDBALL_MGR__
#define __REDBALL_MGR__
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>

#include "game_obj.h"
#include "redballs.h"

class REDBALL_MANAGER : public GAME_OBJ {
protected:
	REDBALL *mRedball;
	Real actionPeriod;

public:
	REDBALL_MANAGER(SceneManager *a_SceneMgr);
	virtual void update(const Ogre::FrameEvent& evt);
	virtual void setWandering();
};

#endif