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

#include "AudioTask.h"

MAudioTask::MAudioTask( void )
{
    printf(" -> MAudioTask object created.\n");
}

MAudioTask::~MAudioTask( void )
{
	printf(" -> MAudioTask object destructed.\n");
}

void MAudioTask::VInit( void )
{
	printf(" -> MAudioTask::VInit() called.\n");

	m_AudioCache = MAudioCachePtr(new MAudioCache());
	printf(" -> Initialising FMOD subsystem.\n");
	FSOUND_Init(44100,32,0);
}

void MAudioTask::VKill( void )
{
	printf(" -> MAudioTask::VKill() called.\n");

	m_AudioCache.reset();
	m_AudioQueue.clear();

	FSOUND_Close();
}

void MAudioTask::VFrame( const int iDelta )
{
	// Render all queued objects.
	vector<FSOUND_SAMPLE*>::iterator sample;
	for( sample = m_AudioQueue.begin(); sample < m_AudioQueue.end(); ++sample )
		FSOUND_PlaySound(FSOUND_FREE,(*sample));

	m_AudioQueue.clear();
}

void MAudioTask::PlaySound( const string sName )
{
	FSOUND_SAMPLE* pSample = NULL;
	if( ( pSample = m_AudioCache->LoadSound(sName) ) == NULL ) {
		printf(" -! ERROR queuing sound for playback in MAudioTask::PlaySound().\n");
		return;
	}
	
	m_AudioQueue.push_back(pSample);
	printf(" -> Registered object (0x%X) with audio queue.\n",pSample);
}