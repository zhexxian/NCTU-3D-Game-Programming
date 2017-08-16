#include "redballs.h"
#include "BasicTools.h"

REDBALL::REDBALL(SceneManager *a_SceneMgr) : GAME_OBJ(a_SceneMgr)
{
	
}

void REDBALL::setWandering(){

	actionPeriod = Math::RangeRandom(5,10);

	speed = Math::RangeRandom(10,15);
	
	angle = Math::RangeRandom(-30,30);
	direction = Quaternion(Degree(angle), Vector3::UNIT_Y) * direction;
	direction.y = 0;
	direction.normalise();
}

/*
Update the position and view direction of the monster.
*/
void REDBALL::update(const Ogre::FrameEvent& evt)
{
	actionPeriod -= evt.timeSinceLastFrame;

	
	if (actionPeriod <= 0){
		this->setWandering();
	}


	currentPosition = this->getPosition();



	//compute the position based on velocity, evt.time, and current position

	currentPosition = currentPosition + speed * direction * evt.timeSinceLastFrame;

	this->setPosition(currentPosition);
}