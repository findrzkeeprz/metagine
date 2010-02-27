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

#include "InputTask.h"
#include "Engine.h"

MInputTask::MInputTask( void )
{
    printf(" -> MInputTask object created.\n");

	memset(&m_bKeysHeld,0,sizeof(m_bKeysHeld));
}

MInputTask::~MInputTask( void )
{
    printf(" -> MInputTask object destructed.\n");
}

void MInputTask::VInit( void )
{
	//SDL_EnableKeyRepeat(0,SDL_DEFAULT_REPEAT_INTERVAL);
	//SDL_EnableKeyRepeat(1,1);
}

void MInputTask::VKill( void )
{
	printf(" -> MInputTask::Shutdown() called.\n");
    
    // Delete allocated objects.
    vector<IInputListenerPtr>::reverse_iterator it;
	for( it = m_Listeners.rbegin(); it < m_Listeners.rend(); ++it )
		if( (*it) ) {
			printf(" -> Releasing input listener object (0x%X).\n",(*it).get());
			it->reset();
		}
}

void MInputTask::VFrame( const int iDelta )
{
	while( SDL_PollEvent(&m_Event) ) {
		if( m_Event.type == SDL_QUIT ) Engine::GetInstance()->TaskManager()->EarlyAbort();
		else if( m_Event.type == SDL_KEYDOWN ) KeyDownEvent(m_Event.key.keysym.sym);
		else if( m_Event.type == SDL_KEYUP ) KeyUpEvent(m_Event.key.keysym.sym);
	}
}

void MInputTask::KeyDownEvent( int iKey )
{
	m_bKeysHeld[iKey] = true;
	
	vector<IInputListenerPtr>::iterator it;
	for( it = m_Listeners.begin(); it < m_Listeners.end(); ++it )
		(*it)->UpdateInput(m_bKeysHeld,iKey,true);		
}

void MInputTask::KeyUpEvent( int iKey )
{
	m_bKeysHeld[iKey] = false;
	
	vector<IInputListenerPtr>::iterator it;
	for( it = m_Listeners.begin(); it < m_Listeners.end(); ++it )
		(*it)->UpdateInput(m_bKeysHeld,iKey,false);		
}

void MInputTask::SetKeyRepeat( int iDelay, int iInterval )
{
	SDL_EnableKeyRepeat(iDelay,iInterval);
}

void MInputTask::RegisterListener( IInputListenerPtr pListener )
{
	if( !pListener ) {
		// Error msg here
		return;
	}

	m_Listeners.push_back(pListener);
	printf(" -> Registered new input listener object (0x%X).\n",pListener);
}

void MInputTask::RemoveListener( IInputListenerPtr pListener )
{
	vector<IInputListenerPtr>::iterator it = m_Listeners.begin();
	while( it != m_Listeners.end() ) {
		if( *it == pListener ) {
			printf(" -> Removing object (0x%X) from input listeners.\n",pListener);
			it = m_Listeners.erase(it);
		} else ++it;
	}
}