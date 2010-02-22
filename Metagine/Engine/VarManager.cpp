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
#include <string.h>
#include "VarManager.h"

MVarManager::MVarManager( void )
{
    printf(" -> MVarManager object created.\n");
}

MVarManager::~MVarManager( void )
{
	// Free all of the allocated variables.
    std::vector<IVar*>::iterator it;
    for( it = m_Container.begin(); it < m_Container.end(); ++it ) {
    	if( (*it) ) {
            delete (*it);
        }
    }

    printf(" -> MVarManager object destructed.\n");
}

IVar* MVarManager::CreateVar( const char* pszName, int iValue )
{
    MVar* pResult = NULL;
    
    if( !GetVarByName(pszName) ) {
        pResult = new MVar(pszName,iValue);
        m_Container.push_back(pResult);
    }
    
    return pResult;
}

IVar* MVarManager::CreateVar( const char* pszName, float fValue )
{
    MVar* pResult = NULL;
    
    if( !GetVarByName(pszName) ) {
        pResult = new MVar(pszName,fValue);
        m_Container.push_back(pResult);
    }
    
    return pResult;
}

IVar* MVarManager::CreateVar( const char* pszName, bool bValue )
{
    MVar* pResult = NULL;
    
    if( !GetVarByName(pszName) ) {
        pResult = new MVar(pszName,bValue);
        m_Container.push_back(pResult);
    }
    
    return pResult;
}

IVar* MVarManager::GetVarByName( const char* pszName )
{
    // Compare each variable against the specified name.
	std::vector<IVar*>::iterator it;
	for( it = m_Container.begin(); it < m_Container.end(); ++it ) {
        if( !strcmp((*it)->GetName(),pszName) ) {
            return (*it);
        }
    }
    
    return NULL;
}
