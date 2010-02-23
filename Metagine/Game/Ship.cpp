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
#include "../Engine/InputManager.h"
#include "../Engine/Renderer.h"

MShip::MShip( void ) :
m_bActive(true)
{
	// This will all need to go through the engine interface in future.
	//m_ShipSprite(new MSprite("Ship1.png",0,true,71,0,50,65,255,0,255,0.95f));
	m_ShipSprite = ISpritePtr(new MSprite("Ship1.png",0,true,71,0,50,65,255,0,255,0.95f));
	Renderer::GetInstance()->RegisterDrawable(m_ShipSprite);
	
	// Center the ship on the center of the screen initially.
	int iCenter = (Renderer::GetInstance()->GetScreenWidth() / 2) - ( m_ShipSprite->GetWidth() / 2 );
	m_vPosition.x = (float)iCenter;
	m_vPosition.y = 575.0f;
	m_vVelocity.Zero();
	m_vAcceleration.Zero();
	m_ShipSprite->SetPosition((int)m_vPosition.x,(int)m_vPosition.y);
	
	InputManager::GetInstance()->RegisterListener(this);
	//Engine::GetInstance()->RegisterEntity(this);

	m_fFriction = VarManager::GetInstance()->CreateVar("ffriction",25.0f);
	m_fImpulse = VarManager::GetInstance()->CreateVar("fimpulse",2.75f);
	m_fCutOff = VarManager::GetInstance()->CreateVar("fcutoff",0.15f);
}

MShip::~MShip( void )
{
}

void MShip::UpdateInput( const bool bKeys[], const int iKey, const bool bKeyDown )
{
	if( !bKeyDown )
		return;

	if( bKeys[SDLK_LEFT] ) m_vVelocity.x -= m_fImpulse->GetValueFloat();
	if( bKeys[SDLK_RIGHT] ) m_vVelocity.x += m_fImpulse->GetValueFloat();
	if( bKeys[SDLK_UP] ) m_vVelocity.y -= m_fImpulse->GetValueFloat();
	if( bKeys[SDLK_DOWN] ) m_vVelocity.y += m_fImpulse->GetValueFloat();
}

void MShip::UpdateLogic( int iDelta )
{
	if( m_vVelocity.Magnitude() <= 0.0f )
		return;
	
	m_vAcceleration = -m_vVelocity.Normalised();

	// Friction force = constant * mg.
	// F=Ma, so acceleration = force/mass = constant*g
	m_vAcceleration *= m_fFriction->GetValueFloat();

	MVector2 vDeltaVelocity = ( ( m_vAcceleration * (float)iDelta ) / 1000.0f );

	// Cap magnitude of change in velocity to remove integration errors
	if( vDeltaVelocity.Magnitude() > m_vVelocity.Magnitude() )
		m_vVelocity.Zero();
	else m_vVelocity += vDeltaVelocity;

	m_vPosition += ( ( m_vVelocity * (float)iDelta ) / 1000.0f );

	if(m_vVelocity.Magnitude() < m_fCutOff->GetValueFloat()) 
		m_vVelocity.Zero();
		
	m_ShipSprite->SetPosition((int)m_vPosition.x,(int)m_vPosition.y);
}

void MShip::CollisionEvent( IEntityPtr pEntity, int iDelta )
{
	m_vPosition += ( ( -m_vVelocity * (float)iDelta ) / 1000.0f );
	m_vVelocity.Zero();
	m_ShipSprite->SetPosition((int)m_vPosition.x,(int)m_vPosition.y);
}

bool MShip::GetActive( void )
{
	return m_bActive;
}