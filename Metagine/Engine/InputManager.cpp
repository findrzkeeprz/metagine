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

#include "InputManager.h"
#include "Engine.h"

MInputManager::MInputManager( void )
{
    printf(" -> MInputManager object created.\n");

	memset(&m_bKeysHeld,0,sizeof(m_bKeysHeld));
}

MInputManager::~MInputManager( void )
{
    printf(" -> MInputManager object destructed.\n");
}

void MInputManager::VInit( void )
{
	//SDL_EnableKeyRepeat(0,SDL_DEFAULT_REPEAT_INTERVAL);
	//SDL_EnableKeyRepeat(1,1);
}

void MInputManager::VKill( void )
{
	printf(" -> MInputManager::Shutdown() called.\n");
    
    // Delete allocated objects.
    vector<IInputListenerPtr>::reverse_iterator it;
	for( it = m_Listeners.rbegin(); it < m_Listeners.rend(); ++it )
		if( (*it) ) {
			printf(" -> Releasing input listener object (0x%X).\n",(*it).get());
			it->reset();
		}
}

void MInputManager::VFrame( const int iDelta )
{
	while( SDL_PollEvent(&m_Event) ) {
		if( m_Event.type == SDL_QUIT ) Engine::GetInstance()->TaskManager()->EarlyAbort();
		else if( m_Event.type == SDL_KEYDOWN ) KeyDownEvent(m_Event.key.keysym.sym);
		else if( m_Event.type == SDL_KEYUP ) KeyUpEvent(m_Event.key.keysym.sym);

		/*if( m_Event.type == SDL_KEYDOWN ||
			m_Event.type == SDL_KEYUP ) {
				m_bKeysHeld[m_Event.key.keysym.sym] = m_Event.type == SDL_KEYDOWN ? true : false;
				vector<IInputListenerPtr>::iterator it;
				for( it = m_Listeners.begin(); it < m_Listeners.end(); ++it ) {
					(*it)->UpdateInput(m_bKeysHeld,m_Event.key.keysym.sym,true);
				}
		}*/
		/*if( m_Event.type == SDL_QUIT ) { 
			//m_bActive = false;
			//Shutdown();
		} else if( m_Event.type == SDL_KEYDOWN ) {
			Engine::GetInstance()->InputManager()->Update(m_Event.key.keysym.sym,true);
		} else if( m_Event.type == SDL_KEYUP ) {
			Engine::GetInstance()->InputManager()->Update(m_Event.key.keysym.sym,false);
		}*/
	}
	
	/*m_bKeysHeld[iKey] = bKeyDown ? true : false;
	
	vector<IInputListenerPtr>::iterator it;
	for( it = m_Listeners.begin(); it < m_Listeners.end(); ++it ) {
		(*it)->UpdateInput(m_bKeysHeld,iKey,bKeyDown);
	}*/
}

void MInputManager::KeyDownEvent( int iKey )
{
	m_bKeysHeld[iKey] = true;
	
	vector<IInputListenerPtr>::iterator it;
	for( it = m_Listeners.begin(); it < m_Listeners.end(); ++it )
		(*it)->UpdateInput(m_bKeysHeld,iKey,true);		
}

void MInputManager::KeyUpEvent( int iKey )
{
	m_bKeysHeld[iKey] = false;
	
	vector<IInputListenerPtr>::iterator it;
	for( it = m_Listeners.begin(); it < m_Listeners.end(); ++it )
		(*it)->UpdateInput(m_bKeysHeld,iKey,false);		
}

void MInputManager::SetKeyRepeat( int iDelay, int iInterval )
{
	SDL_EnableKeyRepeat(iDelay,iInterval);
}

void MInputManager::RegisterListener( IInputListenerPtr pListener )
{
	if( !pListener ) {
		// Error msg here
		return;
	}

	m_Listeners.push_back(pListener);
	printf(" -> Registered new input listener object (0x%X).\n",pListener);
}

void MInputManager::RemoveListener( IInputListenerPtr pListener )
{
	vector<IInputListenerPtr>::iterator it = m_Listeners.begin();
	while( it != m_Listeners.end() ) {
		if( *it == pListener ) {
			printf(" -> Removing object (0x%X) from input listeners.\n",pListener);
			it = m_Listeners.erase(it);
		} else ++it;
	}
}