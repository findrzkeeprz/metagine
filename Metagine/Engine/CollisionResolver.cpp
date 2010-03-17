// This file is part of Metagine.
// 
// Metagine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Metagine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Metagine.  If not, see <http://www.gnu.org/licenses/>.

#include "CollisionResolver.h"
#include "RenderTask.h"
#include "Engine.h"
#include <tbb/task.h>
#include <tbb/task_scheduler_init.h>
#include <tbb/concurrent_vector.h>

class CollisionTask : public tbb::task
{
public:

	vector<pair<IEntity*,IEntity*>> m_Entities;
	
	CollisionTask( vector<pair<IEntity*,IEntity*>>& entities, float fDelta )
	{
		m_fDelta = fDelta;
		m_Entities = entities;
	}

	tbb::task* execute()
	{
		/*for( int j = 0; j < (int)m_Entities.size(); j++ )
			CheckScreenBoundary(m_Entities[j]);*/
		
		/*for( int j = 0; j < (int)m_Entities.size(); j++ ) {
			for( int k = j + 1; k < (int)m_Entities.size(); k++ ) {
				m_EntityPairs[j * (int)m_Entities.size() + k] = make_pair(m_Entities[j],m_Entities[k]);
				//m_EntityPairs.push_back(make_pair(m_Entities[j],m_Entities[k]));
			}
		}*/

		//printf("hi!!\n");

		//ProcessEntityPairs();
		//m_EntityPairs.clear();
		
		return NULL;
	}
	
	/*bool CheckScreenBoundary( IEntity* pEntity )
	{
		ISpritePtr pSprite = pEntity->GetSprite();
		int w = Engine::GetInstance()->Renderer()->GetScreenWidth();
		int h = Engine::GetInstance()->Renderer()->GetScreenHeight();
		float x = pSprite->GetPositionX();
		float y = pSprite->GetPositionY();

		if( ( x + pSprite->GetWidth() ) > w ) {
			pEntity->CollisionEvent(NULL,COLLISION_RIGHT_SCREEN,m_fDelta);
			return false;
		} else if( ( y + pSprite->GetHeight() ) > h ) {
			pEntity->CollisionEvent(NULL,COLLISION_LOWER_SCREEN,m_fDelta);
			return false;
		} else if( x < 0 ) {
			pEntity->CollisionEvent(NULL,COLLISION_LEFT_SCREEN,m_fDelta);
			return false;
		} else if( y < 0 ) {
			pEntity->CollisionEvent(NULL,COLLISION_UPPER_SCREEN,m_fDelta);
			return false;
		}
	
		return true;
	}*/

	float m_fDelta;
	//vector<pair<IEntity*,IEntity*>>& m_Entities;
	//vector<pair<IEntity*,IEntity*>> m_EntityPairs;
	//tbb::concurrent_vector<pair<IEntity*,IEntity*>> m_EntityPairs;
	//pair<IEntity*,IEntity*> m_EntityPairs[1024];
};

MCollisionResolver::MCollisionResolver( void ) :
m_fDelta(0)
{
	tbb::task_scheduler_init init(4);

	int w = 1024;
	int h = 576;
	
	for( int i = 0; i < 4; ++i ) {
		for( int j = 0; j < 4; ++j ) {
			m_ScreenPartitions[i][j].iWidth = w / 4;
			m_ScreenPartitions[i][j].iHeight = h / 4;
			m_ScreenPartitions[i][j].x = (w / 4) * i;
			m_ScreenPartitions[i][j].y = (w / 4) * j;
			printf(" -> ScreenPartition: x(%i) y(%i) w(%i) h(%i)\n",
				m_ScreenPartitions[i][j].x,m_ScreenPartitions[i][j].y,
				m_ScreenPartitions[i][j].iWidth,m_ScreenPartitions[i][j].iHeight);
		}
	}

	printf(" -> MCollisionResolver object created.\n");
}

MCollisionResolver::~MCollisionResolver( void )
{
	for( int i = 0; i < 4; ++i ) {
		for( int j = 0; j < 4; ++j ) {
			m_Partitions[i][j].clear();
			m_EntityPairs[i][j].clear();
		}
	}
	
	printf(" -> MCollisionResolver object destructed.\n");
}

