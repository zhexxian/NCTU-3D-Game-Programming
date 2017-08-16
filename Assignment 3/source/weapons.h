#ifndef __WEAPONS_H__
#define __WEAPONS_H__
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>

#include "game_obj.h"
#include "game_obj.h"
#include "sound.h"
class WEAPON : public GAME_OBJ {
protected:
	SOUND *mSound;
public:
	WEAPON(SceneManager *a_SceneMgr);
	virtual void update(const Ogre::FrameEvent& evt);
	bool hitTarget_Sphere(const Vector3 &p, Real r );
	Real timeSinceBulletFiring;
};

#endif