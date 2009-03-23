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
    printf(" -> MVarManager object destructed.\n");
    
    // Free all of the allocated variables.
    for( int i = 0; i < (int)m_Container.size(); i++ ) {
        if( m_Container[i] ) {
            delete m_Container[i];
        }
    }
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
    for( int i = 0; i < (int)m_Container.size(); i++ ) {
        if( !strcmp(m_Container[i]->GetName(),pszName) ) {
            return m_Container[i];
        }
    }
    
    return NULL;
}
