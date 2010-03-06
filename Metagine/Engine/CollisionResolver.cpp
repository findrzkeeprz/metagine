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
m_fDelta(0)
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
	ISpritePtr pSprite = pEntity->GetSprite();
	int w = Engine::GetInstance()->Renderer()->GetScreenWidth() / 2;
	int h = Engine::GetInstance()->Renderer()->GetScreenHeight() / 2;
	float x = pSprite->GetPositionX();
	float y = pSprite->GetPositionY();
	
	// Entity is currently on-screen.
	if( CheckScreenBoundary(pEntity) ) {
		if( x < w && y < h ) // Upper left.
			m_Partitions[0].push_back(pEntity);
		if( x + pSprite->GetWidth() > w && y < h ) // Upper right.
			m_Partitions[1].push_back(pEntity);
		if( x < w && y + pSprite->GetHeight() > h ) // Lower left.
			m_Partitions[2].push_back(pEntity);
		if( x + pSprite->GetWidth() > w && y + pSprite->GetHeight() > h ) // Lower right.
			m_Partitions[3].push_back(pEntity);
	}
}

bool MCollisionResolver::CheckScreenBoundary( IEntityPtr pEntity )
{
	ISpritePtr pSprite = pEntity->GetSprite();
	int w = Engine::GetInstance()->Renderer()->GetScreenWidth();
	int h = Engine::GetInstance()->Renderer()->GetScreenHeight();
	float x = pSprite->GetPositionX();
	float y = pSprite->GetPositionY();

	if( ( x + pSprite->GetWidth() ) > w ) {
		pEntity->CollisionEvent(IEntityPtr(),COLLISION_RIGHT_SCREEN,m_fDelta);
		return false;
	} else if( ( y + pSprite->GetHeight() ) > h ) {
		pEntity->CollisionEvent(IEntityPtr(),COLLISION_LOWER_SCREEN,m_fDelta);
		return false;
	} else if( x < 0 ) {
		pEntity->CollisionEvent(IEntityPtr(),COLLISION_LEFT_SCREEN,m_fDelta);
		return false;
	} else if( y < 0 ) {
		pEntity->CollisionEvent(IEntityPtr(),COLLISION_UPPER_SCREEN,m_fDelta);
		return false;
	}
	
	return true;
}

void MCollisionResolver::ProcessEntityPairs( void )
{
	vector<pair<IEntityPtr,IEntityPtr>>::iterator it;
	for( it = m_EntityPairs.begin(); it < m_EntityPairs.end(); ++it ) {
		// Two objects that are not moving will never collide.
		if( (*it).first->GetVelocity().Magnitude() == 0.0f &&
			(*it).second->GetVelocity().Magnitude() == 0.0f ) {
				continue;
		}
		
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
		//if( SDL_CollidePixel(pSurface1,x,y,pSurface2,x2,y2,4) ) {
		if( RectangleIntersects(x1,y1,x2,y2,w1,h1,w2,h2) ) {
			(*it).first->CollisionEvent((*it).second,COLLISION_ENTITY,m_fDelta);
			(*it).second->CollisionEvent((*it).first,COLLISION_ENTITY,m_fDelta);
		}
	}

	m_EntityPairs.clear();
}

void MCollisionResolver::Resolve( vector<IEntityPtr>& Entities, float fDelta )
{
	m_fDelta = fDelta;
	
	vector<IEntityPtr>::iterator entity;
	for( entity = Entities.begin(); entity < Entities.end(); ++entity ) {
		if( (*entity)->GetActive() ) {
			DeterminePartition((*entity));
		}
	}

	// Create the set of possible collision pairs.
	for( int i = 0; i < 4; i++ ) {
		for( int j = 0; j < (int)m_Partitions[i].size(); j++ ) {
			for( int k = j + 1; k < (int)m_Partitions[i].size(); k++ ) {
				m_EntityPairs.push_back(make_pair(m_Partitions[i][j],m_Partitions[i][k]));
			}
		}
	}

	// Perform the collision detection.
	ProcessEntityPairs();

	// Cleanup and store partition counts for debug purposes.
	for( int i = 0; i < 4; i++ ) {
		m_iLastSize[i] = (int)m_Partitions[i].size();
		m_Partitions[i].clear();
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