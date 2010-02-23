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
#include "Renderer.h"
#include "InputManager.h"
#include "Font.h"
#include "OutlineFont.h"
#include "Sprite.h"
#include "Console.h"
#include "CollisionResolver.h"
#include "../Public/Exports.h"

MEngine::MEngine( void )
{
    printf(" -> MEngine object created.\n");

	//m_iFrameStart = 0;
	//m_iFrameEnd = 0;
	//m_iFrameDuration = 0;
	//m_pGame = NULL;
}

MEngine::~MEngine( void )
{
    Shutdown();
	printf(" -> MEngine object destructed.\n");
}

bool MEngine::Init( void )
{
    printf(" -> MEngine::Init() called.\n");
    
	m_pVarManager = IBaseInterfacePtr(VarManager::GetInstance());
	m_pRenderer = IBaseInterfacePtr(Renderer::GetInstance());
	m_pInputManager = IBaseInterfacePtr(InputManager::GetInstance());
	m_pConsole = IBaseInterfacePtr(Console::GetInstance());
	m_pCollisionResolver = IBaseInterfacePtr(CollisionResolver::GetInstance());
	
	// Register the main interfaces here.
    /*if( !RegisterInterface(IBaseInterfacePtr(VarManager::GetInstance())) ) {
        printf(" -! ERROR registering MVarManager object.\n");
        return false;
	} else if( !RegisterInterface(IBaseInterfacePtr(Renderer::GetInstance())) ) {
		printf(" -! ERROR registering MRenderer object.\n");
		return false;
	} else if( !RegisterInterface(IBaseInterfacePtr(InputManager::GetInstance())) ) {
		printf(" -! ERROR registering MInputManager object.\n");
		return false;
	} else if( !RegisterInterface(m_pConsole) ) {
		printf(" -! ERROR registering MConsole object.\n");
		return false;
	} else if( !RegisterInterface(IBaseInterfacePtr(CollisionResolver::GetInstance())) ) {
		printf(" -! ERROR registering MCollisionResolver object.\n");
		return false;
	}*/

	// Setup the subsystems.
	if( !Renderer::GetInstance()->Init(500,650) ) {
		printf(" -! ERROR in Renderer::GetInstance()->Init(), aborting.\n");
		return false;
	} else if( !InputManager::GetInstance()->Init() ) {
		printf(" -! ERROR in InputManager::GetInstance()->Init(), aborting.\n");
		return false;
	} else if( !Console::GetInstance()->Init() ) {
		printf(" -! ERROR in Console::GetInstance()->Init(), aborting.\n");
		return false;
	}

	// Load the game module.
	if( !LoadGameModule() ) {
		printf(" -! ERROR unable to load game module, aborting.\n");
		return false;
	}

	//IConsolePtr pConPtr(Console::GetInstance());
	InputManager::GetInstance()->RegisterListener(shared_dynamic_cast<IInputListener>(m_pConsole));
	Console::GetInstance()->Echo("Testing 1.");
	Console::GetInstance()->Echo("Testing 2.");
	Console::GetInstance()->Echo("Testing 3.");
	Console::GetInstance()->Echo("Testing 4.");
	Console::GetInstance()->Echo("Testing 5.");

	// Get the game interface pointer.
	/*if( !( m_pGame = (IGame*)GetInterfaceByName("MGame") ) ) {
		printf(" -! ERROR unable to get game interface, aborting.\n");
		return false;
	}*/

	m_GameBoard.Init();

	m_iFpsMax = VarManager::GetInstance()->CreateVar("ifpsmax",60);
	m_bFpsCap = VarManager::GetInstance()->CreateVar("bfpscap",true);

	m_GameTimer.Start();

	m_bActive = true;
    return true;
}

void MEngine::Shutdown( void )
{
	printf(" -> MEngine::Shutdown() called.\n");
	
	m_GameBoard.Kill();
	/*m_pVarManager.reset();
	m_pInputManager.reset();
	m_pRenderer.reset();
	m_pConsole.reset();
	m_pCollisionResolver.reset();*/
	m_pVarManager.reset();
	m_pConsole.reset();
	m_pInputManager.reset();
	m_pRenderer.reset();
	m_pCollisionResolver.reset();
	
	// Delete allocated objects.
    /*vector<IBaseInterfacePtr>::reverse_iterator it;
	for( it = m_Interfaces.rbegin(); it < m_Interfaces.rend(); ++it ) {
		if( (*it) ) {
			(*it)->Shutdown();
			printf(" -> Releasing interface object (0x%X).\n",(*it).get());
			it->reset();
		}
	}*/

	vector<IEntityPtr>::iterator ent;
	for( ent = m_Entities.begin(); ent < m_Entities.end(); ++ent ) {
		if( (*ent) ) {
			printf(" -> Releasing entity object (0x%X).\n",(*ent).get());
			ent->reset();
		}
	}

	m_Entities.clear();
}

bool MEngine::RegisterInterface( IBaseInterfacePtr pInterface )
{
    assert(pInterface);

    printf(" -> Registering interface (0x%X).\n",pInterface.get());
    m_Interfaces.push_back(pInterface);
    return true;
}

void MEngine::Run( void )
{
	while( m_bActive ) {
		m_FpsTimer.Start();
		int iDelta = m_GameTimer.GetTicks();
		
		HandleInput();
		UpdateEntities(iDelta);
		CollisionResolver::GetInstance()->Resolve(m_Entities,iDelta);
		m_GameTimer.Start();
		
		Renderer::GetInstance()->Frame();
		
		// Limit the frame rate.
		if( m_bFpsCap->GetValueBool() ) {
			if( m_FpsTimer.GetTicks() < ( 1000 / m_iFpsMax->GetValueInt()) ) {
				SDL_Delay( ( 1000 / m_iFpsMax->GetValueInt() ) - m_FpsTimer.GetTicks());
			}
		}
	}
}

void MEngine::UpdateEntities( int iDelta )
{
	vector<IEntityPtr>::iterator it;
	for( it = m_Entities.begin(); it < m_Entities.end(); ++it )
		if( (*it)->GetActive() )
			(*it)->UpdateLogic(iDelta);
}

bool MEngine::RegisterEntity( IEntityPtr pEntity )
{
	if( !pEntity ) {
		// Error msg here
		return false;
	}

	m_Entities.push_back(pEntity);
	printf(" -> Registered entity (0x%X) with logic queue.\n",pEntity.get());
	
	return true;
}

void MEngine::RemoveEntity( IEntityPtr pEntity )
{
	vector<IEntityPtr>::iterator it = m_Entities.begin();
	while( it != m_Entities.end() ) {
		if( (*it) && (*it == pEntity) ) {
			printf(" -> Removing entity (0x%X) from logic queue.\n",pEntity.get());
			it = m_Entities.erase(it);
		} else ++it;
	}
}

void MEngine::HandleInput( void )
{
	while( SDL_PollEvent(&m_Event) ) {
		// Quit the application.
		if( m_Event.type == SDL_QUIT ) { 
			m_bActive = false;
		} else if( m_Event.type == SDL_KEYDOWN ) {
			InputManager::GetInstance()->Update(m_Event.key.keysym.sym,true);
		} else if( m_Event.type == SDL_KEYUP ) {
			InputManager::GetInstance()->Update(m_Event.key.keysym.sym,false);
		}
	}
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

