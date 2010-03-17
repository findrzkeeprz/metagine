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

#include "Ship.h"
#include "../Engine/VarManager.h"

// Temp.
#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "../Engine/InputTask.h"
#include "../Engine/RenderTask.h"

MShip::MShip( void ) :
MBaseEntity(MVector2(0.0f,0.0f),MVector2(0.0f,0.0f),true,true,ENTITY_PLAYER_SHIP),
m_bFireLock(false),
m_bFlipFlop(false)
{
	// This will all need to go through the engine interface in future.
	//m_ShipSprite(new MSprite("Ship1.png",0,true,71,0,50,65,255,0,255,0.95f));
	//m_ShipSprite = ISpritePtr(new MSprite("Ship1.png",0,true,71,0,50,65,255,0,255,0.95f));
	m_pSprite = ISpritePtr(new MSprite("Sprites/gogorisset1.png",52,13,39,36,255,0,255,0.5f));
	
	Engine::GetInstance()->Renderer()->RegisterDrawable(m_pSprite);
	
	// Center the ship on the center of the screen initially.
	int iCenter = (Engine::GetInstance()->Renderer()->GetScreenWidth() / 2) - ( m_pSprite->GetWidth() / 2 );
	m_vPosition.x = (float)iCenter;
	m_vPosition.y = 520.0f;
	m_vVelocity.Zero();
	m_vAcceleration.Zero();
	m_pSprite->SetPosition(m_vPosition.x,m_vPosition.y);

	m_pShield = IEntityPtr(new MPlayerShield(MVector2(m_vPosition.x - 2,m_vPosition.y - 10),MVector2(0.0f,0.0f)));
	m_pShield->SetActive(false);
	Engine::GetInstance()->EntityManager()->RegisterEntity(m_pShield);	
	//Engine::GetInstance()->InputManager()->RegisterListener(this);
	//Engine::GetInstance()->RegisterEntity(this);

	m_fFriction = Engine::GetInstance()->VarManager()->CreateVar("f_friction",25.0f);
	m_fImpulse = Engine::GetInstance()->VarManager()->CreateVar("f_impulse",2.75f);
	m_fCutOff = Engine::GetInstance()->VarManager()->CreateVar("f_cutoff",0.15f);
}

MShip::~MShip( void )
{
	m_pShield.reset();
}

