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

#ifndef _IENTITYTASK_H_
#define _IENTITYTASK_H_

#include "../Public/Public.h"
#include "../Interfaces/ITask.h"
#include "../Interfaces/IEntity.h"
#include "../Interfaces/ICollisionResolver.h"

/// Public interface for the IEntityTask class.
class IEntityTask : public ITask
{
public:

	virtual ~IEntityTask( void ) { };
	virtual void RegisterEntity( IEntityPtr pEntity ) = 0;
	virtual void RemoveEntity( IEntityPtr pEntity ) = 0;
	virtual ICollisionResolverPtr CollisionResolver( void ) = 0;
};

typedef shared_ptr<IEntityTask> IEntityManagerPtr;

#endif // _IENTITYTASK_H_
