/*
-----------------------------------------------------------------------------
Filename:    BasicTutorial2.cpp
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
 
//#include "BasicTutorial.h"
#include "TutorialApplication.h"
//#include "OgreGamePlatform.h"

//-------------------------------------------------------------------------------------
BasicTutorial2::BasicTutorial2(void)
{
}
//-------------------------------------------------------------------------------------
BasicTutorial2::~BasicTutorial2(void)
{
}

/*!
\brief Choose the scene manager type

\return void
*/

void BasicTutorial2::chooseSceneManager(void)
{
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
	mSceneMgrSmall = mRoot->createSceneManager(Ogre::ST_GENERIC);
}

/*!
\brief Create the camera

Create the primary and secondary cameras

\return void
*/

//-------------------------------------------------------------------------------------
void BasicTutorial2::createCamera(void)
{
    // create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");
	mCameraSmall = mSceneMgrSmall->createCamera("PlayerCamSmall");
    // set its position, direction  
    mCamera->setPosition(Ogre::Vector3(120,300,600));
    mCamera->lookAt(Ogre::Vector3(120,0,0));
	mCameraSmall->setPosition(Ogre::Vector3(0,350,0));
    mCameraSmall->lookAt(Ogre::Vector3(0.0001,0,0));
}
//-------------------------------------------------------------------------------------

/*!
\brief Create the viewports

Create the primary and secondary viewports

\return void
*/

void BasicTutorial2::createViewports(void)
{
    // create the viewport
    Ogre::Viewport* viewport = mWindow->addViewport(mCamera,0);
	Ogre::Viewport* viewportSmall = mWindow->addViewport(mCameraSmall,1, 0.75, 0, 0.25, 0.25);
	// set its background color, overlay
    viewport->setBackgroundColour(Ogre::ColourValue(0,0,1));
    viewportSmall->setBackgroundColour(Ogre::ColourValue(0.5,0,0.5));
	viewportSmall->setOverlaysEnabled(false);
	// alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));  
	mCameraSmall->setAspectRatio(Ogre::Real(viewportSmall->getActualWidth()) / Ogre::Real(viewportSmall->getActualHeight()));
	// create a default camera controller
	mCameraMan = new OgreBites::SdkCameraMan(mCamera);   
}
//-------------------------------------------------------------------------------------

/*!
\brief Create the specific scene

Create the scene of penguins and cube

\return void
*/

void BasicTutorial2::createScene(void)
{
	// set ambient light and shadow
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	mSceneMgrSmall->setAmbientLight(Ogre::ColourValue(0, 0, 0));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	mSceneMgrSmall->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
 
	// create user-facing penguin
    Ogre::Entity* entPenguinFacingUser = mSceneMgr->createEntity("PenguinFacingUser", "penguin.mesh");
    entPenguinFacingUser->setCastShadows(true);
	Ogre::SceneNode* ogreNodePenguinFacingUser = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 50, 0));
	ogreNodePenguinFacingUser->setScale(2, 3, 2);
    ogreNodePenguinFacingUser->attachObject(entPenguinFacingUser);
	
	// create penguin-facing penguin
	Ogre::Entity* entPenguinFacingPenguin = mSceneMgr->createEntity("PenguinFacingPenguin", "penguin.mesh");
    entPenguinFacingPenguin->setCastShadows(true);
	Ogre::SceneNode* ogreNodePenguinFacingPenguin = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(150, 20, 0));
    ogreNodePenguinFacingPenguin->yaw(Ogre::Degree(-90));
	ogreNodePenguinFacingPenguin->attachObject(entPenguinFacingPenguin);


	// create circles and rows of cubes
	Ogre::Real numCubes = 72;
	BasicTutorial2::createCircleOfObjects("cube.mesh", numCubes, 100, mSceneMgr);
	BasicTutorial2::createRowOfObjects("cube.mesh", numCubes, mSceneMgr);


	// create plane
	BasicTutorial2::createDefaultPlane();

    Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);

    Ogre::Entity* entGroundSmall = mSceneMgrSmall->createEntity("SmallGroundEntity", "ground");
    mSceneMgrSmall->getRootSceneNode()->createChildSceneNode()->attachObject(entGroundSmall);


	// create cube for secondary viewport
	Ogre::Entity* entCube = mSceneMgrSmall->createEntity("Cube", "cube.mesh");
    entCube->setCastShadows(true);
	entCube->setMaterialName("Examples/Green");
	Ogre::SceneNode* entNodeCube = mSceneMgrSmall->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(50, 0, 0));
	entNodeCube->setScale(0.8,1.1,0.5);
	entNodeCube->attachObject(entCube);

 
	// create light
	BasicTutorial2::createPointLight("pointLightGreen", Ogre::Vector3(150, 250, 100), 0.0, 1.0, 0.0, mSceneMgr);
	BasicTutorial2::createPointLight("pointLightGrey", Ogre::Vector3(-150, 300, 250), 0.5, 0.5, 0.5, mSceneMgr);
	BasicTutorial2::createPointLight("pointLightForSmallViewpoint", Ogre::Vector3(100, 150, 250), 0.0, 0.0, 1.0, mSceneMgrSmall);
 
}

