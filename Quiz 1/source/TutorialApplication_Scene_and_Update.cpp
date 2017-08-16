#include "TutorialApplication.h"
#include "BasicTools.h"

using namespace Ogre;
using namespace std;

void BasicTutorial_00::createScene(void) 
{
    mCurrentPathPointIndex = 0;
    ColourValue fadeColour(0.9, 0.9, 0.9); 
    //mSceneMgr->setFog(FOG_LINEAR, fadeColour, 0, 1400, 1600);
    mSceneMgr->setSkyBox(
        true, 
        "Examples/SpaceSkyBox"); 

    mSceneMgr->setAmbientLight( ColourValue( 0.9, 0.9, 0.9 ) ); 
    //mSceneMgr->setAmbientLight( ColourValue( 1, 1, 1 ) );  
    mSceneMgr->setShadowTechnique(
        SHADOWTYPE_STENCIL_ADDITIVE); 

    //
    Light *light = mSceneMgr->createLight("Light1"); 
    light->setType(Light::LT_POINT); 
    light->setPosition(Vector3(0, 150, 250)); 
    light->setDiffuseColour(1.0, 1.0, 1.0);		//red
    light->setSpecularColour(0.5, 0.5, 0.5);	//red

    mLightSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    mLightSceneNode->attachObject(light);
    int i;

    //Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing SCENE ***");

    //
    //
    Plane plane(Vector3::UNIT_Y, 0); 
    MeshManager::getSingleton().createPlane(
        "ground", 						ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
        plane, 
        2500,2500, 	// width, height
        20,20, 		// x- and y-segments
        true, 		// normal
        1, 		// num texture sets
        5,5, 		// x- and y-tiles
        Vector3::UNIT_Z	// upward vector
        ); 

    Entity *ent = mSceneMgr->createEntity(
        "GroundEntity", "ground"); 
    ent->setMaterialName("Examples/Rocky");
    ent->setQueryFlags(0x0);
    mSceneMgr
        ->getRootSceneNode()
        ->createChildSceneNode()
        ->attachObject(ent); 
    //
    mRobotNode = mSceneMgr
        ->getRootSceneNode()
        ->createChildSceneNode(Vector3(-90, 0 , -30));
    mRobotEntity = mSceneMgr->createEntity(
        "robot", "robot.mesh"); 
    mRobotNode->attachObject( mRobotEntity );
    //
    mRobotNode->scale(1.0, 1.0, 1.0 );
    mAnimationState = mRobotEntity->getAnimationState("Idle");
    mAnimationState->setEnabled(true);
    mAnimationState->setLoop(true);

    //
    mMap = new MAP;
    mMap->generateMap( mSceneMgr );
    //

}

void BasicTutorial_00::computeGoalPosition(int selectionPointIndex )
{
    Vector3 planeNormal = Vector3(0, 1, 0);
    Ray ray;
    ray = mTrayMgr->getCursorRay(mCamera);
    Plane p(Vector3(0, 1, 0), 0);
    std::pair<bool,Real> result = ray.intersects(p);
    Vector3 point = ray.getOrigin()+result.second*ray.getDirection();
    if ( selectionPointIndex == 0 ) {
        mGoalPosition = point;
    } else {
        mGoalPosition = point;

    }
}

void BasicTutorial_00::controlRobotMovingAlongPath( const FrameEvent &evt )
{
    if ( mPathPoints.size() == 0 ) {
		return;
	}

    else if ( mPathPoints.size() == mCurrentPathPointIndex ) {
        mAnimationState =  mRobotEntity->getAnimationState("Idle");
		mAnimationState->setEnabled(true);
		mAnimationState->setLoop(true);
        mAnimationState->addTime( evt.timeSinceLastFrame );
		return;
    }
	else {
		//Fill in your code
		//

		mAnimationState =  mRobotEntity->getAnimationState("Walk");
		mAnimationState->setEnabled(true);
		mAnimationState->setLoop(true);
		mAnimationState->addTime( evt.timeSinceLastFrame );
	
		Vector3 walkDirection = mPathPoints[mCurrentPathPointIndex] - mRobotNode->getPosition();
		walkDirection.normalise();
		mRobotNode->translate(walkDirection * evt.timeSinceLastFrame * 100, Node::TS_LOCAL);

		if(walkDirection.dotProduct(mPathPoints[mCurrentPathPointIndex] - mRobotNode->getPosition()) < 0) {

			mAnimationState = mRobotEntity->getAnimationState("Idle");
			mAnimationState->setLoop(true);
			mAnimationState->setEnabled(true);
			mAnimationState->addTime( evt.timeSinceLastFrame );
			mCurrentPathPointIndex++;
			return;
		}	

	}
	
}

bool BasicTutorial_00::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if (id == OIS::MB_Left) {
        computeGoalPosition(0);
        mStartPosition = mRobotNode->getPosition( );
        bool flgValid = mMap->performPathFinding( mStartPosition, mGoalPosition );
        if ( flgValid == false ) return true;
		mCurrentPathPointIndex = 0;
        mPathPoints = mMap->getPathPoints();
        return BaseApplication::mouseReleased( arg, id );
    }

    return BaseApplication::mousePressed( arg, id );
}



bool BasicTutorial_00::frameStarted(const FrameEvent &evt)
{
    controlRobotMovingAlongPath( evt );
    return BaseApplication::frameStarted(evt);
}