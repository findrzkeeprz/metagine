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
#include "Renderer.h"
#include "../ThirdParty/SDL_collide.h"

MCollisionResolver::MCollisionResolver( void ) :
m_iDelta(0)
{
	printf(" -> MCollisionResolver object created.\n");
}

MCollisionResolver::~MCollisionResolver( void )
{
	printf(" -> MCollisionResolver object destructed.\n");
}

/*bool MCollisionResolver::Init( void )
{	
	return true;
}*/

void MCollisionResolver::Shutdown( void )
{
	printf(" -> MCollisionResolver::Shutdown() called.\n");
}

void MCollisionResolver::DeterminePartition( IEntityPtr pEntity )
{
	int w = Renderer::GetInstance()->GetScreenWidth() / 2;
	int h = Renderer::GetInstance()->GetScreenHeight() / 2;
	ISpritePtr pSprite = pEntity->GetSprite();
	int x, y = 0;
	
	pSprite->GetPosition(x,y);
	if( x < w && y < h ) m_Partitions[0].push_back(pEntity);
	else if( x > w && y < h ) m_Partitions[1].push_back(pEntity);
	else if( x < w && y > h ) m_Partitions[2].push_back(pEntity);
	else if( x > w && y > h ) m_Partitions[3].push_back(pEntity);
}

void MCollisionResolver::ProcessEntityPairs( void )
{
	vector<pair<IEntityPtr,IEntityPtr>>::iterator it;
	for( it = m_EntityPairs.begin(); it < m_EntityPairs.end(); ++it ) {
		SDL_Surface* pSurface1 = (SDL_Surface*)(*it).first->GetSprite()->GetSurface();
		SDL_Surface* pSurface2 = (SDL_Surface*)(*it).second->GetSprite()->GetSurface();
		ISpritePtr pSprite1 = (*it).first->GetSprite();
		ISpritePtr pSprite2 = (*it).second->GetSprite();

		int x, y, x2, y2 = 0;
		pSprite1->GetPosition(x,y);
		pSprite2->GetPosition(x2,y2);

		// Test for collision and inform involved parties.
		if( SDL_CollidePixel(pSurface1,x,y,pSurface2,x2,y2,4) ) {
		//if( SDL_CollideBoundingBox(pSurface1,x,y,pSurface2,x2,y2) ) {
			(*it).first->CollisionEvent((*it).second,m_iDelta);
			(*it).second->CollisionEvent((*it).first,m_iDelta);
		}
	}

	m_EntityPairs.clear();
}

void MCollisionResolver::Resolve( vector<IEntityPtr>& Entities, int iDelta )
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