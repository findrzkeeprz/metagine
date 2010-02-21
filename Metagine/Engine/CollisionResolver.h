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

#ifndef _COLLISIONRESOLVER_H_
#define _COLLISIONRESOLVER_H_

#define COLLISIONRESOLVER_NAME "MCollisionResolver"
#define COLLISIONRESOLVER_VERSION "01"

#include "GlobalIncludes.h"
#include "../Interfaces/ICollisionResolver.h"

/// Fix me.
class MCollisionResolver : public ICollisionResolver
{
public:

	/// Default constructor.
	MCollisionResolver( void );
	~MCollisionResolver( void );

	// Documented in IBaseInterface.h
	const char* GetName( void ) { return COLLISIONRESOLVER_NAME; }
	const char* GetVersion( void ) { return COLLISIONRESOLVER_VERSION; }

	// Documented in IConsole.h
	//bool Init( void );
	void Shutdown( void );

	void ProcessEntityPairs( void );
	void DeterminePartition( IEntity* pEntity );
	void Resolve( std::vector<IEntity*>& Entities );

private:

	//std::vector<IEntity*> m_Partitions[4];
	std::vector<IEntity*> m_Partitions[4];
	std::vector<std::pair<IEntity*,IEntity*>> m_EntityPairs;
};

typedef MSingleton<MCollisionResolver> CollisionResolver;

#endif // _COLLISIONRESOLVER_H_