void MCollisionResolver::DeterminePartition( IEntity* pEntity )
{
	if( !CheckScreenBoundary(pEntity) )
		return;
	
	ISpritePtr pSprite = pEntity->GetSprite();
	
	for( int i = 0; i < 4; ++i ) {
		for( int j = 0; j < 4; ++j ) {
			float x1 = (float)m_ScreenPartitions[i][j].x;
			float y1 = (float)m_ScreenPartitions[i][j].y;
			float w1 = (float)m_ScreenPartitions[i][j].iWidth;
			float h1 = (float)m_ScreenPartitions[i][j].iHeight;
			float x2 = pSprite->GetPositionX();
			float y2 = pSprite->GetPositionY();
			float w2 = pSprite->GetWidth();
			float h2 = pSprite->GetHeight();
			
			if( RectangleIntersects(x1,y1,x2,y2,w1,h1,w2,h2) ) {
				m_Partitions[i][j].push_back(pEntity);
				break;
			}
		}
	}
	
	/*int iPartions[8][2];
	int iScreenWidth = Engine::GetInstance()->Renderer()->GetScreenWidth();
	int iScreenHeight = Engine::GetInstance()->Renderer()->GetScreenHeight();
	int iDivHeight = iScreenHeight / 8;
	int iDivWidth = iScreenWidth / 8;

	for( int i = 0; i < 8; ++i ) {
		iPartions[i][0] = iDivWidth * (i + 1);
		iPartions[i][1] = iDivHeight * (i + 1);
		int w = iPartions[i][0] / 2;
		int h = iPartions[i][1] / 2;
	}*/
	
	/*ISpritePtr pSprite = pEntity->GetSprite();
	int w = Engine::GetInstance()->Renderer()->GetScreenWidth() / 2;
	int h = Engine::GetInstance()->Renderer()->GetScreenHeight() / 2;
	float x = pSprite->GetPositionX();
	float y = pSprite->GetPositionY();
	
	// Entity is currently on-screen.
	//if( CheckScreenBoundary(pEntity) ) {
		if( x < w && y < h ) // Upper left.
			m_Partitions[0].push_back(pEntity);
		else if( x + pSprite->GetWidth() > w && y < h ) // Upper right.
			m_Partitions[1].push_back(pEntity);
		else if( x < w && y + pSprite->GetHeight() > h ) // Lower left.
			m_Partitions[2].push_back(pEntity);
		else if( x + pSprite->GetWidth() > w && y + pSprite->GetHeight() > h ) // Lower right.
			m_Partitions[3].push_back(pEntity);
	//}*/
}

bool MCollisionResolver::CheckScreenBoundary( IEntity* pEntity )
{
	ISpritePtr pSprite = pEntity->GetSprite();
	int w = Engine::GetInstance()->Renderer()->GetScreenWidth();
	int h = Engine::GetInstance()->Renderer()->GetScreenHeight();
	float x = pSprite->GetPositionX();
	float y = pSprite->GetPositionY();

	if( ( x + pSprite->GetWidth() ) > w ) {
		pEntity->CollisionEvent(NULL,COLLISION_RIGHT_SCREEN,m_fDelta);
		return false;
	} else if( ( y + pSprite->GetHeight() ) > h ) {
		pEntity->CollisionEvent(NULL,COLLISION_LOWER_SCREEN,m_fDelta);
		return false;
	} else if( x < 0 ) {
		pEntity->CollisionEvent(NULL,COLLISION_LEFT_SCREEN,m_fDelta);
		return false;
	} else if( y < 0 ) {
		pEntity->CollisionEvent(NULL,COLLISION_UPPER_SCREEN,m_fDelta);
		return false;
	}
	
	return true;
}

