#include "weapons.h"
#include "BasicTools.h"
#include "sound.h"

WEAPON::WEAPON(SceneManager *a_SceneMgr) : GAME_OBJ(a_SceneMgr)
{
	mSound = new SOUND;
	mSound->init();
}

//return true if it hits the sphere with radius r.
bool WEAPON::hitTarget_Sphere(const Vector3 &p, Real r )
{
	bool flg = false;

	Vector3 pos = mSceneNode->getPosition();
	if ( r >= pos.distance( p ) ) {
		Vector3 normal_dir = pos - p;
		normal_dir.normalise( );
		Vector3 new_pos = p + (r+0.5)*normal_dir; 
		mSceneNode->setPosition( new_pos );
		Real d = mVelocity.dotProduct( normal_dir );
		if ( 0.0 >= d ) {
			mVelocity = mVelocity - d*normal_dir;
		}
		flg = true;
		mSound->play();
	}
	/*

		Vector3 p0 = this->getPosition();
		Vector3 p1 = p;
		Vector3 mm = p0 - p1;
		Real d = mm.length();
		if (d < r + 5) {
			flg = true;
		}
	*/

	return flg;




}

//
// Decrease its life and disable it if its life is negative
// Compute the position of the weapon
// Check collision between it and the terrain surface
// Adjust its position if it his the terrain surface
//
//
void WEAPON::update(const Ogre::FrameEvent& evt)
{
	
	this->mLifeTime -= evt.timeSinceLastFrame;
	if (mLifeTime < 0 ) {
		mLifeTime = 0;
		mSceneNode->setVisible(false);
		mIsAlive = false;
		logMessage("*********NOT ALIVE**************");
		return;
	}

	timeSinceBulletFiring += evt.timeSinceLastFrame;
	//Trajectory
	//Vector3 position = this->getPosition();
	//bool flg = projectScenePointOntoTerrain_PosDirection(position);
	bool flg = true;
	if (flg) {
		if (hitTarget_Sphere(this->getPosition(),100)){
			
		}
		
		Vector3 position = this->getPosition();

		Vector3 velocity = this->mVelocity*7;
		Vector3 a = Vector3(0,-1,0);
	
		velocity.y = -this->mVelocity.y*0.9;
		position = (this->getPosition())+velocity*timeSinceBulletFiring+a*timeSinceBulletFiring*timeSinceBulletFiring;
		if(projectScenePointOntoTerrain_PosDirection(position))
		{
			velocity = velocity * 0.8;
			position = (this->getPosition())+Vector3(velocity.x, -velocity.y, velocity.z);
		}
		
	    this->setPosition(position);
	}
}