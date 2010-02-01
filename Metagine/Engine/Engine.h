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
#include "../Includes/SDL/SDL.h"
#include "../Interfaces/IEngine.h"
//#include "../Interfaces/IGame.h"
#include "../Public/Singleton.h"

/// Main game engine interface.
/// This object is responsible for the creation and
/// destruction of all other crucial game systems. It should be the first and
/// last piece of code that is executed at game runtime. This object is also
/// responsible for interfacing game components through a simple interface
/// tracking system.
class MEngine : public IEngine
{
public:

    /// Default constructor.
	/// Performs some simple class member initialisation. The main object
	/// initialisation is performed in Init() rather than here.
    MEngine( void );
    

    /// Destructor method.
    /// Makes a call to Shutdown() and triggers a global game engine shutdown
    /// procedure involving all registered IBaseInterface classes.
    ~MEngine( void );
    
    bool Init( void );
    void Shutdown( void );
    bool RegisterInterface( IBaseInterface* pInterface );
	IBaseInterface* GetInterfaceByName( const std::string& sName );

private:

    void Run( void );

    // Handle player input.
    void HandleInput( void );

    // Load the game module.
	bool LoadGameModule( void );

    std::vector<IBaseInterface*> m_Interfaces; 	///< Container of all registered game interfaces.
	bool m_bActive;							   	///< Identifies whether the engine is currently active.
	SDL_Event m_Event;							///< SDL event object.
	int m_iFrameStart;							///< The elapsed time at the start of the current frame.
	int m_iFrameEnd;							///< The elapsed time at the end of the current frame.
	int m_iFrameDuration;						///< The duration of the current frame.

	// Game interface pointer.
	//IGame* m_pGame;
};

typedef MSingleton<MEngine> Engine;

#endif // _CENGINE_H_
