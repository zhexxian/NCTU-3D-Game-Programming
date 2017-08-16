#include "map.h"

MAP::MAP( )
{
    mNX = 10;
    mNZ = 10;
    mMinSpace = Vector3( -250.0, 0.0, -250.0 );
    mMaxSpace = Vector3( 250.0, 0.0, 250.0 );
    mSceneNodes = 0;
    mEntitys = 0;
    reset( );
}

void MAP::setDimension( int nx, int nz )
{
    mNX = nx;
    mNZ = nz;
    reset( );
}

void MAP::reset( )
{
    for ( int j = 0; j < MAX_NZ; ++j ) {
        for ( int i = 0; i < MAX_NX; ++i ) {
            mMapNodes[i][j].flgCanMove = false;
        }
    }
}

void MAP::generateMap( SceneManager* mSceneMgr )
{
    mSceneNodes = new SceneNode*[mNX*mNZ];
    mEntitys = new Entity*[mNX*mNZ];
    Vector3 w = mMaxSpace - mMinSpace;
    double dx = w.x/(mNX-1);
    double dz = w.z/(mNZ-1);
    //
    mDWidth = Vector3( dx, 0.0, dz );

    for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            int index = i + j*mNX;
            double x, y, z;
            y = 0.0;
            x = i*dx + mMinSpace.x;
            z = j*dz + mMinSpace.z;
            //
            mMapNodes[i][j].flgCanMove = false;
            mMapNodes[i][j].ix = i;
            mMapNodes[i][j].iz = j;

            mMapNodes[i][j].position = Vector3( x, 0.0, z );
            //
            mSceneNodes[ index ] = mSceneMgr->getRootSceneNode()->createChildSceneNode( );
            mSceneNodes[ index ]->setPosition( Vector3( x, y, z ) );
            mSceneNodes[ index ]->scale(0.35, 1.0, 0.35 );
            mSceneNodes[ index ]->translate( 0.0, -40.0, 0.0);
            String name;
            genNameUsingIndex("br", index, name);
			

            mEntitys[ index ] = mSceneMgr
                ->createEntity( name, "cube.mesh" ); 
            mEntitys[ index ]->setMaterialName("Examples/SphereMappedRustySteel");
            mSceneNodes[ index ]->attachObject( mEntitys[ index ] );
			
        }


    }
    //
    //
    //Fill in your code
	//Clear parts of the map
	for ( int j = 1; j < 9; ++j ) {
        for ( int i = 1; i < 9; ++i ) {
			mMapNodes[i][j].flgCanMove = true;
			mSceneNodes[ i + j*mNX ]->setVisible( false );
		}
	}

	for ( int i = 2; i < 8; ++i ) {
		int j=2;
		mMapNodes[i][j].flgCanMove = false;
		mSceneNodes[ i + j*mNX ]->setVisible( true );
	}

	for ( int i = 2; i < 8; ++i ) {
		int j=7;
		mMapNodes[i][j].flgCanMove = false;
		mSceneNodes[ i + j*mNX ]->setVisible( true );
	}


	int i=0;
	int j=4;
	mMapNodes[i][j].flgCanMove = false;
	mSceneNodes[ i + j*mNX ]->setVisible( false );

	i=9;
	j=5;
	mMapNodes[i][j].flgCanMove = false;
	mSceneNodes[ i + j*mNX ]->setVisible( false );

	i=1;
	j=4;
	mMapNodes[i][j].flgCanMove = false;
	mSceneNodes[ i + j*mNX ]->setVisible( true );

	i=4;
	j=4;
	mMapNodes[i][j].flgCanMove = false;
	mSceneNodes[ i + j*mNX ]->setVisible( true );

	i=5;
	j=5;
	mMapNodes[i][j].flgCanMove = false;
	mSceneNodes[ i + j*mNX ]->setVisible( true );

	i=8;
	j=5;
	mMapNodes[i][j].flgCanMove = false;
	mSceneNodes[ i + j*mNX ]->setVisible( true );

    //
    //
    mMaxNumOfPathPoints = mNX*mNZ; 
    mSceneNodes_Path = new SceneNode*[mMaxNumOfPathPoints];
    mEntitys_Path = new Entity*[mMaxNumOfPathPoints];
    for ( int j = 0; j < mMaxNumOfPathPoints; ++j ) {
        String name;
        genNameUsingIndex("path", j, name);

        mSceneNodes_Path[ j ] = mSceneMgr->getRootSceneNode()->createChildSceneNode( );
        mEntitys_Path[ j ] = mSceneMgr
            ->createEntity( name, "sphere.mesh" ); 
        mEntitys_Path[ j ]->setMaterialName("Examples/BeachStones");
        mSceneNodes_Path[ j ]->attachObject( mEntitys_Path[ j ] );
        mSceneNodes_Path[ j ]->scale(0.15, 0.20, 0.15);
        mSceneNodes_Path[ j ]->setVisible( false );
		//Ogre::LogManager::getSingletonPtr()->logMessage("*** Sphere Jesse Jesse Jesse ***");
    }
}