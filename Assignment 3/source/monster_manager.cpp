#include "monster_manager.h"
#include "read_data.h"

MONSTER_MANAGER::MONSTER_MANAGER(SceneManager *a_SceneMgr): GAME_OBJ(a_SceneMgr)
{

	mMonstersTarget = 0;
	mCurMonstersNum = mNumMonsters = 512;
	for (int i = 0; i < mNumMonsters; ++i) 
	{
		mLifeStateArr[i] = true;
		mMonstersArr[i] = new MONSTER(a_SceneMgr);
		mMonstersArr[i]->createGameObj("m", DATA_READER::getMeshName());
		monsterTotalTranslation[i];
		Vector3 org(750, 100, 750);
		Vector3 pos;
		Real x = -1+2*(rand()%100)/100.0;
		Real z = -1+2*(rand()%100)/100.0;
		pos.x = 700*x;
		pos.z = 700*z;
		pos.y = 20;

		mMonstersArr[i]->setPosition(pos+org);
		mMonstersArr[i]->setInitPosition(pos+org);
		Real sx, sy, sz;
		sx = sy = sz = DATA_READER::getMeshScale();
		mMonstersArr[i]->scale(sx, sy, sz);
	}

}
void MONSTER_MANAGER::setMaxMonstersNum(int a_Num)
{
	if (a_Num >= mNumMonsters) 
	{
		a_Num = mNumMonsters;
	}


	mCurMonstersNum = a_Num;
	for (int i = 0; i < mNumMonsters; ++i) 
	{
		if (i<mCurMonstersNum) {
			mMonstersArr[i]->setVisible(true);
			mMonstersArr[i]->makeAlive(true);
		} else {
			mMonstersArr[i]->setVisible(false);
			mMonstersArr[i]->makeAlive(false);
		}
	}
}

void MONSTER_MANAGER::setTargetForMonsters(GAME_OBJ *a_Target)
{

	mMonstersTarget = a_Target;
	for (int i = 0; i < mNumMonsters; ++i) 
	{
		//Vector3 p = mMonstersArr[i]->getInitPosition();
		mMonstersArr[i]->setTarget(a_Target, 0);
	}
}

//resolve collision between the target and the monsters
void MONSTER_MANAGER::resolveMonsterTargetCollision()
{
	if (mMonstersTarget == 0) return;	
	Vector3 p1 = mMonstersTarget->getPosition();
	for (int i = 0; i < mCurMonstersNum; ++i) 
	{
		Vector3 p0 = mMonstersArr[i]->getPosition();
		Vector3 mm = p0 - p1;
		mm.y = 0;
		Real d = mm.length();
		mm.length();
		mm.normalise();
		if (d < 50) {
			d = 50 - d +1.0;
			mMonstersArr[i]->translate(d*mm);
		}

		//facing robot
		mMonstersArr[i]->lookAt(p0+ mm*10);
	}
}

//resolve collision between monsters
void MONSTER_MANAGER::resolveMonsterCollision()
{
	if (mCurMonstersNum<=0){
		return;
	}

	//Real monsterRadius = mMonstersArr[0].getBoundingRadius();
	Real monsterRadius = DATA_READER::getMeshScale()*70;
	for (int i = 0; i < mCurMonstersNum; ++i) 
	{
		Vector3 p0 = mMonstersArr[i]->getPosition();
		for (int j = 0; j < mCurMonstersNum; ++j){
			if (i != j){
				Vector3 p1 = mMonstersArr[j]->getPosition();
				Vector3 mm = p0 - p1;
				mm.y = 0;
				Real d = mm.length();
				mm.length();
				mm.normalise();
				if (d < monsterRadius) {
					d = monsterRadius - d+1.0;
					mMonstersArr[j]->translate(-0.5*d*mm);
					mMonstersArr[i]->translate(0.5*d*mm);
				}
			}
		}
	}
}

void MONSTER_MANAGER::resolveMonsterFollowingTarget()
{
	if (mCurMonstersNum<=0){
		return;
	}

	Vector3 p1 = mMonstersTarget->getPosition();
	for (int i = 0; i < mCurMonstersNum; ++i) 
	{
		Vector3 p0 = mMonstersArr[i]->getPosition();
		Vector3 mm = p0 - p1;
		mm.y = 0;
		mm.length();
		mm.normalise();
		mMonstersArr[i]->translate(-mm/(DATA_READER::getMeshScale()*10));
	}
}

//compute the positions of the monsters
//resolve collision between monsters
//resolve collision between the target and the monsters
void MONSTER_MANAGER::update(const Ogre::FrameEvent& evt)
{
	Vector3 targetPosition = mMonstersTarget->getPosition();


    resolveMonsterCollision();
    resolveMonsterTargetCollision();

	resolveMonsterFollowingTarget();
	
}
