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

class MBaseProjectile : public MBaseEntity
{
public:

	MBaseProjectile( MVector2 vPosition, MVector2 vVelocity, int iType );
	~MBaseProjectile( void );

	// Documented in IEntity.h
	void UpdateLogic( float fDelta );
	void CollisionEvent( const IEntity* pEntity, const int iType, const float fDelta );
	void VKill( void );

private:

	MVector2 m_vAcceleration;
};