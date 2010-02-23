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

#ifndef _ICOLLISIONRESOLVER_H_
#define _ICOLLISIONRESOLVER_H_

#include "../Public/Public.h"
#include "../Interfaces/IBaseInterface.h"

/// Public interface for the ICollisionResolver class.
class ICollisionResolver : public IBaseInterface
{
public:

	virtual ~ICollisionResolver( void ) { };

	virtual void Shutdown( void ) = 0;
	virtual void ProcessEntityPairs( void ) = 0;
	virtual void DeterminePartition( IEntityPtr pEntity ) = 0;
	virtual void Resolve( vector<IEntityPtr>& Entities, int iDelta ) = 0;
};

typedef shared_ptr<ICollisionResolver> ICollisionResolverPtr;

#endif // _ICOLLISIONRESOLVER_H_
