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

#ifndef _IAUDIOTASK_H_
#define _IAUDIOTASK_H_

#include "../Public/Public.h"
#include "../Interfaces/ITask.h"

class IAudioTask : public ITask
{
public:

	virtual ~IAudioTask( void ) { };
	virtual void PlaySound( const string sName ) = 0;
};

typedef shared_ptr<IAudioTask> IAudioTaskPtr;

#endif // _IAUDIOTASK_H_
