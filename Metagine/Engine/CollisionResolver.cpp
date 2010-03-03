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
#include "../ThirdParty/SDL_collide.h"

MCollisionResolver::MCollisionResolver( void ) :
m_iDelta(0)
{
	printf(" -> MCollisionResolver object created.\n");
}

MCollisionResolver::~MCollisionResolver( void )
{
	m_EntityPairs.clear();
	for( int i = 0; i < 4; i++ ) {
		m_Partitions[i].clear();
	}
	
	printf(" -> MCollisionResolver object destructed.\n");
}

void MCollisionResolver::DeterminePartition( IEntityPtr pEntity )
{
	int w = Engine::GetInstance()->Renderer()->GetScreenWidth() / 2;
	int h = Engine::GetInstance()->Renderer()->GetScreenHeight() / 2;
	int x = pEntity->GetSprite()->GetPositionX();
	int y = pEntity->GetSprite()->GetPositionY();
	
	// Entity is currently on-screen.
	if( CheckScreenBoundary(pEntity) ) {
		if( x < w && y < h ) 
			m_Partitions[0].push_back(pEntity);
		else if( x > w && y < h ) 
			m_Partitions[1].push_back(pEntity);
		else if( x < w && y > h ) 
			m_Partitions[2].push_back(pEntity);
		else if( x > w && y > h ) 
			m_Partitions[3].push_back(pEntity);
	}
}

bool MCollisionResolver::CheckScreenBoundary( IEntityPtr pEntity )
{
	ISpritePtr pSprite = pEntity->GetSprite();
	int w = Engine::GetInstance()->Renderer()->GetScreenWidth();
	int h = Engine::GetInstance()->Renderer()->GetScreenHeight();
	int x = pSprite->GetPositionX();
	int y = pSprite->GetPositionY();

	if( ( x + pSprite->GetWidth() ) > w ) {
		pEntity->CollisionEvent(IEntityPtr(),COLLISION_RIGHT_SCREEN,m_iDelta);
		return false;
	} else if( ( y + pSprite->GetHeight() ) > h ) {
		pEntity->CollisionEvent(IEntityPtr(),COLLISION_LOWER_SCREEN,m_iDelta);
		return false;
	} else if( x < 0 ) {
		pEntity->CollisionEvent(IEntityPtr(),COLLISION_LEFT_SCREEN,m_iDelta);
		return false;
	} else if( y < 0 ) {
		pEntity->CollisionEvent(IEntityPtr(),COLLISION_UPPER_SCREEN,m_iDelta);
		return false;
	}
	
	return true;
}

void MCollisionResolver::ProcessEntityPairs( void )
{
	vector<pair<IEntityPtr,IEntityPtr>>::iterator it;
	for( it = m_EntityPairs.begin(); it < m_EntityPairs.end(); ++it ) {
		SDL_Surface* pSurface1 = (SDL_Surface*)(*it).first->GetSprite()->GetSurface();
		SDL_Surface* pSurface2 = (SDL_Surface*)(*it).second->GetSprite()->GetSurface();
		ISpritePtr pSprite1 = (*it).first->GetSprite();
		ISpritePtr pSprite2 = (*it).second->GetSprite();
		
		int x = pSprite1->GetPositionX();
		int y = pSprite1->GetPositionY();
		int x2 = pSprite2->GetPositionX();
		int y2 = pSprite2->GetPositionY();

		// Test for collision and inform involved parties.
		if( SDL_CollidePixel(pSurface1,x,y,pSurface2,x2,y2,4) ) {
		//if( SDL_CollideBoundingBox(pSurface1,x,y,pSurface2,x2,y2) ) {
			(*it).first->CollisionEvent((*it).second,COLLISION_ENTITY,m_iDelta);
			(*it).second->CollisionEvent((*it).first,COLLISION_ENTITY,m_iDelta);
		}
	}

	m_EntityPairs.clear();
}

void MCollisionResolver::Resolve( vector<IEntityPtr> Entities, int iDelta )
{
	// 1. Divide screen into 4 divisions.
	// 2. Perform collision detection.
	// 3. Notify responsible entities (collision response).
	
	m_iDelta = iDelta;
	
	vector<IEntityPtr>::iterator it;
	for( it = Entities.begin(); it < Entities.end(); ++it ) {
		if( (*it)->GetActive() ) {
			DeterminePartition((*it));
		}
	}

	for( int i = 0; i < 4; i++ ) {
		for( int j = 0; j < (int)m_Partitions[i].size(); j++ ) {
			for( int k = j + 1; k < (int)m_Partitions[i].size(); k++ ) {
				m_EntityPairs.push_back(make_pair(m_Partitions[i][j],m_Partitions[i][k]));
			}
		}
	}

	ProcessEntityPairs();
	
	for( int i = 0; i < 4; i++ ) {
		m_Partitions[i].clear();
	}
}