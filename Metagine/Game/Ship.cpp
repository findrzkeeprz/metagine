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
m_bActive(true)
{
	// This will all need to go through the engine interface in future.
	m_ShipSprite = new MSprite("Ship1.png",0,true,71,0,50,65,255,0,255,0.95f);
	
	// Center the ship on the center of the screen initially.
	int iCenter = (Renderer::GetInstance()->GetScreenWidth() / 2) - ( m_ShipSprite->GetWidth() / 2 );
	m_fPosition[0] = (float)iCenter;
	m_fPosition[1] = 575.0f;
	m_fVelocity[0] = 0.0f;
	m_fVelocity[1] = 0.0f;
	m_ShipSprite->SetPosition((int)m_fPosition[0],(int)m_fPosition[1]);
	
	InputManager::GetInstance()->RegisterListener(this);
	Engine::GetInstance()->RegisterEntity(this);
}

MShip::~MShip( void )
{
}

void MShip::UpdateInput( const bool bKeys[], const int iKey, const bool bKeyDown )
{
	if( !bKeyDown )
		return;

	if( iKey == SDLK_LEFT ) {
		m_fVelocity[0] -= 2.25f;
		//--m_fPosition[0];
		//m_ShipSprite->SetPosition(m_fPosition[0],m_fPosition[1]);
	} else if( iKey == SDLK_RIGHT ) {
		m_fVelocity[0] += 2.25f;
		//++m_fPosition[0];
		//m_ShipSprite->SetPosition(m_fPosition[0],m_fPosition[1]);
	}
}

void MShip::UpdateLogic( int iDelta )
{
	//x += xVel * ( deltaTicks / 1000.f );
	m_fVelocity[0] *= 0.995f;
	m_fPosition[0] += m_fVelocity[0] * ( iDelta / 1000.0f );
	m_fPosition[1] += m_fVelocity[1] * ( iDelta / 1000.0f );
	
	//printf("iDelta: %i\n",iDelta);
	m_ShipSprite->SetPosition((int)m_fPosition[0],(int)m_fPosition[1]);
}

bool MShip::GetActive( void )
{
	return m_bActive;
}