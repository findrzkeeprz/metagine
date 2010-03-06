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


#include "../Interfaces/ISprite.h"
#include "../Interfaces/IEntity.h"

class MBaseProjectile : public IEntity
{
public:

	MBaseProjectile( int iType, float x, float y, float fSpeed );
	~MBaseProjectile( void );

	// Documented in IEntity.h
	void UpdateLogic( float fDelta );
	bool GetActive( void );
	bool GetExpired( void );
	ISpritePtr GetSprite( void ) { return m_TestSprite; }
	void CollisionEvent( const IEntityPtr pEntity, const int iType, const float fDelta );
	void VKill( void );
	void SetVelocity( MVector2& vVelocity );
	MVector2 GetVelocity( void );
	void SetPosition( float x, float y );
	MVector2 GetPosition( void );

private:

	ISpritePtr m_TestSprite;
	MVector2 m_vPosition;
	MVector2 m_vVelocity;
	MVector2 m_vAcceleration;
	bool m_bActive;
	bool m_bExpired;
};