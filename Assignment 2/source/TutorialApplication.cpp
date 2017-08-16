//
// Student Name: Zhang Zhexian
// Student ID: 0545080
// Student Email Address: zhangzhexian@outlook.com
//
//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
#include "TutorialApplication.h"
#include "BasicTools.h"
#include "Windows.h"
#include "MMSystem.h"

#if defined(_MSC_VER)
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "shlwapi.lib")
#endif

using namespace Ogre;
using namespace std;
BasicTutorial_00::BasicTutorial_00(void) {
	mSound = new SOUND;
	mSound->init();
}


/*!
\brief Create the camera

Create the primary and secondary cameras

\return void
*/
void BasicTutorial_00::createCamera(void)
{
	mCamera = mSceneMgr->createCamera("PlayerCamera");
	mCamera->setPosition(Ogre::Vector3(0,700,800));
	mCamera->lookAt(Ogre::Vector3(0,0,0));
	mCamera->setNearClipDistance(0.1);
	mCamera->setFarClipDistance(50000);
	mCameraMan = new OgreBites::SdkCameraMan(mCamera);

	mCameraSmall = mSceneMgrSmall->createCamera("PlayerCamSmall");
	mCameraSmall->setPosition(Ogre::Vector3(0,1400,0));
    mCameraSmall->lookAt(Ogre::Vector3(0.0001,0,0));
	mCameraSmall->setNearClipDistance(5);
	mCameraManSmall = new OgreBites::SdkCameraMan(mCameraSmall);
}

/*!
\brief Create the viewports

Create the primary and secondary viewports

\return void
*/
void BasicTutorial_00::createViewports(void)
{
	Ogre::Viewport* vp;
	vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

	Ogre::Viewport* viewportSmall = mWindow->addViewport(mCameraSmall,1, 0.75, 0, 0.25, 0.25);
	viewportSmall->setBackgroundColour(Ogre::ColourValue(1,1,0));
	viewportSmall->setOverlaysEnabled(false);
	vp->setSkiesEnabled(false);
	mCameraSmall->setAspectRatio(
		Ogre::Real(viewportSmall->getActualWidth())*4 / Ogre::Real(viewportSmall->getActualHeight()));

}


/*!
\brief Create the specific scene

Create the scene of penguins and cube

\return void
*/


