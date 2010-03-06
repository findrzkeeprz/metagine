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

#ifndef _ENTITYTASK_H_
#define _ENTITYTASK_H_

#include "../Public/Public.h"
#include "../Public/BaseTypes.h"
#include "../Public/Interfaces.h"
#include "CollisionResolver.h"

/// Fix me.
class MEntityTask : public IEntityTask, public noncopyable
{
public:

	/// Default constructor.
	MEntityTask( void );
	~MEntityTask( void );

	void VInit( void );
	void VFrame( const float fDelta );
	void VKill( void );

	void RegisterEntity( IEntityPtr pEntity );
	void RemoveEntity( IEntityPtr pEntity );

	ICollisionResolverPtr CollisionResolver( void ) { return m_pCollisionResolver; }

	int GetEntityCount( void );

private:

	vector<IEntityPtr> m_Entities;
	vector<IEntityPtr> m_ExpiredEntities;
	ICollisionResolverPtr m_pCollisionResolver;
	IEntity* m_pEntities[1024];
};

#endif // _ENTITYTASK_H_