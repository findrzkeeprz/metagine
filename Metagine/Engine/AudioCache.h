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

#ifndef _AUDIOCACHE_H_
#define _AUDIOCACHE_H_

#include "../Public/Public.h"
#include "ThirdParty.h"

/// Fix me.
class MAudioCache
{
public:

	MAudioCache( void );
	~MAudioCache( void );

	FSOUND_SAMPLE* LoadSound( const string sName );

private:

	map<string,FSOUND_SAMPLE*> m_AudioSamples;
};

typedef shared_ptr<MAudioCache> MAudioCachePtr;

#endif // _SURFACECACHE_H_
