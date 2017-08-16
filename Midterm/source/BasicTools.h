#ifndef __BASIC_TOOLS_H__
#define __BASIC_TOOLS_H__
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreParticleSystem.h>
#include <OgreRoot.h>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreParticleEmitter.h>

extern void genNameUsingIndex(const Ogre::String & prefix, int index, Ogre::String &out_name);
void setOffParticleSystem(
	Ogre::SceneNode *objectSceneNode, 
	const Ogre::String &particleScriptName, 
	const Ogre::Vector3 &pos); 

Ogre::SceneNode* initParticleSystem(
	Ogre::SceneManager *sceneMgr,
	const Ogre::String particleScriptName
	);
#endif