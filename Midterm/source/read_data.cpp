#include <fstream>
#include <iostream>
#include <string>
#include "read_data.h"
#define DATA_FILE_NAME	"game_data.txt"

using namespace std;
/*
bool DATA_READER::mEnableShadow = true;
int	DATA_READER::mMaxBulletsNum = 10;
int	DATA_READER::mMaxMonstersNum = 10;
double	DATA_READER::mWaterCoord_Y = 0.0;

std::string DATA_READER::mMeshName = "";
double DATA_READER::mMeshScale = 1.0;

float DATA_READER::mExpFogDensity = 0.0003;
*/
std::string DATA_READER::mPlaneMaterialName = "";
double DATA_READER::mDimensionX = 0.0;
double DATA_READER::mDimensionZ = 0.0;
bool DATA_READER::mEnableExpFog = true;
double DATA_READER::mFogColourRedComponent = 1.0;
double DATA_READER::mFogColourGreenComponent = 1.0;
double DATA_READER::mFogColourBlueComponent = 1.0;


DATA_READER::DATA_READER()
{

}

void DATA_READER::readData()
{
	using namespace std;
	std::ifstream *fp;
	fp = new std::ifstream(DATA_FILE_NAME, ios::in | ios::binary);
	if (fp == 0 || fp->fail()) {
		cout << "Cannot open data file:" << DATA_FILE_NAME << endl;
		return;
	}
	
	std::string key;
	double num;
	while (!fp->eof()) {
	*fp >> key;
	
	if (key.compare("PLANE_MATERIAL") == 0) {
	*fp >> mPlaneMaterialName;
	}

if (key.compare("DIMENSION_X") == 0) {
	*fp >> mDimensionX;
	
	}

if (key.compare("DIMENSION_Z") == 0) {
	*fp >> mDimensionZ;
	
	}
if (key.compare("ENABLE_FOG") == 0) {
	*fp >> mEnableExpFog;
	*fp >> mFogColourRedComponent >> mFogColourGreenComponent >> mFogColourBlueComponent;
	
	}
	}

}



double DATA_READER::getDimensionX()
{
	return mDimensionX;
}

double DATA_READER::getDimensionZ()
{
	return mDimensionZ;
}

std::string DATA_READER::getPlaneMaterialName()
{
	return mPlaneMaterialName;
}

bool DATA_READER::isFogEnabled()
{
	return mEnableExpFog;
}

double DATA_READER::getFogColourRedComponent()
{
	return mFogColourRedComponent;
}

 double DATA_READER::getFogColourGreenComponent()
{
	return mFogColourGreenComponent;
}

 double DATA_READER::getFogColourBlueComponent()
{
	return mFogColourBlueComponent;
}