void BasicTutorial_00::createScene(void) 
{
	mSceneMgr->setAmbientLight( ColourValue( 0.6, 0.6, 0.6 ) ); 
	Ogre::ColourValue fadeColour(0.7, 0.7, 0.7);
	mSceneMgr->setFog(Ogre::FOG_LINEAR, fadeColour, 0.0, 1400, 1600);
	/*
	mSceneMgr->setSkyBox(
		true, 
		"Examples/SpaceSkyBox"); 
	*/
	mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
	mSceneMgr->setShadowTechnique(
		SHADOWTYPE_STENCIL_ADDITIVE); 
	mSceneMgr->setShadowColour(ColourValue(0, 0, 0));

	mSceneMgrSmall->setAmbientLight(Ogre::ColourValue(1, 1, 1));
	//mSceneMgrSmall->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	mSceneMgrSmall->setSkyDome(false,"Examples/CloudySky", 5, 8);

	// ground
	BasicTutorial_00::createDefaultPlane();
    Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
	entGround->setMaterialName("Examples/BumpyMetal");
	entGround->setCastShadows(false);
	entGround->setQueryFlags(0);
	

	// 2 circles of robots
	Ogre::Real numRobots = 30;
	BasicTutorial_00::createCircleOfObjects("robot.mesh", 0, numRobots, 300, mSceneMgr, "outerRobot");
	BasicTutorial_00::createCircleOfObjects("robot.mesh", numRobots, numRobots, 200, mSceneMgr, "innerRobot");
	mSceneMgr->getRootSceneNode()->getChild(0)->scale(2, 2, 2);

	// central sphere
	Ogre::Entity* entSphere = mSceneMgr->createEntity("sphere", "sphere.mesh");
    entSphere->setCastShadows(true);
	Ogre::SceneNode* ogreNodeSphere = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 50, 0));
	ogreNodeSphere->setScale(Ogre::Vector3(0.7,0.7,0.7));
    ogreNodeSphere->attachObject(entSphere);
	entSphere->setMaterialName("Examples/SphereMappedRustySteel");
	entSphere->setQueryFlags(0);

	// rotating light

	Ogre::Light* rotatingLight = mSceneMgr->createLight("AnimLight");
	//light->setType(Ogre::Light::LT_DIRECTIONAL);
	rotatingLight->setType(Light::LT_POINT);
	rotatingLight->setDiffuseColour(ColourValue(1,1,1));
	rotatingLight->setSpecularColour(ColourValue(1,1,1));
	rotatingLight->setCastShadows(true);

	Ogre::SceneNode* ogreNodeParentLight = mSceneMgr->getRootSceneNode()->createChildSceneNode("parentLight", Ogre::Vector3(0, 0, 0));
    Ogre::SceneNode* ogreNodeLight = ogreNodeParentLight->createChildSceneNode(Ogre::Vector3(0, 0, 0));
	ogreNodeLight->attachObject(rotatingLight);
	ogreNodeLight->translate(Ogre::Vector3(-1000,500,0));
	

	// selection rectangle
	mSelectionRect = new SelectionRectangle("selectionRect");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(mSelectionRect);
	mSelectionRect->setLightMask(0);
	mSelectionRect->setCastShadows(false);

	// bounding box & volume selection
	PlaneBoundedVolumeList volList;
	mVolQuery = mSceneMgr->createPlaneBoundedVolumeQuery(volList);
	mCurrentObject = mSceneNodeArr[0];

	// particle system
	ParticleSystem* sunParticle = mSceneMgr->createParticleSystem("Sun", "Examples/GreenyNimbus");
	mSceneNodeArr[0]->attachObject(sunParticle);
}

bool BasicTutorial_00::mouseMoved( const OIS::MouseEvent &arg )
{

	Ray mRay =mTrayMgr->getCursorRay(mCamera);

	Vector2 scn = mTrayMgr->sceneToScreen(mCamera, mRay.getOrigin());
	left = scn.x;
	top = scn.y;
	mSelectionRect->setCorners(left, top, right, bottom);

	//only show the selection area when mouse is pressed
	mSelectionRect->setVisible(isMousePressed);

	return BaseApplication::mouseMoved( arg);

}


