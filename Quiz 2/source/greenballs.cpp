#include "greenballs.h"
#include "BasicTools.h"

GREENBALL::GREENBALL(SceneManager *a_SceneMgr) : GAME_OBJ(a_SceneMgr)
{
	direction = Vector3(Math::RangeRandom(-10,10),0,Math::RangeRandom(-10,10));
	//previousPosition = this->getInitPosition();
	speed = 0;
}

void GREENBALL::setAction(Ogre::String actionMode){
	if (actionMode == "Wandering"){
		this->setWandering();
	}
	else if (actionMode == "Chasing"){
		this->setChasing();
	}
	else if (actionMode == "Evading"){
		this->setEvading();
	}
	else if (actionMode == "Arrival"){
		this->setArrival();
	}
}

void GREENBALL::setWandering(){
	//get random angle and speed

	//set direction based on the angle

	//update velocity based on direction and speed
	actionPeriod = Math::RangeRandom(1,3);

	speed = Math::RangeRandom(10,15);
	
	angle = Math::RangeRandom(-30,30);
	direction = Quaternion(Degree(angle), Vector3::UNIT_Y) * direction;
	direction.y = 0;
	direction.normalise();

}

void GREENBALL::setChasing(){
	//get random angle and speed

	//set direction based on the angle

	//update velocity based on direction and speed
	actionPeriod = Math::RangeRandom(1,3);

	speed = Math::RangeRandom(10,15);

	Vector3 p0 = this->getPosition();
	Vector3 p1 = mGreenballTarget->getPosition();
	direction = p1 - p0;
	direction.y = 0;
	direction.normalise();

}

void GREENBALL::setEvading(){
	//get random angle and speed

	//set direction based on the angle

	//update velocity based on direction and speed
	actionPeriod = Math::RangeRandom(1,3);

	speed = Math::RangeRandom(10,15);

	Vector3 p0 = this->getPosition();
	Vector3 p1 = mGreenballTarget->getPosition();
	direction = p0 - p1;
	direction.y = 0;
	direction.normalise();

}

void GREENBALL::setArrival(){
	//get random angle and speed

	//set direction based on the angle

	//update velocity based on direction and speed
	actionPeriod = Math::RangeRandom(1,3);

	speed = Math::RangeRandom(10,15);

	Vector3 p0 = this->getPosition();
	Vector3 p1 = Vector3(500,120,500);
	direction = p1 - p0;
	direction.y = 0;
	direction.normalise();

}

/*
Update the position and view direction of the monster.
*/
void GREENBALL::update(const Ogre::FrameEvent& evt, Ogre::String actionType,  GAME_OBJ *a_Target)
{
	mGreenballTarget = a_Target;
	//check if (random number) cool down time is reached
	actionPeriod -= evt.timeSinceLastFrame;

	if(actionPeriod <= 0){
		
		this->setAction(actionType);
	}

	currentPosition = this->getPosition();



	//compute the position based on velocity, evt.time, and current position

	currentPosition = currentPosition + speed * direction * evt.timeSinceLastFrame;

	this->setPosition(currentPosition);
	
}