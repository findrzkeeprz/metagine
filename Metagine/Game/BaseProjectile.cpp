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

#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "../Engine/InputTask.h"
#include "../Engine/RenderTask.h"

MBaseProjectile::MBaseProjectile( MVector2 vPosition, MVector2 vVelocity, int iType ) :
MBaseEntity(vPosition,vVelocity,true,true,ENTITY_UNDEFINED)
{
	if( iType == 0 ) {
		m_pSprite = ISpritePtr(new MSprite("Sprites/gogorisset1.png",8,84,5,38,255,0,255,0.99f));
		m_iType = ENTITY_PLAYER_PROJECTILE;
	} else if( iType == 1 ) {
		m_pSprite = ISpritePtr(new MSprite("Sprites/gogorisset1.png",17,65,3,38,255,0,255,0.99f));
		m_iType = ENTITY_PLAYER_PROJECTILE;
	} else if( iType == 2 ) {
		m_pSprite = ISpritePtr(new MSprite("Sprites/gogorisset1.png",109,124,7,7,255,0,255,0.99f));
		m_iType = ENTITY_ENEMY_PROJECTILE;
	}
	
	Engine::GetInstance()->Renderer()->RegisterDrawable(m_pSprite);
	m_pSprite->SetPosition(m_vPosition.x,m_vPosition.y);
}

MBaseProjectile::~MBaseProjectile( void )
{
	Engine::GetInstance()->Renderer()->RemoveDrawable(m_pSprite);
	printf(" -> MBaseProjectile object deleted.\n");
}

void MBaseProjectile::UpdateLogic( float fDelta )
{
	m_pSprite->Animate(true);
	
	if( m_vVelocity.Magnitude() <= 0.0f )
		return;
	
	m_vAcceleration = -m_vVelocity.Normalised();
	//m_vAcceleration *= m_fFriction->GetValueFloat();

	MVector2 vDeltaVelocity = ( ( m_vAcceleration * (float)fDelta ) / 1000.0f );

	// Cap magnitude of change in velocity to remove integration errors
	if( vDeltaVelocity.Magnitude() > m_vVelocity.Magnitude() )
		m_vVelocity.Zero();
	else m_vVelocity += vDeltaVelocity;

	m_vPosition += ( ( m_vVelocity * (float)fDelta ) / 1000.0f );

	if(m_vVelocity.Magnitude() < 0.1f) 
		m_vVelocity.Zero();
		
	m_pSprite->SetPosition(m_vPosition.x,m_vPosition.y);
}

void MBaseProjectile::CollisionEvent( IEntity* pEntity, const int iType, const float fDelta )
{
	if( iType == COLLISION_ENTITY ) {
		if( m_iType == ENTITY_PLAYER_PROJECTILE &&
			pEntity->GetType() == ENTITY_PLAYER_PROJECTILE ) {
				printf(" SELF HIT!\n");
				return;
		}
	}
	
	m_bExpired = true;
}

void MBaseProjectile::VKill( void )
{
}