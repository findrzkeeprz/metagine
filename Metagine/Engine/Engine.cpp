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
    
	// Create the main engine subsystems.
	m_pVarManager			= IVarManagerPtr(new MVarManager());
	m_pRenderer				= IRendererPtr(new MRenderer());
	m_pInputManager			= IInputManagerPtr(new MInputManager());
	m_pConsole				= IConsolePtr(new MConsole());
	m_pCollisionResolver	= ICollisionResolverPtr(new MCollisionResolver());
	
	// Initialize the subsystems.
	if( !m_pRenderer->Init(500,650) ) {
		printf(" -! ERROR unable to initialize renderer, aborting.\n");
		return false;
	} else if( !m_pInputManager->Init() ) {
		printf(" -! ERROR unable to initialize input mananger, aborting.\n");
		return false;
	} else if( !m_pConsole->Init() ) {
		printf(" -! ERROR unable to initialize console, aborting.\n");
		return false;
	}

	// Load the game module.
	if( !LoadGameModule() ) {
		printf(" -! ERROR unable to load game module, aborting.\n");
		return false;
	}

	//IConsolePtr pConPtr(Console::GetInstance());
	//Engine::GetInstance()->InputManager()->RegisterListener(shared_dynamic_cast<IInputListener>(m_pConsole));
	m_pInputManager->RegisterListener(m_pConsole);
	m_pConsole->Echo("Testing 1.");
	m_pConsole->Echo("Testing 2.");
	m_pConsole->Echo("Testing 3.");
	m_pConsole->Echo("Testing 4.");
	m_pConsole->Echo("Testing 5.");

	// Get the game interface pointer.
	/*if( !( m_pGame = (IGame*)GetInterfaceByName("MGame") ) ) {
		printf(" -! ERROR unable to get game interface, aborting.\n");
		return false;
	}*/

	m_GameBoard.Init();

	m_iFpsMax = m_pVarManager->CreateVar("ifpsmax",60);
	m_bFpsCap = m_pVarManager->CreateVar("bfpscap",true);

	m_GameTimer.Start();

	m_bActive = true;
    return true;
}

void MEngine::Shutdown( void )
{
	printf(" -> MEngine::Shutdown() called.\n");
	
	m_GameBoard.Kill();

	m_pVarManager.reset();
	m_pConsole.reset();
	m_pInputManager.reset();
	m_pRenderer.reset();
	m_pCollisionResolver.reset();
	
	vector<IEntityPtr>::iterator ent;
	for( ent = m_Entities.begin(); ent < m_Entities.end(); ++ent ) {
		if( (*ent) ) {
			printf(" -> Releasing entity object (0x%X).\n",(*ent).get());
			ent->reset();
		}
	}

	m_Entities.clear();
}

void MEngine::Run( void )
{
	while( m_bActive ) {
		m_FpsTimer.Start();
		int iDelta = m_GameTimer.GetTicks();
		
		HandleInput();
		UpdateEntities(iDelta);
		m_pCollisionResolver->Resolve(m_Entities,iDelta);
		m_GameTimer.Start();
		
		Engine::GetInstance()->Renderer()->Frame();
		
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
			Engine::GetInstance()->InputManager()->Update(m_Event.key.keysym.sym,true);
		} else if( m_Event.type == SDL_KEYUP ) {
			Engine::GetInstance()->InputManager()->Update(m_Event.key.keysym.sym,false);
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

