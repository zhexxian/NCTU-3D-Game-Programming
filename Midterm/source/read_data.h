#ifndef __DATA_READER_H__
#define __DATA_READER_H__

#include <string>

class DATA_READER {
protected:
	static bool mEnableExpFog;
	static bool mEnableShadow;
	static float mExpFogDensity;
	static int mMaxBulletsNum;
	static int mMaxMonstersNum;
	static double mWaterCoord_Y;
	static std::string mPlaneMaterialName;
	static std::string mMeshName;
	static double mMeshScale;
	
	static double mDimensionX;
	static double mDimensionZ;
	static double mFogColourRedComponent;
	static double mFogColourGreenComponent;
	static double mFogColourBlueComponent;


public:
	DATA_READER();
	static void readData();

static double getDimensionX();
static double getDimensionZ();
static std::string getPlaneMaterialName();
static bool isFogEnabled();
static double getFogColourRedComponent();
static double getFogColourGreenComponent();
static double getFogColourBlueComponent();
};

#endif