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

#include "PlayerShield.h"
#include "../Metagine/Engine/Engine.h"
#include "../Metagine/Engine/Sprite.h"
#include "../Metagine/Engine/RenderTask.h"

MPlayerShield::MPlayerShield( MVector2 vPosition, MVector2 vVelocity ) :
MBaseEntity(vPosition,vVelocity,true,true,ENTITY_PLAYER_SHIELD)
{
	m_pSprite = ISpritePtr(new MSprite("Manifests/PlayerShield.xml"));
	m_pSprite->SetActive(false);
	Engine::GetInstance()->Renderer()->RegisterDrawable(m_pSprite);
	m_pSprite->SetPosition(m_vPosition.x,m_vPosition.y);
}

MPlayerShield::~MPlayerShield( void )
{
	Engine::GetInstance()->Renderer()->RemoveDrawable(m_pSprite);
	printf(" -> MPlayerShield object deleted.\n");
}

void MPlayerShield::UpdateLogic( float fDelta )
{
	m_pSprite->AnimateCycle();
	
	// Expire after animation has finished.
	/*m_vPosition += ( ( m_vVelocity * (float)fDelta ) / 1000.0f );
	m_pSprite->SetPosition(m_vPosition.x,m_vPosition.y);
	if( !m_pSprite->Animate(false) )
		m_bExpired = true;*/
}

void MPlayerShield::SetActive( bool bActive )
{
	m_bActive = bActive;

}

void MPlayerShield::VKill( void )
{
	Engine::GetInstance()->Renderer()->RemoveDrawable(m_pSprite);
}