/*!
\brief Create a series of objects that form a circle

A circle is formed by repeatedly rendering the same basic units of objects that are distributed evenly. The objects have varying heights that follow a sine function to produce a wavy effect.

\param objectMesh The type of object that forms the circle
\param numObjects The number of basic units of objects
\param circleRadius The radius of the circle formed by objects
\param mSceneMgr The target scene manager

\return void
*/

void BasicTutorial2::createCircleOfObjects(Ogre::String objectMesh, Ogre::Real numObjects, float circleRadius, Ogre::SceneManager* mSceneMgr) {
	Ogre::Real numCubes = numObjects;
	float PI = 3.141592654;
	float function;
	float height;
	float xPosition;
	float zPosition;
	float scaleFactor;
	for (int i=0; i<numCubes; ++i){
		Ogre::String name="cubeCircle"+ Ogre::StringConverter::toString(i);
		Ogre::Entity *ent = mSceneMgr->createEntity(name, objectMesh);
		ent->setMaterialName("Examples/SphereMappedRustySteel");
		Ogre::AxisAlignedBox boundingBox = ent->getBoundingBox();
		Ogre::Real cubeSize = boundingBox.getMaximum().x - boundingBox.getMinimum().x;
		Ogre::SceneNode *sceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		sceneNode->attachObject(ent);
		function = i/(double)(numCubes-1);
		height = (1+sin(function*PI*4))*50;
		xPosition = circleRadius*cos(function*PI*2);
		zPosition = circleRadius*sin(function*PI*2);
		scaleFactor = 1.0/cubeSize/numCubes*255*0.8;
		sceneNode->scale(scaleFactor, height/cubeSize, scaleFactor);
		sceneNode->setPosition(xPosition, 50, zPosition);
	}
}

/*!
\brief Create a series of objects that form a row

A row is formed by repeatedly rendering the same basic units of objects that are distributed evenly. The objects have varying heights that follow a cosine function to produce a wavy effect.

\param objectMesh The type of object that forms the circle
\param numObjects The number of basic units of objects
\param mSceneMgr The target scene manager

\return void
*/

void BasicTutorial2::createRowOfObjects(Ogre::String objectMesh, Ogre::Real numObjects, Ogre::SceneManager* mSceneMgr){
	Ogre::Real numCubes = numObjects;
	float PI = 3.141592654;
	float function;
	float height;
	float xPosition;
	float scaleFactor;
	for (int i=0; i<numCubes; ++i){
		Ogre::String name="cubeRow"+ Ogre::StringConverter::toString(i);
		Ogre::Entity *ent = mSceneMgr->createEntity(name, objectMesh);
		ent->setMaterialName("Examples/Chrome");
		Ogre::AxisAlignedBox boundingBox = ent->getBoundingBox();
		Ogre::Real cubeSize = boundingBox.getMaximum().x - boundingBox.getMinimum().x;
		Ogre::SceneNode *sceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		sceneNode->attachObject(ent);
		function = 2*i/(double)(numCubes-1);
		height = (1+cos(function*PI*2))*20;
		xPosition = function*255-255/2.0;
		scaleFactor = 1.0/cubeSize/numCubes*255*0.8;
		sceneNode->scale(scaleFactor, height/cubeSize, scaleFactor);
		sceneNode->setPosition(xPosition, 20, 125);
	}
}


/*!
\brief Create a plane

Create a plane with default settings, which are: width 1500, height 1500, x-segment 20, y-segment 20, number of texture sets 1, x-tile 5, y-tile 5, upward vector Z axis

\return void
*/

void BasicTutorial2::createDefaultPlane(void){
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
}

/*!
\brief Create a point light

A point light with default setting (type point light) is created with specific parameters

\param name The unique name for the light
\param position The location where the point light shines from
\param redValue R in RGB value
\param greenValue B in RGB value
\param blueValue G in RGB value
\param mSceneMgr The target scene manager

\return void
*/

void BasicTutorial2::createPointLight(Ogre::String name, Ogre::Vector3 position, float redValue, float greenValue, float blueValue, Ogre::SceneManager* mSceneMgr){
	Ogre::SceneManager* mSceneMgrTarget = mSceneMgr;
	Ogre::Light* pointLight = mSceneMgrTarget->createLight(name);
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(position);
    pointLight->setDiffuseColour(redValue, greenValue, blueValue);
    pointLight->setSpecularColour(redValue, greenValue, blueValue);
}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif
 

#ifdef __cplusplus
extern "C" {
#endif

//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
//    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
//#else
    int main(int argc, char *argv[])
//#endif
    {
        // Create application object
        BasicTutorial2 app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
			/*
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
				*/
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