bool BasicTutorial_00::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	mSelectionRect->clear();
	if (id == OIS::MB_Right)
	{
		Real x = arg.state.X.abs;
		Real y = arg.state.Y.abs; 

		Ogre::Real screenWidth = Ogre::Root::getSingleton().getAutoCreatedWindow()->getWidth();
		Ogre::Real screenHeight = Ogre::Root::getSingleton().getAutoCreatedWindow()->getHeight();

		// convert to 0-1 offset
		Ogre::Real offsetX = x / screenWidth;
		Ogre::Real offsetY = y / screenHeight;

		// set up the ray
		Ray mouseRay = mCamera->getCameraToViewportRay(offsetX, offsetY);

		// check if the ray intersects our plane
		// intersects() will return whether it intersects or not (the bool value) and
		// what distance (the Real value) along the ray the intersection is

		Plane plane(Vector3::UNIT_Y,0);
		//Ogre::TerrainGroup::RayResult result = plane->rayIntersects(mouseRay);
		std::pair<bool, Real> result = mouseRay.intersects(plane);

/*
		SceneNode::ChildNodeIterator childNodeIterator = mSceneMgr->getRootSceneNode()->getChildIterator();

		while (childNodeIterator.hasMoreElements())
		{
			String nameNode = childNodeIterator.getNext()->getName();
			if (mSceneMgr->getSceneNode(nameNode)->getShowBoundingBox())
			{
				Vector3 destination = mSceneNodeArr[10] -> getPosition();
				mSceneMgr->getSceneNode(nameNode)->setPosition(destination);
			}
		}
*/
		if(result.first) {
			// if the ray intersect the plane, we have a distance value
			// telling us how far from the ray origin the intersection occurred.
			// the last thing we need is the point of the intersection.
			// Ray provides us getPoint() function which returns a point
			// along the ray, supplying it with a distance value.

			// get the point where the intersection is
			mDestination = mouseRay.getPoint(result.second);

			//mDestination = Vector3(0,0,0);
			for (int robotCounter=0; robotCounter<60; robotCounter++)
			{
				if (mSceneNodeArr[robotCounter]->getShowBoundingBox())
				{
					mAnimationState[robotCounter] = mEntityArr[robotCounter]->getAnimationState("Walk");
					mAnimationState[robotCounter]->setLoop(true);
					mAnimationState[robotCounter]->setEnabled(true);
					robotIsWalking[robotCounter] = true;
					mDirection[robotCounter] = mDestination - mSceneNodeArr[robotCounter]->getPosition();
					mDistance[robotCounter] = mDirection[robotCounter].normalise();
				}
			}
		}

		

	}
	else if (id == OIS::MB_Left)
	{
		isMousePressed = false;
		if (left==right && top==bottom) {
			return BaseApplication::mouseReleased( arg, id );
		
		}

		//USING mTrayMgr=============
		Real nleft = left;
		Real nright = right;
		Real ntop = 1+top;
		Real nbottom = 1+bottom;

		Ray topLeft = mTrayMgr->screenToScene(mCamera, Vector2(nleft, ntop));
		Ray topRight = mTrayMgr->screenToScene(mCamera, Vector2(nright, ntop));
		Ray bottomLeft = mTrayMgr->screenToScene(mCamera, Vector2(nleft, nbottom));
		Ray bottomRight = mTrayMgr->screenToScene(mCamera, Vector2(nright, nbottom));
		//End Using mTrayMgr=============

		// The plane faces the counter clockwise position.
		PlaneBoundedVolume vol;
		int np = 100;
		vol.planes.push_back(Plane(topLeft.getPoint(3), topRight.getPoint(3), 			bottomRight.getPoint(3)));         // front plane
		vol.planes.push_back(Plane(topLeft.getOrigin(), topLeft.getPoint(np), 	topRight.getPoint(np)));         // top plane
		vol.planes.push_back(Plane(topLeft.getOrigin(), bottomLeft.getPoint(np), 	topLeft.getPoint(np)));       // left plane
		vol.planes.push_back(Plane(bottomLeft.getOrigin(), bottomRight.getPoint(np), 	bottomLeft.getPoint(np)));   // bottom plane
		vol.planes.push_back(Plane(bottomRight.getOrigin(), topRight.getPoint(np), 	bottomRight.getPoint(np)));     // right plane 

		PlaneBoundedVolumeList volList;
		volList.push_back(vol);
		mVolQuery->setVolumes(volList);

		SceneQueryResult result = mVolQuery->execute();

		SceneQueryResultMovableList::iterator itr = result.movables.begin();


		// Get the results, set the camera height
		// We are interested in the first intersection. It is ok to traverse all the results.
	
		for (itr = result.movables.begin(); itr != result.movables.end(); ++itr)
		{
			if (*itr)
			{
				mCurrentObject = (*itr)->getParentSceneNode();
				bool flgShow = mCurrentObject->getShowBoundingBox();
				mCurrentObject->showBoundingBox(!flgShow);
			}
		}
		PlaySound((LPCSTR) "stereo.wav", NULL, SND_FILENAME | SND_ASYNC);
	}

	return BaseApplication::mouseReleased( arg, id );

}

bool BasicTutorial_00::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	isMousePressed = true;

	if (id == OIS::MB_Right)
	{
		return BaseApplication::mousePressed( arg, id );
	}
	else if (id == OIS::MB_Left)
	{
		for (int a=0; a<60; a++)
		{
			if (!robotIsWalking[a])
			{
				mSceneNodeArr[a]->showBoundingBox(false);
			}
		}
		mSelectionRect->clear();
		
		Ray mRay =mTrayMgr->getCursorRay(mCamera);

		Vector2 scn = mTrayMgr->sceneToScreen(mCamera, mRay.getOrigin());
		initX = scn.x;
		initY = scn.y;
/*
		if (left>right)
		{
			swap(left,right);
		}
		if (top>bottom)
		{
			swap(top,bottom);
		}
*/
		mSelectionRect->setCorners(initX, initY, initX, initY);
		right = initX;
		bottom = initY;
	}
	return BaseApplication::mousePressed( arg, id );
}

