//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
#include "TutorialApplication.h"
#include "BasicTools.h"
#include "read_data.h"

using namespace Ogre;
BasicTutorial_00::BasicTutorial_00(void) {
	mFlgMotion = true;
	mToggle = false;
	mKeyPressed = false;


	mCameraDistance = 0;
	mKeyPressedZoomMode = 0;
	mCameraDistanceAdjustSpeed = 0;
	mCameraDistanceSlowDownSpeed = 0;
}

//
//handle the mouse motion (passive) event
//
bool BasicTutorial_00::mouseMoved( const OIS::MouseEvent &arg )
{
	bool flg = BaseApplication::mouseMoved(arg);
	return flg;
}

//handle the key pressed event
bool BasicTutorial_00::keyPressed( const OIS::KeyEvent &arg )
{
	bool flg = BaseApplication::keyPressed(arg);
	if (arg.key == OIS::KC_W && flg) {
		mGreenballMgr->setAction("Wandering");
		mRedball->setWandering();
	}

	if (arg.key == OIS::KC_C && flg) {
		mGreenballMgr->setAction("Chasing");
		mRedball->setWandering();

	}

	if (arg.key == OIS::KC_E && flg) {
		mGreenballMgr->setAction("Evading");
		mRedball->setWandering();

		
	}

	if (arg.key == OIS::KC_SPACE && flg) {
		if(mToggle == false){
			mGreenballMgr->setAction("Wandering");
		}
		else if(mToggle == true){
			mGreenballMgr->setAction("Arrival");
		}
	}

	return flg;
}

//handle the key released event
bool BasicTutorial_00::keyReleased( const OIS::KeyEvent &arg )
{
	bool flg = BaseApplication::keyReleased(arg);

	if (arg.key == OIS::KC_W && flg) {
		//unset?
		//mGreenballMgr->setWandering();
		//wandering
	}

	if (arg.key == OIS::KC_C && flg) {

		//chasing
	}

	if (arg.key == OIS::KC_E && flg) {

		//evading
		
	}

	if (arg.key == OIS::KC_SPACE && flg) {

		//wandering vs arrival
		if(mToggle == false){
			mToggle = true;
		}
		else if(mToggle == true){
			mToggle = false;
		}
	}

	if (arg.key == OIS::KC_ESCAPE)
	{
		mShutDown = true;
	}
	return flg;
}
void BasicTutorial_00::chooseSceneManager()
{
	mSceneMgrArr[0] = mRoot
		->createSceneManager(
		ST_EXTERIOR_CLOSE, "primary");
	mSceneMgrArr[1] =mSceneMgrArr[0];

}

void BasicTutorial_00::createCamera_00(void)
{
	mSceneMgr = mSceneMgrArr[0];
	mCamera = mCameraArr[0] = mSceneMgr->createCamera("PlayerCam");
	mCamera->setNearClipDistance(5);
	mCamera->setPosition(Ogre::Vector3(800,1000,800));
	mCamera->lookAt(Ogre::Vector3(500,0.001,800));
	mCameraManArr[0] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void BasicTutorial_00::createCamera_01(void)
{
	
	mSceneMgr = mSceneMgrArr[1];
	mCamera = mCameraArr[1] = mSceneMgr->createCamera("PlayerCam2");
	mCamera->setPosition(Ogre::Vector3(50,1500,50));
	mCamera->lookAt(Ogre::Vector3(0,0.001,0));
	mCamera->setNearClipDistance(5);

}



void BasicTutorial_00::createViewport_00(void)
{
	mCamera = mCameraArr[0];
	Ogre::Viewport* vp = mWindow->addViewport(
		mCamera,
		1,
		0,
		0,
		1,
		1
		);
	vp->setBackgroundColour(Ogre::ColourValue(1,1,1));

	Ogre::int32 mask = 0xFFFFFFF0;
	vp->setVisibilityMask(mask);

	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight())
	);

}

void BasicTutorial_00::createViewport_01(void)
{
	
	mCamera = mCameraArr[1];

	Ogre::Viewport* vp = mWindow->addViewport(
		mCamera,
		2,
		0.75,
		0,
		0.25,
		0.25
		);
	vp->setBackgroundColour(Ogre::ColourValue(1,1,1));
	vp->setOverlaysEnabled(false);

	
	Ogre::int32 mask = 0xFFFFFFFF;
	vp->setVisibilityMask(mask);

	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}



