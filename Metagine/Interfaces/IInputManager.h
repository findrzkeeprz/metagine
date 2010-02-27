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

#ifndef _IINPUTMANAGER_H_
#define _IINPUTMANAGER_H_

#include "../Public/Public.h"
#include "../Interfaces/ITask.h"
#include "../Interfaces/IInputListener.h"

class IInputManager : public ITask
{
public:

    /// Virtual destructor method.
    virtual ~IInputManager( void ) { };
	
	virtual void SetKeyRepeat( int iDelay, int iInterval ) = 0;
    virtual void RegisterListener( IInputListenerPtr pListener ) = 0;
    virtual void RemoveListener( IInputListenerPtr pListener ) = 0;
};

typedef shared_ptr<IInputManager> IInputManagerPtr;

#endif // _IINPUTMANAGER_H_
