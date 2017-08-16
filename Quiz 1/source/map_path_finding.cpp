#include "map.h"
using namespace std;

void MAP::setInvisibleAllPathPoints( )
{
    for ( int j = 0; j < mMaxNumOfPathPoints; ++j ) {
        mSceneNodes_Path[j]->setVisible( false );
    }
}

void MAP::computeIndices( const Vector3 &p, int &ix, int &iz ) const
{
    Vector3 relative_p = p - mMinSpace;
    ix = (relative_p.x + mDWidth.x*0.5 )/ mDWidth.x ;
    iz = (relative_p.z + mDWidth.z*0.5 ) / mDWidth.z;
    if ( ix < 0 ) ix = 0;
    if ( ix >= mNX - 1 ) ix = mNX - 1;

    if ( iz < 0 ) iz = 0;
    if ( iz >= mNZ - 1 ) iz = mNZ - 1;
}

Vector3 MAP::computePointPosition( int ix, int iz ) const
{
    Real x, z;
    x = ix*mDWidth.x + mMinSpace.x;
    z = iz*mDWidth.z + mMinSpace.z;
    return Vector3( x, 0.0, z );

}

void MAP::setPathPoint( int index, const pair<int , int> &point )
{
    Vector3 p = computePointPosition( point.first, point.second );
    mSceneNodes_Path[index]->setPosition( p );
    mSceneNodes_Path[index]->setVisible( true );
}

void MAP::setPathPoint( int index, const Vector3 &position )
{
    mSceneNodes_Path[index]->setPosition( position );
    mSceneNodes_Path[index]->setVisible( true );
}

void MAP::constructPathPoints( MapNode *node )
{
    if ( node == 0 ) return;
    constructPathPoints( node->parent );
    mPathPoints.push_back( node->position );
}

void MAP::constructPathPoints( int goal_ix, int goal_iz )
{
    mPathPoints.clear( );
    MapNode *goalNode = &mMapNodes[goal_ix][goal_iz];
    constructPathPoints( goalNode );

}

// true: the goal position is valid
// false: the goal position is invalid
bool MAP::performPathFinding( const Vector3 &start_position, const Vector3 &goal_position )
{
    int start_ix, start_iz;
    computeIndices( start_position, start_ix, start_iz );
    pair<int, int> start_point(start_ix, start_iz);
    //
    int goal_ix, goal_iz;
    computeIndices( goal_position, goal_ix, goal_iz );
    pair<int, int> goal_point(goal_ix, goal_iz);
    //
    mStartNode = &mMapNodes[start_ix][start_iz];
    mStartNode->parent = 0;
    mGoalNode = &mMapNodes[goal_ix][goal_iz];
    if ( mGoalNode->flgCanMove == false) return false;
    //
    setInvisibleAllPathPoints( );
    if ( mStartNode == mGoalNode ) {
        mPathPoints.clear( );    
        setPathPoint( 0, goal_point );
        constructPathPoints( mStartNode );
    } else {
        mPathPoints.clear( );
        performAStarPathFinding( );
        constructPathPoints( mGoalNode );
        for ( int i = 0; i < mPathPoints.size( ); ++i ) {
            setPathPoint( i, mPathPoints[i] );
        }

    }
    return true;
}

std::vector<Vector3> MAP::getPathPoints( ) const
{
    return mPathPoints;
}

void MAP::clearAllCosts( )
{
    for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            mMapNodes[i][j].f = -1.0;
            mMapNodes[i][j].g = -1.0;
            mMapNodes[i][j].h = -1.0;

        }

    }
}

double MAP::getCostBetweenTwoNodes( const MapNode *p0, const MapNode *p1 ) const
{
    double dx = p0->ix - p1->ix;
    double dz = p0->iz - p1->iz;
    if ( dx < 0 ) dx = -dx;
    if ( dz < 0 ) dz = -dz;
    return dx + dz;
}

