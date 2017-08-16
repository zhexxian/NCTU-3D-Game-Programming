#ifndef __REDBALLS_H__
#define __REDBALLS_H__
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>

#include "game_obj.h"
class REDBALL : public GAME_OBJ {
protected:

public:
	REDBALL(SceneManager *a_SceneMgr);
	Vector3 direction;
	Vector3 currentPosition;
	Real angle;
	Real speed;
	Real actionPeriod;
	virtual void setWandering();
	virtual void update(const Ogre::FrameEvent& evt);
};

#endif
