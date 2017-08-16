#include "greenball_manager.h"
#include "read_data.h"

GREENBALL_MANAGER::GREENBALL_MANAGER(SceneManager *a_SceneMgr): GAME_OBJ(a_SceneMgr)
{

	mGreenballsTarget = 0;
	mCurGreenballsNum = mNumGreenballs = 100;
	for (int i = 0; i < mNumGreenballs; ++i) 
	{
		mLifeStateArr[i] = true;
		mGreenballsArr[i] = new GREENBALL(a_SceneMgr);
		mGreenballsArr[i]->createGameObj("g", DATA_READER::getMeshName());
		mGreenballsArr[i]->getEntity()->setMaterialName("Examples/green");
		greenballTotalTranslation[i];
		Vector3 org(750, 100, 750);
		Vector3 pos;
		Real x = -1+2*(rand()%100)/100.0;
		Real z = -1+2*(rand()%100)/100.0;
		pos.x = 700*x;
		pos.z = 700*z;
		pos.y = 20;

		mGreenballsArr[i]->setPosition(pos+org);
		mGreenballsArr[i]->setInitPosition(pos+org);
		Real sx, sy, sz;
		sx = sy = sz = DATA_READER::getMeshScale();
		mGreenballsArr[i]->scale(sx, sy, sz);
	}

}
void GREENBALL_MANAGER::setMaxGreenballsNum(int a_Num)
{
	if (a_Num >= mNumGreenballs) 
	{
		a_Num = mNumGreenballs;
	}


	mCurGreenballsNum = a_Num;
	for (int i = 0; i < mNumGreenballs; ++i) 
	{
		if (i<mCurGreenballsNum) {
			mGreenballsArr[i]->setVisible(true);
			mGreenballsArr[i]->makeAlive(true);
		} else {
			mGreenballsArr[i]->setVisible(false);
			mGreenballsArr[i]->makeAlive(false);
		}
	}
}

void GREENBALL_MANAGER::setAction(Ogre::String actionMode)
{
	actionType = actionMode;
	for (int i = 0; i < mNumGreenballs; ++i) 
	{
		mGreenballsArr[i]->setAction(actionMode);
	}

}

void GREENBALL_MANAGER::setTargetForGreenballs(GAME_OBJ *a_Target)
{

	mGreenballsTarget = a_Target;
	for (int i = 0; i < mNumGreenballs; ++i) 
	{
		//Vector3 p = mGreenballsArr[i]->getInitPosition();
		mGreenballsArr[i]->setTarget(a_Target, 0);
	}
}


void GREENBALL_MANAGER::resolveGreenballTargetCollision()
{
	if (mGreenballsTarget == 0) return;	
	Vector3 p1 = mGreenballsTarget->getPosition();
	for (int i = 0; i < mCurGreenballsNum; ++i) 
	{
		Vector3 p0 = mGreenballsArr[i]->getPosition();
		Vector3 mm = p0 - p1;
		mm.y = 0;
		Real d = mm.length();
		mm.length();
		mm.normalise();
		if (d < 60) {
			d = 60 - d +1.0;
			mGreenballsArr[i]->translate(d*mm);
		}

	}
}


void GREENBALL_MANAGER::resolveGreenballCollision()
{
	if (mCurGreenballsNum<=0){
		return;
	}

	//Real monsterRadius = mGreenballsArr[0].getBoundingRadius();
	Real monsterRadius = DATA_READER::getMeshScale()*150;
	for (int i = 0; i < mCurGreenballsNum; ++i) 
	{
		Vector3 p0 = mGreenballsArr[i]->getPosition();
		for (int j = 0; j < mCurGreenballsNum; ++j){
			if (i != j){
				Vector3 p1 = mGreenballsArr[j]->getPosition();
				Vector3 mm = p0 - p1;
				mm.y = 0;
				Real d = mm.length();
				mm.length();
				mm.normalise();
				if (d < monsterRadius) {
					d = monsterRadius - d+1.0;
					mGreenballsArr[j]->translate(-0.5*d*mm);
					mGreenballsArr[i]->translate(0.5*d*mm);
				}
			}
		}
	}
}

void GREENBALL_MANAGER::resolveGreenballFollowingTarget()
{
	if (mCurGreenballsNum<=0){
		return;
	}

	Vector3 p1 = mGreenballsTarget->getPosition();
	for (int i = 0; i < mCurGreenballsNum; ++i) 
	{
		Vector3 p0 = mGreenballsArr[i]->getPosition();
		Vector3 mm = p0 - p1;
		mm.y = 0;
		mm.length();
		mm.normalise();
		mGreenballsArr[i]->translate(-mm/(DATA_READER::getMeshScale()*10));
	}
}


void GREENBALL_MANAGER::update(const Ogre::FrameEvent& evt)
{
	//Vector3 targetPosition = mGreenballsTarget->getPosition();

	for (int i = 0; i < mNumGreenballs; ++i) 
	{
		mGreenballsArr[i]->update(evt, actionType, mGreenballsTarget);
	}

    resolveGreenballCollision();
    resolveGreenballTargetCollision();

	//resolveGreenballFollowingTarget();
	
}
