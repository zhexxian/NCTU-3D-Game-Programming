//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
#include "TutorialApplication.h"
#include "Windows.h"
#include "MMSystem.h"
using namespace std;
using namespace Ogre;
BasicTutorial_00::BasicTutorial_00(void) {}

void BasicTutorial_00::chooseSceneManager(void)
{
    // Get the SceneManager, in this case a generic one
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
}
void BasicTutorial_00::createCamera(void)
{
    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCamera");
	
    mCamera->setPosition(Ogre::Vector3(0.1,1500,0.1));
    mCamera->lookAt(Ogre::Vector3(0.0001,0.1,0.1));

    mCamera->setNearClipDistance(5);

    mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller


	mCameraSmall = mSceneMgr->createCamera("PlayerCamSmall");
	mCameraSmall->setPosition(Ogre::Vector3(0.1,1500,0.1));
    mCameraSmall->lookAt(Ogre::Vector3(0.0001,0.1,0.1));
	mCameraSmall->setNearClipDistance(5);
	//mCameraManSmall = new OgreBites::SdkCameraMan(mCameraSmall);
}

void BasicTutorial_00::createViewports(void)
{
    Ogre::Viewport* vp = mWindow->addViewport(
		mCamera
		);


    vp->setBackgroundColour(Ogre::ColourValue(1.0, 1.0, 1.0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));



	Ogre::Viewport* viewportSmall = mWindow->addViewport(mCameraSmall,1, 0.75, 0, 0.25, 0.25);
	viewportSmall->setBackgroundColour(Ogre::ColourValue(1,1,1));
	viewportSmall->setOverlaysEnabled(false);
	mCameraSmall->setAspectRatio(Ogre::Real(viewportSmall->getActualWidth()) / Ogre::Real(viewportSmall->getActualHeight()));

}
void BasicTutorial_00::createScene(void) 
{

	// CHANG THIS!!!!!!!!!!!!!!!!!!!
	mSceneMgr->setAmbientLight( ColourValue( 0.25, 0.25, 0.25 ) );
	//mSceneMgr->setAmbientLight( ColourValue( 1, 1, 1 ) );

	// ground
	BasicTutorial_00::createDefaultPlane();
    Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
	entGround->setMaterialName("Examples/BumpyMetal");
	entGround->setCastShadows(false);
	entGround->setQueryFlags(0);

	BasicTutorial_00::createRowOfObjects("sphere.mesh", 0, 3, mSceneMgr, -600, "rowA");
	BasicTutorial_00::createRowOfObjects("sphere.mesh", 3, 3, mSceneMgr, -400, "rowB");
	BasicTutorial_00::createRowOfObjects("sphere.mesh", 6, 3, mSceneMgr, -200, "rowC");
	BasicTutorial_00::createRowOfObjects("sphere.mesh", 9, 3, mSceneMgr, 200, "rowD");
	BasicTutorial_00::createRowOfObjects("sphere.mesh", 12, 3, mSceneMgr, 400, "rowE");
	BasicTutorial_00::createRowOfObjects("sphere.mesh", 15, 3, mSceneMgr, 600, "rowF");

	mEntityArr[4]->setMaterialName("Examples/Green");
	mEntityArr[13]->setMaterialName("Examples/Yellow");

	mEntity 
		= mSceneMgr
		->createEntity( "Robot", "robot.mesh" ); 

	mEntity->setCastShadows(false);

	Light* spotLight = mSceneMgr->createLight("robotLight");
	spotLight->setType(Light::LT_SPOTLIGHT);
	spotLight->setDiffuseColour(ColourValue(1,1,1));
	spotLight->setSpecularColour(ColourValue(1,1,1));
	spotLight->setDirection(Vector3(300,0,0));
	spotLight->setCastShadows(true);

	sNode 
		= mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode( 
		"RobotNode", Vector3( 300, 0, 0 ) ); 

	SceneNode *sNodeChild 
		= sNode->createChildSceneNode( "LightNode", Vector3( 0, 0, 0 ) ); 

	sNode->attachObject( mEntity ); 
	sNodeChild->attachObject( spotLight );


	mAnimationState = mEntity->getAnimationState( "Idle" );
	mAnimationState->setLoop( true );
	mAnimationState->setEnabled( true );

	flag = false; //before starting particle system
}


