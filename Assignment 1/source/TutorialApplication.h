/*
-----------------------------------------------------------------------------
Filename:    BasicTutorial2.h
-----------------------------------------------------------------------------
 
This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
	  Tutorial Framework
	  http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/

/*!
Name: Zhang Zhexian;
ID: 0545080;
Email: zhangzhexian@outlook.com;
*/

#ifndef __BasicTutorial2_h_
#define __BasicTutorial2_h_
 
#include "BaseApplication.h"
//#include "OgreGamePlatform.h"

class BasicTutorial2 : public BaseApplication
{
public:
	BasicTutorial2(void);
	virtual ~BasicTutorial2(void);
protected:
	 Ogre::SceneManager* mSceneMgr0;
	 Ogre::SceneManager* mSceneMgr1;
protected:
	virtual void createScene(void);
	virtual void createCamera(void);
	virtual void createViewports(void);
	//virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	virtual void chooseSceneManager(void);
	virtual void createCircleOfObjects(Ogre::String objectMesh, Ogre::Real numObjects, float circleRadius, Ogre::SceneManager* mSceneMgr);
	virtual void createRowOfObjects(Ogre::String objectMesh, Ogre::Real numObjects, Ogre::SceneManager* mSceneMgr);
	virtual void createDefaultPlane(void);
	virtual void createPointLight(Ogre::String name, Ogre::Vector3 position, float redValue, float greenValue, float blueValue, Ogre::SceneManager* mSceneMgr);
private:
	//ns_phys::OgreGamePlatform *mOgreGamePlatform;
};
 
#endif // #ifndef __BasicTutorial2_h_