void MAP::addNodeToOpenList( MapNode *node )
{
    mOpenList.push_back( node );
}

void MAP::removeNodeFromOpenList( MapNode *node )
{
    int j = 0;

    for ( int i = 0; i < mOpenList.size( ); ++i ) {
        if ( node != mOpenList[i] ) {
            mOpenList[j] = mOpenList[i];
            ++j;
        }
    }
    mOpenList.resize( j );
}

void MAP::removeNodeFromClosedList( MapNode *node )
{
    int j = 0;

    for ( int i = 0; i < mClosedList.size( ); ++i ) {
        if ( node != mClosedList[i] ) {
            mClosedList[j] = mClosedList[i];
            ++j;
        }
    }
    mClosedList.resize( j );
}


MapNode *MAP::getNodeFromOpenList( )
{
    MapNode *node = mOpenList[0];
    double cost = node->f;

    for ( int i = 0; i < mOpenList.size( ); ++i ) {
        if ( cost > mOpenList[i]->f   ) {
            cost = mOpenList[i]->f;
            node = mOpenList[i];
        }
    }

    removeNodeFromOpenList( node );

    return node;
}

/*
Collect the neighboring nodes in neightbors.
*/
void MAP::computeNeighbor( MapNode *node, std::vector<MapNode *> &neightbors)
{
    neightbors.clear( );

    MapNode *n = 0;
    int ix, iz;
    ix = node->ix;
    iz = node->iz;
    //
    //Fill in your code
	if( iz <= 0 ) n = 0;
    //
    if ( ix <= 0 ) n = 0;
    else {
        if ( mMapNodes[ix-1][iz].flgCanMove ) {
            neightbors.push_back( &mMapNodes[ix - 1][iz] );
        }
		//
		//Fill in your code
		if ( mMapNodes[ix+1][iz].flgCanMove ) {
            neightbors.push_back( &mMapNodes[ix + 1][iz] );
        }
		if ( mMapNodes[ix][iz-1].flgCanMove ) {
            neightbors.push_back( &mMapNodes[ix][iz-1] );
        }
		if ( mMapNodes[ix][iz+1].flgCanMove ) {
            neightbors.push_back( &mMapNodes[ix][iz+1] );
        }
		//
    }

}

void MAP::performAStarPathFinding( ) 
{
    mOpenList.clear( );
    mClosedList.clear( );
    clearAllCosts( );

	//g(n): distance from the start point to point n
	//h(n): estimated distance from point n to the goal point
	//f(n): current estimated cost for point n
	//f(n) = g(n) + h(n)

    double g, h;
    g = 0.0;
    h = getCostBetweenTwoNodes(mStartNode, mGoalNode);
    bool flgBetter = mStartNode->updateCost( g, h );
    mOpenList.push_back( mStartNode );

    //A* algorithm
    //
    //Fill in your code
	while (!mOpenList.empty()){
		MapNode *nodeN = getNodeFromOpenList();
		if (nodeN == mGoalNode){
			break;
		}
		mClosedList.push_back(nodeN);
			
		computeNeighbor(nodeN, mNeighbourList);

		for(int i=0; i<mNeighbourList.size(); i++){
			double gPrime, hPrime;
			gPrime = g + 1;
			hPrime = getCostBetweenTwoNodes(mNeighbourList[i], mGoalNode);

			flgBetter = mStartNode->updateCost( gPrime, hPrime );
			
			if((std::find(mOpenList.begin(), mOpenList.end(), mNeighbourList[i]) != mOpenList.end()) && !flgBetter) {
				continue;
			}

			if((std::find(mClosedList.begin(), mClosedList.end(), mNeighbourList[i]) != mClosedList.end())  && !flgBetter) {
				continue;
			}

			removeNodeFromOpenList(mNeighbourList[i]);
			removeNodeFromClosedList(mNeighbourList[i]);

			mNeighbourList[i]->setParent(nodeN);
			addNodeToOpenList(mNeighbourList[i]);
		}
	}
    //
}