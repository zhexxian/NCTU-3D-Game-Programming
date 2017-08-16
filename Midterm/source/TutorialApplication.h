// Name: Zhang Zhexian
// ID: 0545080
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_
 
#include "BaseApplication.h"

using namespace Ogre;
class BasicTutorial_00 : public BaseApplication
{
private:
	Entity *mEntity;
	AnimationState *mAnimationState;
    //
    void chooseSceneManager(void);
    void createCamera(void);
    void createViewports(void);
	bool frameStarted(const FrameEvent &evt);
    
public:
	BasicTutorial_00(void);
	SceneNode *mSceneNodeArr[128];
	Entity *mEntityArr[128];
	//AnimationState *mAnimationState[128];
	Vector3 mDestination;
	SceneNode *sNode;
	SceneNode *sNodeChild;
	bool flag;
	virtual void createScene(void);
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual void createDefaultPlane(void);
	virtual void createRowOfObjects(Ogre::String objectMesh, Ogre::Real startingIndex, Ogre::Real numObjects, Ogre::SceneManager* mSceneMgr, float zPosition, Ogre::String prefix);
};
 
#endif // #ifndef __BasicTutorial_00_h_