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

/// Public interface for the MEngine class.
class IEngine
{
public:
    
    virtual ~IEngine( void ) { };
    
    /// Initialises main engine functionality.
    /// Responsible for the correct initialisation of other game components.
    /// Also responsible for the correct instancing of any Singleton objects
    /// to ensure correct order of object creation.
    virtual bool Init( void ) = 0;
    
    /// Shutdown main engine functionality.
    /// Performs a cleanup on game objects and recursively calls the shutdown
    /// routine of any registered game interfaces in the same order that they
    /// were initially registered with the engine.
    virtual void Shutdown( void ) = 0;

    /// Register a public game interface with the main game module.
    /// Registers the specified game interface with the main engine. From this
    /// point onwards the correct shutdown and deletion of the specified
    /// interface will be handled internally and automatically by the engine.
    /// @param pInterface A pointer to the game interface object.
    virtual bool RegisterInterface( IBaseInterface* pInterface ) = 0;

    /// Returns a pointer to a registered game interface.
    /// This allows external modules to use functionality provided by the main
    /// engine with only access to a class interface definition. This function
    /// should return a NULL pointer if the interface is not found.
    /// @param pszName The agreed name of the registered game interface.
    virtual IBaseInterface* GetInterfaceByName( const char* pszName ) = 0;

    /// Main game engine loop.
    /// Responsible for updating all main game components at regular frame
    /// intervals. The game will spend most of its execution time within this
    /// piece of code.
	virtual void Run( void ) = 0;
};

#endif // _IENGINE_H_
