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

#ifndef _IENTITY_H_
#define _IENTITY_H_

#include "../Public/Public.h"
#include "../Interfaces/ISprite.h"

// Forward declaration (hack).
class IEntity;
typedef shared_ptr<IEntity> IEntityPtr;

class IEntity
{
public:

    /// Virtual destructor method.
    virtual ~IEntity( void ) { };

	/// Virtual accessor to determine object validity.
    virtual void SetActive( bool bActive ) = 0;
	virtual bool GetActive( void ) = 0;
	virtual bool GetExpired( void ) = 0;
	virtual bool GetCollidable( void ) = 0;
	virtual ISpritePtr GetSprite( void ) = 0;
	virtual void SetVelocity( MVector2& vVelocity ) = 0;
	virtual MVector2 GetVelocity( void ) = 0;
	virtual void SetPosition( MVector2& vPosition ) = 0;
	virtual MVector2 GetPosition( void ) = 0;
	virtual int GetType( void ) = 0;
	
	virtual void CollisionEvent( IEntity* pEntity, const int iType, const float fDelta ) = 0;
	virtual void UpdateLogic( float fDelta ) = 0;
	virtual void VKill( void ) = 0;
};

#endif // _IENTITY_H_
