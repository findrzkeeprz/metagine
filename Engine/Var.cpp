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

#include <string.h>
#include <assert.h>

#include "Var.h"

CVar::CVar( void )
{
    m_pszName = new char[ strlen(CVAR_NULL_STRING) + 1 ];
	strcpy_s(m_pszName,strlen(CVAR_NULL_STRING) + 1,CVAR_NULL_STRING);
    m_iValue = 0;
    m_fValue = 0.0f;
    m_bValue = false;
    m_iType = CVAR_NULL;
}

CVar::CVar( const char* pszName, int iValue )
{
    m_pszName = new char[ strlen(pszName) + 1 ];
	strcpy_s(m_pszName,strlen(pszName) + 1,pszName);
    m_iValue = iValue;
    m_fValue = 0.0f;
    m_bValue = false;
    m_iType = CVAR_INT;
}

CVar::CVar( const char* pszName, float fValue )
{
    m_pszName = new char[ strlen(pszName) + 1 ];
    strcpy_s(m_pszName,strlen(pszName) + 1,pszName);
    m_fValue = fValue;
    m_iValue = 0;
    m_bValue = false;
    m_iType = CVAR_FLOAT;
}

CVar::CVar( const char* pszName, bool bValue )
{
    m_pszName = new char[ strlen(pszName) + 1 ];
    strcpy_s(m_pszName,strlen(pszName) + 1,pszName);
    m_bValue = bValue;
    m_iValue = 0;
    m_fValue = 0.0f;
    m_iType = CVAR_BOOL;
}

CVar::~CVar( void )
{
    if( m_pszName ) {
        delete [] m_pszName;
    }
}

const char* CVar::GetName( void )
{
    return m_pszName;
}

const int CVar::GetType( void )
{
    return m_iType;
}

const int CVar::GetValueInt( void )
{
    assert(m_iType == CVAR_INT);
    
    return m_iValue;
}

const float CVar::GetValueFloat( void )
{
    assert(m_iType == CVAR_FLOAT);
    
    return m_fValue;
}

const bool CVar::GetValueBool( void )
{
    assert(m_iType == CVAR_BOOL);
    
    return m_bValue;
}

void CVar::SetValueInt( int iValue )
{
    m_iValue = iValue;
}

void CVar::SetValueFloat( float fValue )
{
    m_fValue = fValue;
}

void CVar::SetValueBool( bool bValue )
{
    m_bValue = bValue;
}
