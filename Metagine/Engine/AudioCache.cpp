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

#include "AudioCache.h"
	
MAudioCache::MAudioCache( void )
{
	m_AudioSamples.clear();
}

MAudioCache::~MAudioCache( void )
{
	map<string,FSOUND_SAMPLE*>::iterator it = m_AudioSamples.begin();
	for( it = m_AudioSamples.begin(); it != m_AudioSamples.end(); ++it ) {
		FSOUND_Sample_Free(it->second);
	}
	
	m_AudioSamples.clear();
}

FSOUND_SAMPLE* MAudioCache::LoadSound( const string sName )
{
	if( !sName.c_str() ) {
		printf(" -! ERROR invalid file name in MAudioCache::LoadSound().\n");
		return NULL;
	}

	map<string,FSOUND_SAMPLE*>::iterator it = m_AudioSamples.find(sName);
	if( it == m_AudioSamples.end() ) {
		printf(" -> Allocating sample: %s in MAudioCache::LoadSound().\n",sName.c_str());
		
		FSOUND_SAMPLE* pResult = NULL;
		if( ( pResult = FSOUND_Sample_Load(FSOUND_FREE,sName.c_str(),0,0,0) ) == NULL ) {
			printf(" -! ERROR FSOUND_Sample_Load() returned a NULL object.\n");
			return NULL;
		}

		m_AudioSamples.insert(make_pair(sName,pResult));
		return pResult;
	}

	return it->second;
}