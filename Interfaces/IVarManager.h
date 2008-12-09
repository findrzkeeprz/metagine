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

#include "../Interfaces/IVar.h"

class IVarManager
{
public:
    
    /// Virtual destructor method.
    virtual ~IVarManager( void ) { };
    
    /// Virtual function to create a new variable and return a pointer (integer).
    virtual IVar* CreateVar( const char* pszName, int iValue ) = 0;
    
    /// Virtual function to create a new variable and return a pointer (integer).
    virtual IVar* CreateVar( const char* pszName, float fValue ) = 0;
    
    /// Virtual function to create a new variable and return a pointer (integer).
    virtual IVar* CreateVar( const char* pszName, bool bValue ) = 0;
    
    /// Virtual function to return a variable's pointer by name, if any.
    virtual IVar* GetVarByName( const char* pszName ) = 0;
};

#endif // _IVARMANAGER_H_
