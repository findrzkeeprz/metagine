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

// Temp.
#include "../Engine/Engine.h"
#include "../Engine/Sprite.h"
#include "../Engine/InputManager.h"
#include "../Engine/Renderer.h"

MShip::MShip( void ) :
m_bActive(true),
m_bColliding(false)
{
	// This will all need to go through the engine interface in future.
	m_ShipSprite = new MSprite("Ship1.png",0,true,71,0,50,65,255,0,255,0.95f);
	
	// Center the ship on the center of the screen initially.
	int iCenter = (Renderer::GetInstance()->GetScreenWidth() / 2) - ( m_ShipSprite->GetWidth() / 2 );
	m_fPosition[0] = (float)iCenter;
	m_fPosition[1] = 575.0f;
	m_fVelocity[0] = 0.0f;
	m_fVelocity[1] = 0.0f;
	m_fAcceleration[0] = 0.0f;
	m_fAcceleration[1] = 0.0f;
	m_ShipSprite->SetPosition((int)m_fPosition[0],(int)m_fPosition[1]);
	
	InputManager::GetInstance()->RegisterListener(this);
	Engine::GetInstance()->RegisterEntity(this);
}

MShip::~MShip( void )
{
}

void MShip::UpdateInput( const bool bKeys[], const int iKey, const bool bKeyDown )
{
	if( !bKeyDown || m_bColliding)
		return;

	if( iKey == SDLK_LEFT ) {
		m_fAcceleration[0] -= 1.25f;
	} else if( iKey == SDLK_RIGHT ) {
		m_fAcceleration[0] += 1.25f;
	} else if( iKey == SDLK_UP ) {
		m_fAcceleration[1] -= 1.25f;
	} else if( iKey == SDLK_DOWN ) {
		m_fAcceleration[1] += 1.25f;
	}
}

void MShip::UpdateLogic( int iDelta )
{
	//x += xVel * ( deltaTicks / 1000.f );
	if( !m_bColliding ) {
		//m_fVelocity[0] *= 0.95f;
		//m_fVelocity[1] *= 0.95f;
		m_fVelocity[0] += ( m_fAcceleration[0] * ( iDelta / 1000.0f ) ) * 0.95f;
		m_fVelocity[1] += ( m_fAcceleration[1] * ( iDelta / 1000.0f ) ) * 0.95f;
		m_fPosition[0] += m_fVelocity[0] * ( iDelta / 1000.0f );
		m_fPosition[1] += m_fVelocity[1] * ( iDelta / 1000.0f );
		//m_fPosition[0] += -m_fVelocity[0] * ( iDelta / 1000.0f );
		//m_fPosition[1] += -m_fVelocity[1] * ( iDelta / 1000.0f );
	
	//printf("iDelta: %i\n",iDelta);
		m_ShipSprite->SetPosition((int)m_fPosition[0],(int)m_fPosition[1]);
	} else {
		m_fPosition[0] += -m_fVelocity[0] * ( iDelta*2 / 1000.0f );
		m_fPosition[1] += -m_fVelocity[1] * ( iDelta*2 / 1000.0f );
		m_fVelocity[0] = 0.0f;
		m_fVelocity[1] = 0.0f;
		m_ShipSprite->SetPosition((int)m_fPosition[0],(int)m_fPosition[1]);
		m_bColliding = false;
	}
}

void MShip::CollisionEvent( IEntity* pEntity )
{
	//printf("i can haz collisions!\n");
	m_bColliding = true;
}

bool MShip::GetActive( void )
{
	return m_bActive;
}