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

#include <vector>
#include "../Interfaces/IEngine.h"
#include "../Public/Singleton.h"

class MEngine : public IEngine
{
public:

    /// Default constructor (takes no arguments).
    MEngine( void );
    
    /// Destructor method.
    ~MEngine( void );
    
    /// Function to initialize the main engine functionality.
    bool Init( void );
    
    /// Function to initialize the main engine functionality.
    void Shutdown( void );

    /// Register a public game interface with the main game module.
    bool RegisterInterface( IBaseInterface* pInterface );

	/// Main application loop.
	void Run( void );

    /// Virtual function to fetch an interface pointer via a given name.
    /// This function should return a NULL pointer if the interface is not found.    
    IBaseInterface* GetInterfaceByName( const char* pszName );
    
private:

    /// Container of all registered game interfaces.
    std::vector<IBaseInterface*> m_Interfaces;

	// Is the engine currently running.
	bool m_bActive;
};

typedef MSingleton<MEngine> Engine;

#endif // _CENGINE_H_