//void BasicTutorial_00::singleClickSelect ( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
//{
//}

//void BasicTutorial_00::volumeSelect(const OIS::MouseEvent &arg, OIS::MouseButtonID id )
//{
//}


/*!
\brief This function is trigerred right before the frame is drawn
Moves the robot with a walking animation (if robot is walking)
Plays idle animation (if robot is not walking)

\param FrameEvent

\return bool 
*/

bool BasicTutorial_00::frameStarted(const FrameEvent &evt)
{
	mSceneMgr->getRootSceneNode()->getChild("parentLight")->yaw(Ogre::Degree(0.1));
    
	//mDeltaTime=evt.timeSinceLastFrame;
	for (int robotCounter=0; robotCounter<60; robotCounter++)
	{	
		if (robotIsWalking[robotCounter])
		{
			mAnimationState[robotCounter] = mEntityArr[robotCounter]->getAnimationState("Walk");
			//determine how far to move this frame
			float mWalkSpeed = 40.0;
			float move = mWalkSpeed * evt.timeSinceLastFrame;
			mDistance[robotCounter] -= move;
			//Alternatively, use dot product here
			if (mDistance[robotCounter] <= 0.0f)
			{
				//Check to see if we've arrived at a waypoint
				//set our node to the destination we've just reached & reset direction to 0
				mSceneNodeArr[robotCounter]->setPosition(mDestination);
				mDirection[robotCounter] = Vector3::ZERO;
				robotIsWalking[robotCounter] = false;          
				mSceneNodeArr[robotCounter]->showBoundingBox(false);
				//playSound
				int totalRobotIsWalking = 0;
				for (int a=0; a<60; a++)
				{
					if (robotIsWalking[a])
					{
						totalRobotIsWalking++;
					}
				}
				if (totalRobotIsWalking==0)
				{
					PlaySound((LPCSTR) "stereo.wav", NULL, SND_FILENAME | SND_ASYNC);
				}
			}
			else
			{
				//check if collide
				Real distanceBetweenRobotAndSphere = mSceneNodeArr[robotCounter]->getPosition().distance(Ogre::Vector3(0, 50, 0));
				Real distanceThreshold = 70.0;

				if (distanceBetweenRobotAndSphere<distanceThreshold)
				{
					mSceneNodeArr[robotCounter]->translate(mSceneNodeArr[robotCounter]->getPosition() * evt.timeSinceLastFrame);
				}
				else
				{
					//movement code goes here
					mSceneNodeArr[robotCounter]->translate(mDirection[robotCounter] * move);
				}
				mDirection[robotCounter] = mDestination - mSceneNodeArr[robotCounter]->getPosition();
				mDistance[robotCounter] = mDirection[robotCounter].normalise();

				//Rotation code goes here
				Vector3 src = mSceneNodeArr[robotCounter]->getOrientation() * Vector3::UNIT_X;
				src.y=0;
				mDirection[robotCounter].y=0;
				src.normalise();
				//mDistance[robotCounter] = mDirection[robotCounter].normalise();
				// fix the divide by zero error bug
				if (abs(1.0f + src.dotProduct(mDirection[robotCounter])) < 0.0001f)
				{
					mSceneNodeArr[robotCounter]->yaw(Degree(180));
				}
				else
				{
					Quaternion quat = src.getRotationTo(mDirection[robotCounter]);
					mSceneNodeArr[robotCounter]->rotate(quat);
				}
			}
		}
		else
		{	
			mAnimationState[robotCounter] = mEntityArr[robotCounter]->getAnimationState("Idle");
		}
		mAnimationState[robotCounter]->addTime(evt.timeSinceLastFrame);
		mAnimationState[robotCounter]->setLoop(true);
		mAnimationState[robotCounter]->setEnabled(true);
	}
	
	
	return BaseApplication::frameStarted(evt);
}


