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
#include "../Includes/SDL/SDL.h"
#include "InputManager.h"

MInputManager::MInputManager( void )
{
    printf(" -> MInputManager object created.\n");

	memset(&m_bKeysHeld,0,sizeof(m_bKeysHeld));
}

MInputManager::~MInputManager( void )
{
    printf(" -> MInputManager object destructed.\n");
}

bool MInputManager::Init( void )
{
	//SDL_EnableKeyRepeat(0,SDL_DEFAULT_REPEAT_INTERVAL);
	//SDL_EnableKeyRepeat(1,1);

	return true;
}

void MInputManager::Shutdown( void )
{
	printf(" -> MInputManager::Shutdown() called.\n");
    
    // Delete allocated objects.
    std::vector<IInputListenerPtr>::reverse_iterator it;
	for( it = m_Listeners.rbegin(); it < m_Listeners.rend(); ++it )
		if( (*it) ) {
			printf(" -> Releasing input listener object (0x%X).\n",(*it).get());
			it->reset();
		}
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
	/*std::vector<IInputListener*>::iterator it;
	for( it = m_Listeners.begin(); it < m_Listeners.end(); ++it ) {
		if( (*it) == pListener ) {
			printf(" -> Removing object (0x%X) from input listeners.\n",pListener);
			m_Listeners.erase(it);
		}
	}*/

	std::vector<IInputListenerPtr>::iterator it = m_Listeners.begin();
	while( it != m_Listeners.end() ) {
		if( *it == pListener ) {
			printf(" -> Removing object (0x%X) from input listeners.\n",pListener);
			it = m_Listeners.erase(it);
		} else ++it;
	}
}

void MInputManager::Update( int iKey, bool bKeyDown )
{
	m_bKeysHeld[iKey] = bKeyDown ? true : false;
	
	std::vector<IInputListenerPtr>::iterator it;
	for( it = m_Listeners.begin(); it < m_Listeners.end(); ++it ) {
		(*it)->UpdateInput(m_bKeysHeld,iKey,bKeyDown);
	}
}