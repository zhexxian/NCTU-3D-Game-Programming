//
// Student Name:
// Student ID:
// Student Email Address:
//
//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
// Select and move characters
#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_

#include "BaseApplication.h"
#include "selection_rectangle.h"
#include "sound.h"

using namespace Ogre;
#define MOTION_TYPE_NONE 0
#define MOTION_TYPE_IDLE 1
#define MOTION_TYPE_WALK 2

class BasicTutorial_00 : public BaseApplication
{
private:
	void initParticleSystemForExplosion();
	void setOffParticleSystem(
		Ogre::SceneNode *fNode, const Ogre::String &pname, const Ogre::Vector3 &pos); 

	SOUND *mSound;
	PlaneBoundedVolumeListSceneQuery *mVolQuery;
	SceneNode *mParticleNode;
	SelectionRectangle *mSelectionRect;
	Real left, top, right, bottom, initX, initY;
	SceneNode *mCurrentObject;
	SceneNode *mSceneNodeArr[128];
	Entity *mEntityArr[128];
	AnimationState *mAnimationState[128];

	bool robotIsWalking[128];
	float mDistance[128];
	Vector3 mDestination;
	Vector3 mDirection[128];
	Vector3 mSphereNormal[128];
	
	virtual void createCamera();
	virtual void createViewports();
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool frameStarted(const FrameEvent &evt);
	virtual void createDefaultPlane(void);
public:
	BasicTutorial_00(void);
	virtual void createScene(void);
	virtual void createCircleOfObjects(Ogre::String objectMesh, Ogre::Real startingIndex, Ogre::Real numObjects, float circleRadius, Ogre::SceneManager* mSceneMgr, Ogre::String prefix);
};

#endif // #ifndef __BasicTutorial_00_h_