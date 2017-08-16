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
#include "TutorialApplication.h"
#include "BasicTools.h"


using namespace Ogre;
using namespace std;
BasicTutorial_00::BasicTutorial_00(void) {}

void BasicTutorial_00::createCamera(void)
{
    mCameraMap = mSceneMgr->createCamera("MapCamera");

    /*
    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(0,0,80));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,-300));
    */


    mCameraMap->setPosition(Ogre::Vector3(0,700,0));
    mCameraMap->lookAt(Ogre::Vector3(0,0,0.001));

    mCameraMap->setNearClipDistance(5);
    mCameraMap->yaw(Degree(180));

    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCamera");

    /*
    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(0,0,80));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,-300));
    */


    mCamera->setPosition(Ogre::Vector3(0,750,500));
    mCamera->lookAt(Ogre::Vector3(0,0,0));

    mCamera->setNearClipDistance(5);

    mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void BasicTutorial_00::createViewports(void)
{
    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(
        mCameraMap, 1, 0.0, 0, 0.25, 0.25);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,1));
    vp->setOverlaysEnabled(false);
    vp->setSkiesEnabled(false);
    // Alter the camera aspect ratio to match the viewport
    mCameraMap->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

    // Create one viewport, entire window
    vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
    //vp->setOverlaysEnabled(false);
    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}


bool BasicTutorial_00::mouseMoved( const OIS::MouseEvent &arg )
{
    return BaseApplication::mouseMoved( arg);

}

int BasicTutorial_00::getSceneObjID(const SceneNode *ptr)
{
    int index = -1;
    return index;
}
void BasicTutorial_00::singleClickSelect ( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    Ray mRay =mTrayMgr->getCursorRay(mCamera);

}



bool BasicTutorial_00::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if (id == OIS::MB_Right) {
        return BaseApplication::mouseReleased( arg, id );
    }
    return BaseApplication::mouseReleased( arg, id );

}



int main(int argc, char *argv[]) {
    BasicTutorial_00 app;
    app.go();  
    return 0;
}
