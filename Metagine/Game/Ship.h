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

#ifndef _SHIP_H_
#define _SHIP_H_

#include "../Interfaces/ISprite.h"
#include "../Interfaces/IInputListener.h"
#include "../Interfaces/IEntity.h"
#include "../Interfaces/IListenEntity.h"
#include "../Interfaces/IVar.h"
#include "../Public/Vector2.h"

#include "BaseEntity.h"

class MShip : public IInputListener, public MBaseEntity
{
public:

	MShip( void );
	~MShip( void );

	// Documented in IInputListener.h
	void UpdateInput( const Uint8* pKeyState, const int iKey, const bool bKeyDown );

	// Documented in IEntity.h
	void UpdateLogic( float fDelta );
	void CollisionEvent( const IEntity* pEntity, const int iType, const float fDelta );
	void VKill( void );

private:

	MVector2 m_vAcceleration;
	IVarPtr m_fFriction;
	IVarPtr m_fImpulse;
	IVarPtr m_fCutOff;
	bool m_bFireLock;
	bool m_bFlipFlop;
};

#endif // _SHIP_H_