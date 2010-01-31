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

#ifndef _IVARMANAGER_H_
#define _IVARMANAGER_H_

#include "../Interfaces/IBaseInterface.h"
#include "../Interfaces/IVar.h"

/// Public interface for the MVarManager class.
class IVarManager : public IBaseInterface
{
public:

	virtual ~IVarManager( void ) { };

    /// Creates a new integer-type MVar object.
	/// This creates a new MVar object with integer type. The MVar object is
	/// created and automatically registered with the variable manager.
    virtual IVar* CreateVar( const char* pszName, int iValue ) = 0;
    
    /// Creates a new float-type MVar object.
    /// This creates a new MVar object with integer type. The MVar object is
    /// created and automatically registered with the variable manager.
    virtual IVar* CreateVar( const char* pszName, float fValue ) = 0;
    
    /// Creates a new boolean-type MVar object.
    /// This creates a new MVar object with integer type. The MVar object is
    /// created and automatically registered with the variable manager.
    virtual IVar* CreateVar( const char* pszName, bool bValue ) = 0;
    
    /// Gets a pointer to an MVar object by name.
    /// This searches the list of registered variables and returns a pointer to
    /// the object if it exists. Returns NULL if no variable is found. Spelling
    /// must be exact.
    virtual IVar* GetVarByName( const char* pszName ) = 0;
};

#endif // _IVARMANAGER_H_
