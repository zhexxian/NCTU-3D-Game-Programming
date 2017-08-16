#include "BasicTools.h"

using namespace Ogre;

void genNameUsingIndex(const Ogre::String & prefix, int index, Ogre::String &out_name)
{
	out_name= prefix + Ogre::StringConverter::toString(static_cast<int>(index));
}

Ogre::SceneNode* initParticleSystem(
	Ogre::SceneManager *sceneMgr,
	const Ogre::String particleScriptName
	) 
{
	SceneNode* objectSceneNode = static_cast<SceneNode*>(
		sceneMgr->getRootSceneNode()->createChild());

	ParticleSystem* p = sceneMgr->createParticleSystem(
		"explosion", "Examples/Smoke");

	Ogre::ParticleEmitter *e = p->getEmitter(0);
	e->setEnabled(false);
	objectSceneNode->attachObject(p);
	objectSceneNode->setPosition(Vector3::ZERO);
	objectSceneNode->setVisible(false);
	return objectSceneNode;
}

void setOffParticleSystem(
	Ogre::SceneNode *objectSceneNode, const Ogre::String &particleScriptName, const Ogre::Vector3 &pos) 
{
	objectSceneNode->setPosition(pos);
	objectSceneNode->setVisible(true);
	MovableObject *s = objectSceneNode->getAttachedObject(particleScriptName);
	ParticleSystem* p =static_cast<ParticleSystem*>(s);
	if (p == NULL) return;
	p->setVisible(true);
	ParticleEmitter *e = p->getEmitter(0);
	e->setEnabled(true);
}
/*
    mSceneMgr->setFog(Ogre::FOG_EXP2, fadeColour, 1.0, 10, 100); 
	mSceneMgr->setWorldGeometry("terrain.cfg");
*/
/*
	mSceneMgr->setShadowTechnique(
		SHADOWTYPE_STENCIL_ADDITIVE); 
*/

/*
	light = mSceneMgr->createLight("Light2"); 
	light->setType(Light::LT_POINT); 
	light->setPosition(Vector3(100, 150, 250)); 
	light->setDiffuseColour(1.0, 1.0, 1.0);		//green
	light->setSpecularColour(1.0, 1.0, 1.0);	//green
*/

/*
	Plane plane(Vector3::UNIT_Y, 0); 
	MeshManager::getSingleton().createPlane(
		"ground", 
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
		plane, 
		1500,1500, 	// width, height
		5,10, 		// x- and y-segments
		true, 		// normal
		1, 		// num texture sets
		2,10, 		// x- and y-tiles
		Vector3::UNIT_Z	// upward vector
		); 

	Entity *ent = mSceneMgr->createEntity(
		"GroundEntity", "ground"); 
	ent->setMaterialName("Examples/CloudySky");
*/

/*
	//mSceneMgr->setWorldGeometry("terrain.cfg");  
	//mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8); 
    mSceneMgr->setSkyBox(true, "Examples/MySky"); 
*/

/*
// Ray Query
	Ray mRay =mTrayMgr->getCursorRay(mCamera);

	RaySceneQuery *mRaySceneQuery = 
		mSceneMgr->createRayQuery ( Ray() ); 

	mRaySceneQuery->setRay(mRay);
	// Perform the scene query
	RaySceneQueryResult &result = 
		mRaySceneQuery->execute();
	RaySceneQueryResult::iterator itr = result.begin();

	// Get the results, set the camera height
	// We are interested in the first intersection. It is ok to traverse all the results.
	if (itr != result.end() && itr->worldFragment)
	{
		mSceneNode->setPosition(itr->worldFragment->singleIntersection);
		
	}

//End Ray Query
*/////////////////////////////////////

//Begin Simple Selection
/*
bool BasicTutorial_00::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	Ray mRay = mTrayMgr->getCursorRay(mCamera);

	RaySceneQuery *mRaySceneQuery = mSceneMgr->createRayQuery ( Ray() ); 

	mRaySceneQuery->setSortByDistance(true); 

	mRaySceneQuery->setRay(mRay);
	// Perform the scene query
	RaySceneQueryResult &result = mRaySceneQuery->execute();
	RaySceneQueryResult::iterator itr = result.begin();

	// Get the results, set the camera height
	// We are interested in the first intersection. It is ok to traverse all the results.
	for (itr = result.begin(); itr != result.end(); itr++)
	{

		if (itr->movable && itr->movable->getName().substr(0, 5) != "tile[")
		{
			mCurrentObject = itr->movable->getParentSceneNode();
			bool flgShow = mCurrentObject->getShowBoundingBox();
			mCurrentObject->showBoundingBox(!flgShow);
			break;
		} // if
		else if (itr->worldFragment) {
			//
		}
	}


	return BaseApplication::mousePressed( arg, id );
	
}
*/
//End Simple Selection

/*
    mSceneNode->lookAt( q, Node::TS_WORLD );
*/