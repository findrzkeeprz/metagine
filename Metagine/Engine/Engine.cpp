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
    printf(" -> MEngine object destructed.\n");
    
    Shutdown();
}

bool MEngine::Init( void )
{
    printf(" -> MEngine::Init() called.\n");
    
	// Register the main interfaces here.
    if( !RegisterInterface(VarManager::GetInstance()) ) {
        printf(" -! ERROR registering MVarManager object.\n");
        return false;
	} else if( !RegisterInterface(Renderer::GetInstance()) ) {
		printf(" -! ERROR registering MRenderer object.\n");
		return false;
	} else if( !RegisterInterface(InputManager::GetInstance()) ) {
		printf(" -! ERROR registering MInputManager object.\n");
		return false;
	} else if( !RegisterInterface(Console::GetInstance()) ) {
		printf(" -! ERROR registering MConsole object.\n");
		return false;
	}

	// Setup the subsystems.
	if( !Renderer::GetInstance()->Init() ) {
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

	m_iFpsMax = VarManager::GetInstance()->CreateVar("ifpsmax",60);
	m_bFpsCap = VarManager::GetInstance()->CreateVar("bfpscap",true);

	m_bActive = true;
    return true;
}

void MEngine::Shutdown( void )
{
    printf(" -> MEngine::Shutdown() called.\n");
    
    // Delete allocated objects.
    std::vector<IBaseInterface*>::reverse_iterator it;
	for( it = m_Interfaces.rbegin(); it < m_Interfaces.rend(); it++ )
		if( (*it) ) {
			(*it)->Shutdown();
			delete (*it);
			(*it) = NULL;
		}
}

bool MEngine::RegisterInterface( IBaseInterface* pInterface )
{
    assert(pInterface);

    const char* pszName = pInterface->GetName();
    const char* pszVersion = pInterface->GetVersion();

    // Quick error check.    
    if( !pszName ) {
        printf(" -! ERROR empty/null interface name string.\n");
        return false;
    } else if( !pszVersion ) {
        printf(" -! ERROR empty/null interface version string.\n");
        return false;
    } else if( GetInterfaceByName(pszName) ) {
        printf(" -! ERROR registering interface, already exists in collection.\n");
        return false;
    }

    // Register the interface with the container.
    printf(" -> Registering interface '%s' version '%s'.\n",pszName,pszVersion);
    m_Interfaces.push_back(pInterface);
    return true;
}

void MEngine::Run( void )
{
	while( m_bActive ) {
		m_FpsTimer.Start();
		
		HandleInput();
		//m_pGame->Frame();
		Renderer::GetInstance()->Frame();

		// Limit the frame rate.
		if( m_bFpsCap->GetValueBool() ) {
			if( m_FpsTimer.GetTicks() < ( 1000 / m_iFpsMax->GetValueInt()) ) {
				SDL_Delay( ( 1000 / m_iFpsMax->GetValueInt() ) - m_FpsTimer.GetTicks());
			}
		}
	}
}

IBaseInterface* MEngine::GetInterfaceByName( const std::string& sName )
{
	// Iterate through the list.
    for( int i = 0; i < (int)m_Interfaces.size(); i++ ) {
        if( !strcmp(m_Interfaces[i]->GetName(),sName.c_str()) ) {
            return m_Interfaces[i];
        }
    }

    return NULL;
}

void MEngine::HandleInput( void )
{
	//Console::GetInstance()->Echo("I pressed something!");
	
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

