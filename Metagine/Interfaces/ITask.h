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

#ifndef _ITASK_H_
#define _ITASK_H_

#include "../Public/Public.h"

/// Public interface for main game components.
class ITask
{
public:
    
    virtual ~ITask( void ) { };    
	virtual void VInit( void ) = 0;
	virtual void VFrame( const int iDelta ) = 0;
	virtual void VKill( void ) = 0;
};

typedef shared_ptr<ITask> ITaskPtr;

#endif // _ITASK_H_