void MCollisionResolver::ProcessEntityPairs( void )
{
	/*vector<pair<IEntity*,IEntity*>>::iterator it;
	for( it = m_EntityPairs.begin(); it < m_EntityPairs.end(); ++it ) {
		if( (*it).first->GetExpired() || (*it).second->GetExpired() )	// Entity may have expired in previous iteration.
			continue;
		else if( (*it).first->GetVelocity().Magnitude() == 0.0f &&		// Two objects that are not moving will never collide.
			(*it).second->GetVelocity().Magnitude() == 0.0f )
			continue;
		
		SDL_Surface* pSurface1 = (SDL_Surface*)(*it).first->GetSprite()->GetSurface();
		SDL_Surface* pSurface2 = (SDL_Surface*)(*it).second->GetSprite()->GetSurface();
		ISpritePtr pSprite1 = (*it).first->GetSprite();
		ISpritePtr pSprite2 = (*it).second->GetSprite();
		
		float x1 = pSprite1->GetPositionX();
		float y1 = pSprite1->GetPositionY();
		float x2 = pSprite2->GetPositionX();
		float y2 = pSprite2->GetPositionY();
		int w1 = pSprite1->GetWidth();
		int h1 = pSprite1->GetHeight();
		int w2 = pSprite2->GetWidth();
		int h2 = pSprite2->GetHeight();

		// Test for collision and inform involved parties.
		if( RectangleIntersects(x1,y1,x2,y2,w1,h1,w2,h2) ) {
			(*it).first->CollisionEvent((*it).second,COLLISION_ENTITY,m_fDelta);
			(*it).second->CollisionEvent((*it).first,COLLISION_ENTITY,m_fDelta);
		}
	}

	m_EntityPairs.clear();*/
}

void MCollisionResolver::Resolve( IEntity** pEntities, int iCount, float fDelta )
{
	m_fDelta = fDelta;

	for( int i = 0; i < iCount; ++i ) {
		if( pEntities[i] && 
			pEntities[i]->GetActive() &&
			pEntities[i]->GetCollidable() ) {
			DeterminePartition(pEntities[i]);
		}
	}

	/*for( int i = 0; i < 4; i++ ) {
		for( int j = 0; j < (int)m_Partitions[i].size(); j++ ) {
			for( int k = j + 1; k < (int)m_Partitions[i].size(); k++ ) {
				m_EntityPairs.push_back(make_pair(m_Partitions[i][j],m_Partitions[i][k]));
			}
		}
	}

	for( int i = 0; i < 4; ++i ) {
		for( int j = 0; j < 4; ++j ) {
			for( int k = 0; k < (int)m_Partitions[i][j].size(); k++ ) {
				for( int l = k + 1; l < (int)m_Partitions[i][j].size(); l++ ) {
					m_EntityPairs[i][j].push_back(make_pair(m_Partitions[i][j],m_Partitions[i][l]));
				}
			}
		}
	}

	tbb::task_list list;
	for( int i = 0; i < 4; ++i ) {
		for( int j = 0; j < 4; ++j ) {
			list.push_back( *new( tbb::task::allocate_root() ) CollisionTask(m_EntityPairs[i][j],m_fDelta) );
			list.push_back( *new( tbb::task::allocate_root() ) CollisionTask(m_EntityPairs[i][j],m_fDelta) );
			list.push_back( *new( tbb::task::allocate_root() ) CollisionTask(m_EntityPairs[i][j],m_fDelta) );
			list.push_back( *new( tbb::task::allocate_root() ) CollisionTask(m_EntityPairs[i][j],m_fDelta) );
		}
	}
	tbb::task::spawn_root_and_wait(list);*/

	// Create the set of possible collision pairs.
	/*for( int i = 0; i < 4; i++ ) {
		for( int j = 0; j < (int)m_Partitions[i].size(); j++ ) {
			for( int k = j + 1; k < (int)m_Partitions[i].size(); k++ ) {
				m_EntityPairs.push_back(make_pair(m_Partitions[i][j],m_Partitions[i][k]));
			}
		}
	}

	// Perform the collision detection.
	ProcessEntityPairs();*/

	// Cleanup and store partition counts for debug purposes.
	for( int i = 0; i < 4; ++i ) {
		for( int j = 0; j < 4; ++j ) {
		//m_iLastSize[i] = (int)m_Partitions[i].size();
			m_Partitions[i][j].clear();
		}
	}
}

int MCollisionResolver::GetEntitiesInPartition( const int iPartition )
{
	return m_iLastSize[iPartition];
}

bool MCollisionResolver::RectangleIntersects( float x1, float y1, float x2, float y2, int w1, int h1, int w2, int h2 )
{
	if( x2 + w2 < x1 ) return false;
	if( x2 > x1 + w1 ) return false;
	if( y2 + h2 < y1 ) return false;
	if( y2 > y1 + h1 ) return false;

	return true;
}