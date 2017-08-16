//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
/*!
\brief 3D Game Programming
\n
My Name: Zhang Zhexian
\n
My ID: 0545080
\n
My Email: zhangzhexian@outlook.com

This is an assignment of 3D Game Programming

*/

#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_

#include "BaseApplication.h"
#include "greenball_manager.h"
#include "redballs.h"

class BasicTutorial_00 : public BaseApplication
{
public:
	BasicTutorial_00(void);
	virtual bool frameStarted(const Ogre::FrameEvent& evt);
	virtual void createViewports(void);
	virtual void createScene(void);
	virtual void createCamera(void);
	virtual void chooseSceneManager(void);

	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	
	void initParticleSystemForExplosion();
	void setOffParticleSystem(
	Ogre::SceneNode *fNode, const Ogre::String &pname, const Ogre::Vector3 &pos); 
	Vector3 big_sphere_position;
	REDBALL *mRedball;

private:

	void createViewport_00(void);
	void createViewport_01(void);
	//
	void createCamera_00();
	void createCamera_01();

	void createScene_00();
	void createScene_01();

	bool mFlgMotion;
	bool mKeyPressed;
	bool mToggle;
	Ogre::Light *mLight0;
	Ogre::SceneNode* fNode;
	Ogre::SceneNode* mSN_Sphere;
	Ogre::Camera* mCameraArr[8];
	Ogre::SceneManager* mSceneMgrArr[8];
	OgreBites::SdkCameraMan* mCameraManArr[8];
		
//
	Real mSphereRadius;
	int mKeyPressedZoomMode;
	Real mCameraDistanceSlowDownSpeed;
	Real mCameraDistance;
	Real mCameraDistanceAdjustSpeed;
	GREENBALL_MANAGER *mGreenballMgr;
};

#endif // #ifndef __BasicTutorial_00_h_