void BasicTutorial_00::initParticleSystemForExplosion() {
	mParticleNode = static_cast<SceneNode*>(
		mSceneMgr->getRootSceneNode()->createChild());
	ParticleSystem* p = mSceneMgr->createParticleSystem(
		"explosion", "Examples/GreenyNimbus");

	ParticleEmitter *e = p->getEmitter(0);
	e->setEnabled(false);
	mParticleNode->attachObject(p);
	mParticleNode->setPosition(Vector3::ZERO);
	mParticleNode->setVisible(false);
}

/*
void setupSound()
{
	soundMgr = SoundManager::createManager();
 
	std::cout << soundMgr->listAvailableDevices();
 
	soundMgr->init();
	soundMgr->setAudioPath( (char*) ".\\" );
 
            // Just for testing
	unsigned int audioId;
	soundMgr->loadAudio( "Explosion.wav", &audioId, true);
            soundMgr->playAudio( audioId, false );
}
*/

/*!
\brief Set off particle system for special effect

\param fNode Scene node
\param pname Entity name
\param pos Position

\return void
*/

void BasicTutorial_00::setOffParticleSystem(
	Ogre::SceneNode *fNode, const Ogre::String &pname, const Ogre::Vector3 &pos) 
{
	fNode->setPosition(pos);
	fNode->setVisible(true);
	MovableObject *s = fNode->getAttachedObject(pname);
	ParticleSystem* p =static_cast<ParticleSystem*>(s);
	if (p == NULL) return;
	p->setVisible(true);
	ParticleEmitter *e = p->getEmitter(0);
	e->setEnabled(true);
}

/*!
\brief Create a plane

Create a plane with default settings, which are: width 1200, height 1200, 
x-segment 20, y-segment 20, number of texture sets 1, x-tile 5, y-tile 5, 
upward vector Z axis

\return void
*/

void BasicTutorial_00::createDefaultPlane(void){
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("ground", 
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 1200, 1200, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
}

/*!
\brief Create a series of objects that form a circle

A circle is formed by repeatedly rendering the same basic units of objects that are 
distributed evenly. The objects have varying heights that follow a sine function to 
produce a wavy effect.

\param objectMesh The type of object that forms the circle
\param numObjects The number of basic units of objects
\param circleRadius The radius of the circle formed by objects
\param mSceneMgr The target scene manager

\return void
*/

void BasicTutorial_00::createCircleOfObjects(Ogre::String objectMesh, 
	Ogre::Real startingIndex, Ogre::Real numObjects, float circleRadius, 
	Ogre::SceneManager* mSceneMgr, Ogre::String prefix) {
	float PI = 3.141592654;
	float function;
	float height;
	float xPosition;
	float zPosition;
	float scaleFactor;
	for (int i=startingIndex; i<startingIndex+numObjects; ++i){
		Ogre::String name=prefix+Ogre::StringConverter::toString(i);
		Ogre::Entity *ent = mSceneMgr->createEntity(name, objectMesh);
		mEntityArr[i] = ent;
		ent->setCastShadows(true);
		Ogre::AxisAlignedBox boundingBox = ent->getBoundingBox();
		Ogre::SceneNode *sceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		mSceneNodeArr[i] = sceneNode;
		sceneNode->attachObject(ent);
		function = i/(double)(numObjects-1);
		xPosition = circleRadius*cos(function*PI*2);
		zPosition = circleRadius*sin(function*PI*2);
		sceneNode->setPosition(xPosition, 50, zPosition);
		sceneNode->lookAt(Ogre::Vector3(0, 50, 0),Node::TS_PARENT, Vector3::UNIT_X);
		mAnimationState[i] = mEntityArr[i]->getAnimationState("Idle");
		mAnimationState[i]->setLoop(true);
		mAnimationState[i]->setEnabled(true);
	}
}

int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}
