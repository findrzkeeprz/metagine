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

#include <stdio.h>
#include <assert.h>
#include "CEngine.h"
#include "CVarManager.h"

CEngine::CEngine( void )
{
    printf(" -> CEngine object created.\n");
}

CEngine::~CEngine( void )
{
    printf(" -> CEngine object destructed.\n");
    
    Shutdown();
}

bool CEngine::Init( void )
{
    printf(" -> CEngine::Init() called.\n");
    
    if( !RegisterInterface(VarManager::GetInstance()) ) {
        printf(" -! ERROR registering CVarManager object.\n");
        return false;
    }
    
    return true;
}

void CEngine::Shutdown( void )
{
    printf(" -> CEngine::Shutdown() called.\n");
    
    // Delete allocated objects.
    for( int i = 0; i < m_Interfaces.size(); i++ ) {
        if( m_Interfaces[i] ) {
            delete m_Interfaces[i];
        }
    }
}

bool CEngine::RegisterInterface( IBaseInterface* pInterface )
{
    assert(pInterface);

    const char* pszName = pInterface->GetName();
    const char* pszVersion = pInterface->GetVersion();

    // Quick error check.    
    if( !pszName ) {
        printf(" -! ERROR empty/null interface name string.\n");
        return false;
    } else if( !pszVersion ) {
        printf(" -! ERROR empty/null interface version string.\n");
        return false;
    }

    // Register the interface with the container.
    printf(" -> Registering interface '%s' version '%s'.\n",pszName,pszVersion);
    m_Interfaces.push_back(pInterface);
    return true;
}

