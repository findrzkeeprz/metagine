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

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Engine.h"
#include "VarManager.h"
#include "RenderTask.h"
#include "InputTask.h"
#include "Font.h"
#include "OutlineFont.h"
#include "Sprite.h"
#include "Console.h"
#include "CollisionResolver.h"
#include "SurfaceCache.h"
#include "../Public/Exports.h"
#include "AudioTask.h"

MEngine::MEngine( void )
{
    printf(" -> MEngine object created.\n");
}

MEngine::~MEngine( void )
{
    Shutdown();
	printf(" -> MEngine object destructed.\n");
}

void MEngine::Init( void )
{
    printf(" -> MEngine::Init() called.\n");
    
	// Create the main engine tasks.
	m_pVarManager = IVarManagerPtr(new MVarManager());
	m_pTaskManager = MTaskManagerPtr(new MTaskManager());
	m_pRenderer = IRendererPtr(new MRenderTask());
	m_pEntityManager = IEntityManagerPtr(new MEntityTask());
	m_pInputManager = IInputManagerPtr(new MInputTask());
	m_pAudioTask = IAudioTaskPtr(new MAudioTask());

	m_pTaskManager->Attach(m_pInputManager,m_pTaskManager->INPUT_TASK);
	m_pTaskManager->Attach(m_pEntityManager,m_pTaskManager->LOGIC_TASK);
	m_pTaskManager->Attach(m_pAudioTask,m_pTaskManager->AUDIO_TASK);
	m_pTaskManager->Attach(m_pRenderer,m_pTaskManager->RENDER_TASK);
	m_pTaskManager->InitTasks();
	
	// Create the remaining engine components (dependent on above systems).
	m_pConsole = IConsolePtr(new MConsole());
	m_pSurfaceCache = ISurfaceCachePtr(new MSurfaceCache());
	m_pDebugOverlay = MDebugOverlayPtr(new MDebugOverlay(this));
	
	m_pConsole->Init();
	m_pRenderer->RegisterDrawable(m_pConsole);
	m_pRenderer->RegisterDrawable(m_pDebugOverlay);

	// Load the game module.
	/*if( !LoadGameModule() ) {
		printf(" -! ERROR unable to load game module, aborting.\n");
		return false;
	}
	if( !( m_pGame = (IGame*)GetInterfaceByName("MGame") ) ) {
		printf(" -! ERROR unable to get game interface, aborting.\n");
		return false;
	}*/

	m_pInputManager->RegisterListener(m_pConsole);
	m_pConsole->Echo("Testing 1.");
	m_pConsole->Echo("Testing 2.");
	m_pConsole->Echo("Testing 3.");
	m_pConsole->Echo("Testing 4.");
	m_pConsole->Echo("Testing 5.");

	m_GameBoard.Init();
}

void MEngine::Shutdown( void )
{
	printf(" -> MEngine::Shutdown() called.\n");
	
	m_GameBoard.Kill();
	
	m_pConsole.reset();
	m_pDebugOverlay.reset();
	m_pSurfaceCache.reset();
	m_pVarManager.reset();
	m_pTaskManager.reset();
	m_pInputManager.reset();
	m_pEntityManager.reset();
	m_pRenderer.reset();
}

void MEngine::Run( void )
{
	while( m_pTaskManager->GetActive() )
		m_pTaskManager->UpdateTasks();
}

bool MEngine::LoadGameModule( void )
{
	printf(" -> MEngine::LoadGameModule() called.\n");
	
	/*HMODULE hGame = LoadLibraryA("Game86.dll");
	
	if( !hGame ) {
		printf(" -! ERROR loading game module.\n");
		return false;
	}

	// Find the exported function.
	InitGameModule_t pFunc = (InitGameModule_t)GetProcAddress(
		hGame,"InitGameModule");

	if( !pFunc ) {
		printf(" -! ERROR finding InitGameModule export.\n");
		return false;
	}

	// Call the function.
	if( !pFunc(this) ) {
		printf(" -! ERROR something wrong in InitGameModule().\n");
		return false;
	}*/
	
	return true;
}

