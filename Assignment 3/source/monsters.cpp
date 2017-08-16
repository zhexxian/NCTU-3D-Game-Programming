#include "monsters.h"
#include "BasicTools.h"

MONSTER::MONSTER(SceneManager *a_SceneMgr) : GAME_OBJ(a_SceneMgr)
{
}

/*
Update the view direction of the monster.
*/
void MONSTER::updateViewDirection()
{
    
}

void MONSTER::lookAt(Vector3 direction)
{
    mSceneNode->lookAt(direction,  Node::TS_WORLD);
}

/*
Update the position and view direction of the monster.
*/
void MONSTER::update(const Ogre::FrameEvent& evt, Vector3 monsterPosition, Vector3 targetPosition)
{
    //compute the position of the monster

	Vector3 actualDirection = monsterPosition - targetPosition;


	//Vector3 actualDirection = mQuaternion*mInitDirection;

	
	//BEGIN: BUG FIXED VERSION
	Vector3 p = mSceneNode->getPosition();
	actualDirection.y = 0.0;
	
	mSceneNode->lookAt(p+ actualDirection*10, Node::TS_WORLD);

    updateViewDirection();
}