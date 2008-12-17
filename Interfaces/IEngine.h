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

#ifndef _IENGINE_H_
#define _IENGINE_H_

#include "../Interfaces/IVarManager.h"

class IEngine
{
public:
    
    /// Virtual destructor method.
    virtual ~IEngine( void ) { };
    
    /// Virtual function to initialize the main engine functionality.
    virtual bool Init( void ) = 0;
    
    /// Virtual function to initialize the main engine functionality.
    virtual void Shutdown( void ) = 0;

    /// Virtual function to register a public game interface with the main game module.
    virtual bool RegisterInterface( IBaseInterface* pInterface ) = 0;

    /// Virtual function to fetch an interface pointer via a given name.    
    virtual IBaseInterface* GetInterfaceByName( const char* pszName ) = 0;
};

#endif // _IENGINE_H_
