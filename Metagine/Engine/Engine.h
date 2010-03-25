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

#ifndef _MENGINE_H_
#define _MENGINE_H_

#include "ThirdParty.h"
#include "../Public/Public.h"
#include "../Public/BaseTypes.h"
#include "../Public/Interfaces.h"

#include "Console.h"
#include "VarManager.h"
#include "RenderTask.h"
#include "InputTask.h"
#include "EntityTask.h"
#include "AudioTask.h"
#include "TaskManager.h"
#include "DebugOverlay.h"

/// Main game engine interface.
/// This object is responsible for the creation and
/// destruction of all other crucial game systems. It should be the first and
/// last piece of code that is executed at game runtime. This object is also
/// responsible for interfacing game components through a simple interface
/// tracking system.
class MEngine : public noncopyable
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
    
    void Init( void );
    void Shutdown( void );
	
public:

    void Run( void );
	
	// Load the game module.
	bool LoadGameModule( void );

public:

	shared_ptr<MConsole>		Console( void );
	shared_ptr<MVarManager>		VarManager( void );
	shared_ptr<MRenderTask>		Renderer( void );
	shared_ptr<MInputTask>		InputManager( void );
	shared_ptr<MEntityTask>		EntityManager( void );
	shared_ptr<MAudioTask>		AudioTask( void );
	shared_ptr<MTaskManager>	TaskManager( void );

private:

	//shared_ptr m_GameBoard;
	shared_ptr<MConsole>		m_pConsole;
	shared_ptr<MVarManager>		m_pVarManager;
	shared_ptr<MRenderTask>		m_pRenderTask;
	shared_ptr<MInputTask>		m_pInputTask;
	shared_ptr<MEntityTask>		m_pEntityTask;
	shared_ptr<MAudioTask>		m_pAudioTask;
	shared_ptr<MTaskManager>	m_pTaskManager;
	shared_ptr<MDebugOverlay>	m_pDebugOverlay;

	/*IConsolePtr m_pConsole;
	IVarManagerPtr m_pVarManager;
	IRendererPtr m_pRenderer;
	IInputManagerPtr m_pInputManager;
	IEntityManagerPtr m_pEntityManager;
	ISurfaceCachePtr m_pSurfaceCache;
	IAudioTaskPtr m_pAudioTask;
	MTaskManagerPtr m_pTaskManager;
	MDebugOverlayPtr m_pDebugOverlay;*

	//IEntity
	// Game interface pointer.
	//IGame* m_pGame;*/
};

#endif // _MENGINE_H_
