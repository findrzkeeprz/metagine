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

#ifndef _AUDIOTASK_H_
#define _AUDIOTASK_H_

#include "ThirdParty.h"
#include "AudioCache.h"
#include "../Public/Public.h"
#include "../Public/BaseTypes.h"
#include "../Public/Interfaces.h"

class MAudioTask : public IAudioTask, public noncopyable
{
public:

	MAudioTask( void );
	~MAudioTask( void );

	void VInit( void );
	void VKill( void );
	void VFrame( const float fDelta );

	void PlaySound( const string sName );

private:

	vector<FSOUND_SAMPLE*> m_AudioQueue;
	MAudioCachePtr m_AudioCache;
};

#endif // _AUDIOTASK_H_
