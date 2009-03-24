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
#include <string.h>
#include <windows.h>
#include "Engine.h"
#include "VarManager.h"
#include "Renderer.h"

MEngine::MEngine( void )
{
    printf(" -> MEngine object created.\n");

	m_bActive = true;
}

MEngine::~MEngine( void )
{
    printf(" -> MEngine object destructed.\n");
    
    Shutdown();
}

bool MEngine::Init( void )
{
    printf(" -> MEngine::Init() called.\n");
    
    if( !RegisterInterface(VarManager::GetInstance()) ) {
        printf(" -! ERROR registering MVarManager object.\n");
        return false;
	} else if( !RegisterInterface(Renderer::GetInstance()) ) {
		printf(" -! ERROR registering MRenderer object.\n");
		return false;
	}

    return true;
}

void MEngine::Shutdown( void )
{
    printf(" -> MEngine::Shutdown() called.\n");
    
    // Delete allocated objects.
    for( int i = 0; i < (int)m_Interfaces.size(); i++ ) {
        if( m_Interfaces[i] ) {
            m_Interfaces[i]->Shutdown();
			delete m_Interfaces[i];
        }
    }
}

bool MEngine::RegisterInterface( IBaseInterface* pInterface )
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
    } else if( GetInterfaceByName(pszName) ) {
        printf(" -! ERROR registering interface, already exists in collection.\n");
        return false;
    }

    // Register the interface with the container.
    printf(" -> Registering interface '%s' version '%s'.\n",pszName,pszVersion);
    m_Interfaces.push_back(pInterface);
    return true;
}

void MEngine::Run( void )
{
	while( m_bActive ) {
		Sleep(60);
	}
}

IBaseInterface* MEngine::GetInterfaceByName( const char* pszName )
{
    assert(pszName);

    // Iterate through the list.
    for( int i = 0; i < (int)m_Interfaces.size(); i++ ) {
        if( !strcmp(m_Interfaces[i]->GetName(),pszName) ) {
            return m_Interfaces[i];
        }
    }

    return NULL;
}

