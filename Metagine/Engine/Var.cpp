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

#include "Var.h"

MVar::MVar( void ) :
m_sName(CVAR_NULL_STRING),
m_iValue(0),
m_fValue(0.0f),
m_bValue(false),
m_iType(CVAR_NULL)
{
}

MVar::MVar( const char* pszName, int iValue ) :
m_sName(pszName),
m_iValue(iValue),
m_fValue(0.0f),
m_bValue(false),
m_iType(CVAR_INT)
{
}

MVar::MVar( const char* pszName, float fValue ) :
m_sName(pszName),
m_iValue(0),
m_fValue(fValue),
m_bValue(false),
m_iType(CVAR_FLOAT)
{
}

MVar::MVar( const char* pszName, bool bValue ) :
m_sName(pszName),
m_iValue(0),
m_fValue(0.0f),
m_bValue(bValue),
m_iType(CVAR_BOOL)
{
}

MVar::~MVar( void )
{
}

const char* MVar::GetName( void )
{
    return m_sName.c_str();
}

const int MVar::GetType( void )
{
    return m_iType;
}

const int MVar::GetValueInt( void )
{
    assert(m_iType == CVAR_INT);
    
    return m_iValue;
}

const float MVar::GetValueFloat( void )
{
    assert(m_iType == CVAR_FLOAT);
    
    return m_fValue;
}

const bool MVar::GetValueBool( void )
{
    assert(m_iType == CVAR_BOOL);
    
    return m_bValue;
}

void MVar::SetValueInt( int iValue )
{
    m_iValue = iValue;
}

void MVar::SetValueFloat( float fValue )
{
    m_fValue = fValue;
}

void MVar::SetValueBool( bool bValue )
{
    m_bValue = bValue;
}
