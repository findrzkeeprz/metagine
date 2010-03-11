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

#include "../Public/Public.h"
#include "../Public/BaseTypes.h"

#define CVAR_NULL_STRING "(null)"

union VarData
{
	int iValue;
	float fValue;  
	bool bValue;
};

class MVar : public IVar
{
public:
    
    /// Default constructor (takes no arguments).
    MVar( void );

    /// Custom constructor (integer).
    MVar( const string& sName, const int iValue );
    
    /// Custom constructor (float).
    MVar( const string& sName, const float fValue );
    
    /// Custom constructor (boolean).
    MVar( const string& sName, const bool bValue );
    
    /// Destructor method.
    ~MVar( void );
    
    /// Return the variable's name.
    const char* GetName( void ) const;
    
    /// Return the datatype of variable.
    const int GetType( void ) const;
    
    /// Return the variable's integer value.
    const int GetValueInt( void ) const;
    
    /// Return the variable's float value.
    const float GetValueFloat( void ) const;
    
    /// Return the variable's boolean value.
	const bool GetValueBool( void ) const;
    
    /// Set the variable's integer value.
    void SetValueInt( const int iValue );
    
    /// Set the variable's float value.
    void SetValueFloat( const float fValue );
    
    /// Set the variable's boolean value.
    void SetValueBool( const bool bValue );
    
    /// Enum to define the different variable datatypes.
    enum Type { CVAR_NULL, CVAR_INT, CVAR_FLOAT, CVAR_BOOL };
    
private:
    
    /// Unique name of the variable.
	string m_sName;
    
    /// The type of variable, represented by an enum.
    int m_iType;
    
    /// Value of the variable.
	VarData m_Value;
};

#endif // _CVAR_H_
