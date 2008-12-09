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

#ifndef _CVARMANAGER_H_
#define _CVARMANAGER_H_

#include <vector>
#include "../Interfaces/IVarManager.h"
#include "CVar.h"

class CVarManager : public IVarManager
{
public:

    /// Default constructor (takes no arguments).
    CVarManager( void );
    
    /// Destructor method.
    ~CVarManager( void );
    
    /// Create a new variable and return a pointer (integer).
    IVar* CreateVar( const char* pszName, int iValue );
    
    /// Create a new variable and return a pointer (integer).
    IVar* CreateVar( const char* pszName, float fValue );
    
    /// Create a new variable and return a pointer (integer).
    IVar* CreateVar( const char* pszName, bool bValue );
    
    /// Return a variable's pointer by name, if any.
    IVar* GetVarByName( const char* pszName );
    
private:

    /// Container to catalog all variables created through this class.
    std::vector<IVar*> m_Container;
};

#endif // _CVARMANAGER_H_
