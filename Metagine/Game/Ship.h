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

class MShip : public IListenEntity
{
public:

	MShip( void );
	~MShip( void );

	// Documented in IInputListener.h
	void UpdateInput( const bool bKeys[], const int iKey, const bool bKeyDown );

	// Documented in IEntity.h
	void UpdateLogic( int iDelta );
	bool GetActive( void );
	//float GetPositionX( void ) { return m_fPosition[0]; }
	//float GetPositionY( void ) { return m_fPosition[0]; }
	ISpritePtr GetSprite( void ) { return m_ShipSprite; }
	void CollisionEvent( IEntityPtr pEntity, int iDelta );

private:

	ISpritePtr m_ShipSprite;
	MVector2 m_vPosition;
	MVector2 m_vVelocity;
	MVector2 m_vAcceleration;
	IVarPtr m_fFriction;
	IVarPtr m_fImpulse;
	IVarPtr m_fCutOff;
	bool m_bActive;
};

#endif // _SHIP_H_