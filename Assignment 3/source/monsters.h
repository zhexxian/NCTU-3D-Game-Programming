#ifndef __MONSTERS_H__
#define __MONSTERS_H__
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>

#include "game_obj.h"
#include "game_obj.h"
class MONSTER : public GAME_OBJ {
protected:
	void updateViewDirection();
public:
	MONSTER(SceneManager *a_SceneMgr);
	void lookAt(Vector3 direction);
	virtual void update(const Ogre::FrameEvent& evt, Vector3 monsterPosition, Vector3 targetPosition);
};

#endif