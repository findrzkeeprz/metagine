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

#include "TempEntity.h"
#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "../Engine/RenderTask.h"

MTempEntity::MTempEntity( MVector2 vPosition, MVector2 vVelocity ) :
MBaseEntity(vPosition,vVelocity,true,true,ENTITY_UNDEFINED)
{
	m_pSprite = ISpritePtr(new MSprite("Sprites/Square.png",10,10,0.0f));
	Engine::GetInstance()->Renderer()->RegisterDrawable(m_pSprite);
	m_pSprite->SetPosition(m_vPosition.x,m_vPosition.y);
}

MTempEntity::~MTempEntity( void )
{
	Engine::GetInstance()->Renderer()->RemoveDrawable(m_pSprite);
	printf(" -> MTempEntity object deleted.\n");
}

void MTempEntity::UpdateLogic( float fDelta )
{
	// Expire after animation has finished.
	m_vPosition += ( ( m_vVelocity * (float)fDelta ) / 1000.0f );
	m_pSprite->SetPosition(m_vPosition.x,m_vPosition.y);
	//if( !m_pSprite->Animate(false) )
	//	m_bExpired = true;
}

void MTempEntity::VKill( void )
{
	Engine::GetInstance()->Renderer()->RemoveDrawable(m_pSprite);
}

void MTempEntity::CollisionEvent( IEntity* pEntity, const int iType, const float fDelta )
{
	if( iType == COLLISION_ENTITY )
		return;

	switch( iType ) {
		case COLLISION_UPPER_SCREEN:
			{
				m_vPosition.y -= ( ( m_vVelocity.y * fDelta ) / 1000.0f );
				MVector2 vNormal(0.0f,1.0f);
				MVector2 vPerp = vNormal * (m_vVelocity.Dot(vNormal));
				MVector2 vParallel = m_vVelocity - vPerp;
				m_vVelocity = vParallel + -vPerp;

			} break;
		case COLLISION_LOWER_SCREEN:
			{
				m_vPosition.y -= ( ( m_vVelocity.y * fDelta ) / 1000.0f );
				MVector2 vNormal(0.0f,-1.0f);
				MVector2 vPerp = vNormal * (m_vVelocity.Dot(vNormal));
				MVector2 vParallel = m_vVelocity - vPerp;
				m_vVelocity = vParallel + -vPerp;
			} break;
		case COLLISION_LEFT_SCREEN:
			{
				m_vPosition.x -= ( ( m_vVelocity.x * fDelta ) / 1000.0f );
				MVector2 vNormal(1.0f,0.0f);
				MVector2 vPerp = vNormal * (m_vVelocity.Dot(vNormal));
				MVector2 vParallel = m_vVelocity - vPerp;
				m_vVelocity = vParallel + -vPerp;
			} break;
		case COLLISION_RIGHT_SCREEN:
			{
				m_vPosition.x -= ( ( m_vVelocity.x * fDelta ) / 1000.0f );
				MVector2 vNormal(-1.0f,0.0f);
				MVector2 vPerp = vNormal * (m_vVelocity.Dot(vNormal));
				MVector2 vParallel = m_vVelocity - vPerp;
				m_vVelocity = vParallel + -vPerp;
			} break;
	};
}