void MShip::UpdateInput( const Uint8* pKeyState, const int iKey, const bool bKeyDown )
{
	//m_pShield->Set
	//pKeyState[SDLK_LALT] ? m_pShield->SetActive(true) : m_pShield->SetActive(false);
	if( pKeyState[SDLK_LALT] ) {
		m_pShield->SetActive(true);
		m_pShield->GetSprite()->SetActive(true);
	} else if( !pKeyState[SDLK_LALT] ) {
		m_pShield->SetActive(false);
		m_pShield->GetSprite()->SetActive(false);
	}

	
	if( !pKeyState[SDLK_SPACE] && m_bFireLock ) 
		m_bFireLock = false;

	if( pKeyState[SDLK_LEFT] ) m_vVelocity.x -= m_fImpulse->GetValueFloat();
	if( pKeyState[SDLK_RIGHT] ) m_vVelocity.x += m_fImpulse->GetValueFloat();
	if( pKeyState[SDLK_UP] ) m_vVelocity.y -= m_fImpulse->GetValueFloat();
	if( pKeyState[SDLK_DOWN] ) m_vVelocity.y += m_fImpulse->GetValueFloat();

	if( pKeyState[SDLK_SPACE] && !m_bFireLock ) {
		if( !m_bFlipFlop ){
			//IEntityPtr pBullet(new MBaseProjectile(0,m_vPosition.x - 1,m_vPosition.y - 35,-300.0f));
			IEntityPtr pBullet(new MBaseProjectile(MVector2(m_vPosition.x - 1,m_vPosition.y - 35),
				MVector2(0.0f,-300.0f),0));

			Engine::GetInstance()->EntityManager()->RegisterEntity(pBullet);

			//IEntityPtr pBullet2(new MBaseProjectile(0,(m_vPosition.x + m_ShipSprite->GetWidth()) - 4,m_vPosition.y - 35,-300.0f));
			IEntityPtr pBullet2(new MBaseProjectile(MVector2((m_vPosition.x + m_pSprite->GetWidth()) - 4,m_vPosition.y - 35),
				MVector2(0.0f,-300.0f),0));
			Engine::GetInstance()->EntityManager()->RegisterEntity(pBullet2);

			m_bFlipFlop = !m_bFlipFlop;
		} else {
			//IEntityPtr pBullet3(new MBaseProjectile(1,m_vPosition.x + 8,m_vPosition.y - 35,-500.0f));
			IEntityPtr pBullet3(new MBaseProjectile(MVector2(m_vPosition.x + 8,m_vPosition.y - 35),
				MVector2(0.0f,-500.0f),1));

			Engine::GetInstance()->EntityManager()->RegisterEntity(pBullet3);

			//IEntityPtr pBullet4(new MBaseProjectile(1,m_vPosition.x + m_ShipSprite->GetWidth() - 11,m_vPosition.y - 35,-500.0f));
			IEntityPtr pBullet4(new MBaseProjectile(MVector2(m_vPosition.x + m_pSprite->GetWidth() - 11,m_vPosition.y - 35),
				MVector2(0.0f,-500.0f),1));
			Engine::GetInstance()->EntityManager()->RegisterEntity(pBullet4);

			m_bFlipFlop = !m_bFlipFlop;
		}

		Engine::GetInstance()->AudioTask()->PlaySound("Shoot1.wav");
		m_bFireLock = true;
	}
}

void MShip::UpdateLogic( float fDelta )
{
	if( m_vVelocity.Magnitude() <= 0.0f )
		return;
	
	m_vAcceleration = -m_vVelocity.Normalised();
	m_vAcceleration *= m_fFriction->GetValueFloat();

	MVector2 vDeltaVelocity = ( ( m_vAcceleration * fDelta ) / 1000.0f );

	// Cap magnitude of change in velocity to remove integration errors
	if( vDeltaVelocity.Magnitude() > m_vVelocity.Magnitude() )
		m_vVelocity.Zero();
	else m_vVelocity += vDeltaVelocity;

	m_vPosition += ( ( m_vVelocity * fDelta ) / 1000.0f );

	if(m_vVelocity.Magnitude() < m_fCutOff->GetValueFloat()) 
		m_vVelocity.Zero();
		
	m_pSprite->SetPosition(m_vPosition.x,m_vPosition.y);
	m_pShield->SetPosition(MVector2(m_vPosition.x,m_vPosition.y - 10));
}

void MShip::CollisionEvent( IEntity* pEntity, const int iType, const float fDelta )
{
	if( iType == COLLISION_LEFT_SCREEN || iType == COLLISION_RIGHT_SCREEN ) {
		m_vPosition.x -= ( ( m_vVelocity.x * fDelta ) / 1000.0f );
		m_pSprite->SetPosition(m_vPosition.x,m_vPosition.y);
		m_vVelocity.x = 0.0f;
	} else if( iType == COLLISION_UPPER_SCREEN || iType == COLLISION_LOWER_SCREEN ) {
		m_vPosition.y += ( ( -m_vVelocity.y * fDelta ) / 1000.0f );
		m_pSprite->SetPosition(m_vPosition.x,m_vPosition.y);
		m_vVelocity.y = 0.0f;
	} else if ( iType == COLLISION_ENTITY ) {
		//if( pEntity->GetType() == ENTITY_ENEMY_PROJECTILE )
		//	printf(" OUCH!!!!!!!!!!!!!!\n");
	}
}

void MShip::VKill( void )
{
}