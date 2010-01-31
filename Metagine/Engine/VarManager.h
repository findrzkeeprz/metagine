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

#define VARMANAGER_NAME "MVarManager"
#define VARMANAGER_VERSION "01"

#include <vector>
#include "../Public/Singleton.h"
#include "../Interfaces/IVarManager.h"
#include "Var.h"

/// Game variable management class.
/// This object is responsible for creating and managing game variables which
/// are often referred to as 'cvars' in other game engines such as Quake. This
/// is a factory type object and manages the creation, deletion and tracking
/// of any variables that are created.
class MVarManager : public IVarManager
{
public:

    /// Default constructor.
    MVarManager( void );
    
    /// Destructor method.
    /// Recursively deletes any existing MVar objects that are presently
    /// registered with the manager.
    ~MVarManager( void );

    // Documented in IBaseInterface.h
    const char* GetName( void ) { return VARMANAGER_NAME; }
    const char* GetVersion( void ) { return VARMANAGER_VERSION; }
    
    // Documented in IVarManager.h
    IVar* CreateVar( const char* pszName, int iValue );
    IVar* CreateVar( const char* pszName, float fValue );
    IVar* CreateVar( const char* pszName, bool bValue );
    IVar* GetVarByName( const char* pszName );
    
private:

    std::vector<IVar*> m_Container; ///< Container to catalog all variables created through this object.
};

typedef MSingleton<MVarManager> VarManager;

#endif // _CVARMANAGER_H_
