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

#ifndef _CENGINE_H_
#define _CENGINE_H_

#include "../Interfaces/IEngine.h"
#include "CVarManager.h"
#include "../Public/CSingleton.h"

class CEngine : public IEngine
{
public:

    /// Default constructor (takes no arguments).
    CEngine( void );
    
    /// Destructor method.
    ~CEngine( void );
    
    /// Function to initialize the main engine functionality.
    bool Init( void );
    
    /// Function to initialize the main engine functionality.
    void Shutdown( void );
    
    /// Accessor to get a pointer to the variable manager.
    const IVarManager* GetVarManager( void );
};

typedef CSingleton<CEngine> Engine;

#endif // _CENGINE_H_
