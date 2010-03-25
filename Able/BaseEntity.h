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

#ifndef _BASEENTITY_H_
#define _BASEENTITY_H_

#include "GameTypes.h"
#include "../Metagine/Interfaces/ISprite.h"
#include "../Metagine/Interfaces/IEntity.h"

class MBaseEntity : public IEntity
{
public:

	MBaseEntity( MVector2 vPosition, MVector2 vVelocity, bool bActive, bool bCollidable, int iType );
	virtual ~MBaseEntity( void );

	virtual void SetActive( bool bActive );
	virtual bool GetActive( void );
	virtual bool GetExpired( void );
	virtual bool GetCollidable( void );
	virtual ISpritePtr GetSprite( void );
	
	virtual void SetVelocity( MVector2& vVelocity );
	virtual MVector2 GetVelocity( void );
	virtual void SetPosition( MVector2& vPosition );
	virtual MVector2 GetPosition( void );
	virtual int GetType( void );

	virtual void UpdateLogic( float fDelta );
	virtual void CollisionEvent( IEntity* pEntity, const int iType, const float fDelta );
	virtual void VKill( void );

protected:

	MVector2 m_vPosition;
	MVector2 m_vVelocity;
	bool m_bActive;
	bool m_bExpired;
	bool m_bCollidable;
	ISpritePtr m_pSprite;
	int m_iType;
};

#endif // _BASEENTITY_H_