#ifndef __GREENBALL_MGR__
#define __GREENBALL_MGR__
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>

#include "game_obj.h"
#include "greenballs.h"

class GREENBALL_MANAGER : public GAME_OBJ {
protected:
	int mNumGreenballs;
	int mCurGreenballsNum;
	bool mLifeStateArr[512];
	GREENBALL *mGreenballsArr[512];
	Vector3 greenballTotalTranslation[512];
	GAME_OBJ *mGreenballsTarget;
	void resolveGreenballTargetCollision();
	void resolveGreenballCollision();
	void resolveGreenballFollowingTarget();

public:
GREENBALL_MANAGER(SceneManager *a_SceneMgr);
virtual void update(const Ogre::FrameEvent& evt);
virtual void setTargetForGreenballs(GAME_OBJ *a_Target);
virtual void setMaxGreenballsNum(int a_Num);
virtual void setAction(Ogre::String actionMode);
Ogre::String actionType;
};

#endif