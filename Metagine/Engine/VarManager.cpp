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

#include "VarManager.h"
#include "Var.h"

MVarManager::MVarManager( void )
{
    printf(" -> MVarManager object created.\n");
}

MVarManager::~MVarManager( void )
{
	// Free all of the allocated variables.
    vector<IVarPtr>::iterator it;
    for( it = m_Container.begin(); it < m_Container.end(); ++it ) {
    	if( (*it) ) {
            printf(" -> Releasing variable object (0x%X).\n",(*it).get());
			(*it).reset();
        }
    }

    printf(" -> MVarManager object destructed.\n");
}

IVarPtr MVarManager::CreateVar( const char* pszName, int iValue )
{
    IVarPtr pResult;
    
    if( !GetVarByName(pszName) ) {
        pResult = IVarPtr(new MVar(pszName,iValue));
        m_Container.push_back(pResult);
    }
    
    return pResult;
}

IVarPtr MVarManager::CreateVar( const char* pszName, float fValue )
{
    IVarPtr pResult;
    
    if( !GetVarByName(pszName) ) {
        pResult = IVarPtr(new MVar(pszName,fValue));
        m_Container.push_back(pResult);
    }
    
    return pResult;
}

IVarPtr MVarManager::CreateVar( const char* pszName, bool bValue )
{
    IVarPtr pResult;
    
    if( !GetVarByName(pszName) ) {
        pResult = IVarPtr(new MVar(pszName,bValue));
        m_Container.push_back(pResult);
    }
    
    return pResult;
}

IVarPtr MVarManager::GetVarByName( const char* pszName )
{
    // Compare each variable against the specified name.
	vector<IVarPtr>::iterator it;
	for( it = m_Container.begin(); it < m_Container.end(); ++it ) {
        if( !strcmp((*it)->GetName(),pszName) ) {
            return (*it);
        }
    }
    
    return IVarPtr();
}
