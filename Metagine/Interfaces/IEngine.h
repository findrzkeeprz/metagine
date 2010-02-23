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

#include "../Public/Public.h"
#include "../Interfaces/IBaseInterface.h"

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
    virtual bool RegisterInterface( IBaseInterfacePtr pInterface ) = 0;

    /// Main game engine loop.
    /// Responsible for updating all main game components at regular frame
    /// intervals. The game will spend most of its execution time within this
    /// piece of code.
	virtual void Run( void ) = 0;
};

typedef shared_ptr<IEngine> IEnginePtr;

#endif // _IENGINE_H_
