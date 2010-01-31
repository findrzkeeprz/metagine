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
	SDL_EnableKeyRepeat(1000,SDL_DEFAULT_REPEAT_INTERVAL);

	return true;
}

void MInputManager::RegisterListener( IInputListener* pListener )
{
	if( !pListener ) {
		// Error msg here
		return;
	}

	m_Listeners.push_back(pListener);
	printf(" -> Registered new input listener object (0x%X).\n",pListener);
}

void MInputManager::RemoveListener( IInputListener* pListener )
{
	std::vector<IInputListener*>::iterator it;
	for( it = m_Listeners.begin(); it < m_Listeners.end(); it++ ) {
		if( (*it) == pListener ) {
			printf(" -> Removing object (0x%X) from input listeners.\n",pListener);
			m_Listeners.erase(it);
		}
	}
}

void MInputManager::Update( int iKey, bool bKeyDown )
{
	memset(&m_bKeysHeld,0,sizeof(m_bKeysHeld));
	m_bKeysHeld[iKey] = bKeyDown ? true : false;
	
	std::vector<IInputListener*>::iterator it;
	for( it = m_Listeners.begin(); it < m_Listeners.end(); it++ ) {
		(*it)->UpdateInput(m_bKeysHeld);
	}
}
