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

#ifndef _IBASEINTERFACE_H_
#define _IBASEINTERFACE_H_

#include "../Public/Public.h"

/// Public interface for main game components.
class IBaseInterface
{
public:
    
    virtual ~IBaseInterface( void ) { };    

	/// Shutdown routine for participating interfaces.
    /// This gives interfaces that are registered with the MEngine class an
    /// opportunity to perform cleanup operations before object deletion.
    /// @see MEngine::~MEngine()
    /// @see MEngine::Shutdown()
	virtual void Shutdown( void ) { };
};

typedef boost::shared_ptr<IBaseInterface> IBaseInterfacePtr;

#endif // _IBASEINTERFACE_H_
