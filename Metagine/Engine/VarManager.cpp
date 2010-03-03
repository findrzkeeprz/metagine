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
	// Free all of the unallocated variables.
	map<string,IVarPtr>::iterator var = m_Container.begin();
	for( var = m_Container.begin(); var != m_Container.end(); ++var ) {
		if( var->second ) var->second.reset();
	}

	m_Container.clear();

    printf(" -> MVarManager object destructed.\n");
}

IVarPtr MVarManager::CreateVar( const string& sName, int iValue )
{
    IVarPtr pResult;
    
    if( !GetVarByName(sName) ) {
        pResult = IVarPtr(new MVar(sName,iValue));
        m_Container.insert(make_pair(sName,pResult));
    }
    
    return pResult;
}

IVarPtr MVarManager::CreateVar( const string& sName, float fValue )
{
    IVarPtr pResult;
    
    if( !GetVarByName(sName) ) {
        pResult = IVarPtr(new MVar(sName,fValue));
        m_Container.insert(make_pair(sName,pResult));
    }
    
    return pResult;
}

IVarPtr MVarManager::CreateVar( const string& sName, bool bValue )
{
    IVarPtr pResult;
    
    if( !GetVarByName(sName) ) {
        pResult = IVarPtr(new MVar(sName,bValue));
        m_Container.insert(make_pair(sName,pResult));
    }
    
    return pResult;
}

IVarPtr MVarManager::GetVarByName( const string& sName )
{
	map<string,IVarPtr>::iterator var = m_Container.find(sName);
	if( var == m_Container.end() )
		return IVarPtr();

	return var->second;
}
