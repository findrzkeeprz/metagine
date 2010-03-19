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

#include "BaseEntity.h"

MBaseEntity::MBaseEntity( MVector2 vPosition, MVector2 vVelocity, bool bActive, bool bCollidable, int iType ) :
m_bActive(bActive),
m_bExpired(false),
m_bCollidable(bCollidable),
m_iType(iType)
{
	m_vPosition = vPosition;
	m_vVelocity = vVelocity;
}

MBaseEntity::~MBaseEntity( void )
{
	m_bActive = false;
	m_bExpired = true;
	m_vPosition.Zero();
	m_vVelocity.Zero();
	m_pSprite.reset();
}

void MBaseEntity::SetActive( bool bActive )
{
	m_bActive = bActive;
}

bool MBaseEntity::GetActive( void )
{
	return m_bActive;
}

bool MBaseEntity::GetExpired( void )
{
	return m_bExpired;
}

bool MBaseEntity::GetCollidable( void )
{
	return m_bCollidable;
}

ISpritePtr MBaseEntity::GetSprite( void )
{
	return m_pSprite;
}

void MBaseEntity::SetVelocity( MVector2& vVelocity )
{
	m_vVelocity = vVelocity;
}

MVector2 MBaseEntity::GetVelocity( void )
{
	return m_vVelocity;
}

void MBaseEntity::SetPosition( MVector2& vPosition )
{
	m_vPosition = vPosition;
	if( m_pSprite) 
		m_pSprite->SetPosition(m_vPosition.x,m_vPosition.y);
}

MVector2 MBaseEntity::GetPosition( void )
{
	return m_vPosition;
}

int MBaseEntity::GetType( void )
{
	return m_iType;
}

void MBaseEntity::UpdateLogic( float fDelta )
{
}

void MBaseEntity::CollisionEvent( IEntity* pEntity, const int iType, const float fDelta )
{
}

void MBaseEntity::VKill( void )
{
}