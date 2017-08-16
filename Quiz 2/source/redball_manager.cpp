#include "redball_manager.h"
#include "read_data.h"

REDBALL_MANAGER::REDBALL_MANAGER(SceneManager *a_SceneMgr) : GAME_OBJ(a_SceneMgr)
{


		mRedball = new REDBALL(a_SceneMgr);
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

}


void REDBALL_MANAGER::setWandering()
{

}



void REDBALL_MANAGER::update(const Ogre::FrameEvent& evt)
{

	
}