void BasicTutorial_00::createScene_00(void) 
{

	DATA_READER::readData(); //Read the data file here.
	bt_Init(mTrayMgr, mSceneMgrArr[0], mCameraArr[0]); //Set the pointers of the objects so that the other functions can use the objects.

	mSceneMgr = mSceneMgrArr[0];

	//fog and shadow
	/*
	if (DATA_READER::isEnabledExpFog()) {
		ColourValue fadeColour(0.9, 0.9, 0.9); 
		Real density = DATA_READER::getExpFogDensity();
		mSceneMgr->setFog(FOG_EXP, fadeColour, density); 
	}
	
	*/
	
	if (DATA_READER::isEnabledShadow()) {
		mSceneMgr->setShadowTechnique(
			SHADOWTYPE_TEXTURE_MODULATIVE);
		mSceneMgr->setShadowColour(ColourValue(0, 0, 0));
	}
	
	//terrian

	mSceneMgr->setWorldGeometry("terrain.cfg");

	mSceneMgr->setSkyBox(true, "Examples/TrippySkyBox");

	//lighting

	mSceneMgr->setAmbientLight( ColourValue( 1.0, 1.0, 1.0 ) ); 

	//water surface
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	Ogre::Entity* entGround = mSceneMgr->createEntity("GroundEntity", "ground");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
	entGround->setMaterialName("Examples/WaterStream");
	entGround->setCastShadows(false);

	//central sphere
	
	Entity* entSphere 
		= mSceneMgr
		->createEntity( "Sphere", "sphere.mesh" );
	mSN_Sphere
		= mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode( 
		"SphereNode", Vector3( 800, 500+DATA_READER::getWaterCoord_Y(), 800 ) ); 


	// red ball

	mRedball = new REDBALL(mSceneMgrArr[0]);
	mRedball->createGameObj("r", DATA_READER::getMeshName());
	mRedball->getEntity()->setMaterialName("Examples/red");
	mRedball->setVisible(true);
	mRedball->makeAlive(true);
	Vector3 pos;
	pos.x = 800;
	pos.z = 800;
	pos.y = 120;

	mRedball->setPosition(pos);
	mRedball->setInitPosition(pos);
	Real sx, sy, sz;
	sx = sy = sz = 5 * DATA_READER::getMeshScale();
	mRedball->scale(sx,sy,sz);

	// green balls


	mGreenballMgr = new GREENBALL_MANAGER(mSceneMgrArr[0]);

	mGreenballMgr->setMaxGreenballsNum(DATA_READER::getMaxMonstersNum());

	mGreenballMgr->setTargetForGreenballs(mRedball);

	//mRedballMgr = new REDBALL_MANAGER(mSceneMgrArr[0]);

}

void BasicTutorial_00::createScene_01(void) 
{
	return;
}

/*
Implement the game logic in this function.
*/
bool BasicTutorial_00::frameStarted(const Ogre::FrameEvent& evt)
{

	bool flg = Ogre::FrameListener::frameStarted(evt);
	mGreenballMgr->update(evt);
	mRedball->update(evt);
	return flg;
}

void BasicTutorial_00::createViewports(void)
{
	createViewport_00();
	//createViewport_01();
	mCamera = mCameraArr[0];
}

void BasicTutorial_00::createCamera(void) {
	createCamera_00();
	createCamera_01();
	mCameraMan = mCameraManArr[0];
	mCamera = mCameraArr[0];
}

void BasicTutorial_00::createScene( void ) {
	createScene_00();
	createScene_01();
	mSceneMgr = mSceneMgrArr[0]; // active SceneManager
}

void BasicTutorial_00::initParticleSystemForExplosion() {
	fNode = static_cast<SceneNode*>(
		mSceneMgr->getRootSceneNode()->createChild());
	ParticleSystem* p = mSceneMgr->createParticleSystem(
		"explosion", "Examples/Smoke");

	ParticleEmitter *e = p->getEmitter(0);
	e->setEnabled(false);
	fNode->attachObject(p);
	fNode->setPosition(Vector3::ZERO);
	fNode->setVisible(false);
}

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

int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}