bool BasicTutorial_00::frameStarted(const FrameEvent &evt)
{
	Ogre::Real randomNumber = Ogre::Math::RangeRandom(-1, 1);    
	Ogre::Real yPosition = sin(5*randomNumber);
	mSceneNodeArr[4]->translate(Vector3(0, yPosition, 0));
	mSceneNodeArr[13]->translate(Vector3(0, yPosition, 0));

	//check if collide
	for(int i=0; i<18; ++i){
		Real distanceBetweenRobotAndSphere = mSceneNodeArr[i]->getPosition().distance(sNode->getPosition());
		Real distanceThreshold = 50.0;

		if (distanceBetweenRobotAndSphere<distanceThreshold)
		{
			sNode->translate(-sNode->getPosition()*evt.timeSinceLastFrame);
		}
	}

	mAnimationState->addTime(evt.timeSinceLastFrame);
	if ( mKeyboard->isKeyDown(OIS::KC_W) ) {
		mAnimationState = mEntity->getAnimationState( "Walk" );
		mAnimationState->setLoop( true );
		mAnimationState->setEnabled( true );
		mDestination = sNode->getPosition();
		Vector3 direction = sNode->_getDerivedOrientation() * Vector3::UNIT_X;
		sNode->translate(Vector3(direction*0.5));
	}
	if ( mKeyboard->isKeyDown(OIS::KC_S) ) {
		mAnimationState = mEntity->getAnimationState( "Walk" );
		mAnimationState->setLoop( true );
		mAnimationState->setEnabled( true );
		mDestination = sNode->getPosition();
		Vector3 direction = sNode->_getDerivedOrientation() * Vector3::NEGATIVE_UNIT_X;
		sNode->translate(Vector3(direction*0.5));
	}
	if ( mKeyboard->isKeyDown(OIS::KC_A) ) {
		mAnimationState = mEntity->getAnimationState( "Walk" );
		mAnimationState->setLoop( true );
		mAnimationState->setEnabled( true );
		sNode->yaw(Degree(5));
	}
	if ( mKeyboard->isKeyDown(OIS::KC_D) ) {
		mAnimationState = mEntity->getAnimationState( "Walk" );
		mAnimationState->setLoop( true );
		mAnimationState->setEnabled( true );
		sNode->yaw(Degree(-5));
	}
	if ( mKeyboard->isKeyDown(OIS::KC_SPACE) ) {
		if(!flag){
			ParticleSystem* sunParticle = mSceneMgr->createParticleSystem("Sun", "Examples/GreenyNimbus");
			mSceneNodeArr[4]->attachObject(sunParticle);

			ParticleSystem* sunParticle2 = mSceneMgr->createParticleSystem("Sun2", "Examples/GreenyNimbus");
			mSceneNodeArr[13]->attachObject(sunParticle2);	
		}
		flag = true;
	}
	return true;
}

bool BasicTutorial_00::mouseMoved( const OIS::MouseEvent &arg )
{
	return BaseApplication::mouseMoved( arg);
}

bool BasicTutorial_00::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	return BaseApplication::mouseReleased( arg, id );
}

bool BasicTutorial_00::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	return BaseApplication::mousePressed( arg, id );
}

int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}


/*!
\brief Create a plane

Create a plane with default settings, which are: width 1200, height 1200, x-segment 20, y-segment 20, number of texture sets 1, x-tile 5, y-tile 5, upward vector Z axis

\return void
*/

void BasicTutorial_00::createDefaultPlane(void){
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 2000, 2000, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
}

/*!
\brief Create a series of objects that form a row

A row is formed by repeatedly rendering the same basic units of objects that are distributed evenly. The objects have varying heights that follow a cosine function to produce a wavy effect.

\param objectMesh The type of object that forms the circle
\param numObjects The number of basic units of objects
\param mSceneMgr The target scene manager

\return void
*/

void BasicTutorial_00::createRowOfObjects(Ogre::String objectMesh, Ogre::Real startingIndex, Ogre::Real numObjects, Ogre::SceneManager* mSceneMgr, float zPosition, Ogre::String prefix){
	Ogre::Real numCubes = numObjects;
	float PI = 3.141592654;
	float function;
	//float height;
	float xPosition;
	float scaleFactor;
	for (int i=startingIndex; i<startingIndex+numCubes; ++i){
		Ogre::String name=prefix+Ogre::StringConverter::toString(i);
		Ogre::Entity *ent = mSceneMgr->createEntity(name, objectMesh);
		ent->setMaterialName("Examples/Chrome");
		ent->setCastShadows(true);
		mEntityArr[i] = ent;
		Ogre::AxisAlignedBox boundingBox = ent->getBoundingBox();
		//Ogre::Real cubeSize = boundingBox.getMaximum().x - boundingBox.getMinimum().x;
		Ogre::SceneNode *sceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		mSceneNodeArr[i] = sceneNode;
		sceneNode->attachObject(ent);
		function = 2*i/(double)(numCubes-1);
		//height = (1+cos(function*PI*2))*20;
		//xPosition = function*255-255/2.0;
		//scaleFactor = 1.0/cubeSize/numCubes*255*0.8;
		sceneNode->scale(Vector3(0.5, 0.5, 0.5));
		sceneNode->setPosition((i-startingIndex)*200, 20, zPosition);
		//sceneNode->setPosition(xPosition, zPosition, -125);
	}
}
