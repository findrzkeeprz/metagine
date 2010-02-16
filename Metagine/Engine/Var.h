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

#ifndef _CVAR_H_
#define _CVAR_H_

#include "../Interfaces/IVar.h"

#define CVAR_NULL_STRING "(null)"

class MVar : public IVar
{
public:
    
    /// Default constructor (takes no arguments).
    MVar( void );

    /// Custom constructor (integer).
    MVar( const char* pszName, int iValue );
    
    /// Custom constructor (float).
    MVar( const char* pszName, float fValue );
    
    /// Custom constructor (boolean).
    MVar( const char* pszName, bool bValue );
    
    /// Destructor method.
    ~MVar( void );
    
    /// Return the variable's name.
    const char* GetName( void );
    
    /// Return the datatype of variable.
    const int GetType( void );
    
    /// Return the variable's integer value.
    const int GetValueInt( void );
    
    /// Return the variable's float value.
    const float GetValueFloat( void );
    
    /// Return the variable's boolean value.
	const bool GetValueBool( void );
    
    /// Set the variable's integer value.
    void SetValueInt( int iValue );
    
    /// Set the variable's float value.
    void SetValueFloat( float fValue );
    
    /// Set the variable's boolean value.
    void SetValueBool( bool bValue );
    
    /// Enum to define the different variable datatypes.
    enum Type { CVAR_NULL, CVAR_INT, CVAR_FLOAT, CVAR_BOOL };
    
private:
    
    /// Unique name of the variable.
    char* m_pszName;
    
    /// The type of variable, represented by an enum.
    int m_iType;
    
    /// Integer value of the variable.
    int m_iValue;
    
    /// Float value of the variable.
    float m_fValue;
    
    // Boolean value of the variable.
    bool m_bValue;
};

#endif // _CVAR_H_
