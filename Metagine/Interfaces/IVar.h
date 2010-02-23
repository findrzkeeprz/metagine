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

#ifndef _IVAR_H_
#define _IVAR_H_

#include "../Public/Public.h"

class IVar
{
public:
    
    /// Virtual destructor method.
    virtual ~IVar( void ) { };
    
    /// Virtual accessor to return the variable's name.
    virtual const char* GetName( void ) = 0;
    
    /// Virtual accessor to return the datatype of variable.
    virtual const int GetType( void ) = 0;
    
    /// Virtual accessor to return the variable's integer value.
    const virtual int GetValueInt( void ) = 0;
    
    /// Virtual accessor to return the variable's float value.
    const virtual float GetValueFloat( void ) = 0;
    
    /// Virtual accessor to return the variable's boolean value.
    const virtual bool GetValueBool( void ) = 0;
    
    /// Virtual accessor to set the variable's integer value.
    virtual void SetValueInt( int iValue ) = 0;
        
    /// Virtual accessor to set the variable's float value.
    virtual void SetValueFloat( float fValue ) = 0;
    
    /// Virtual accessor to set variable's boolean value.
    virtual void SetValueBool( bool bValue ) = 0;
};

typedef shared_ptr<IVar> IVarPtr;

#endif // _IVAR_H_
