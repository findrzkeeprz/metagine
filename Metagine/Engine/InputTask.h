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

#ifndef _INPUTTASK_H_
#define _INPUTTASK_H_

#include "../Public/Public.h"
#include "../Public/BaseTypes.h"
#include "../Public/Interfaces.h"
#include "ThirdParty.h"

class MInputTask : public IInputTask, public noncopyable
{
public:

    /// Default constructor (takes no arguments).
	MInputTask( void );

    /// Destructor method.
    ~MInputTask( void );
	
	void VInit( void );
	void VKill( void );
	void VFrame( const float fDelta );
	
	void SetKeyRepeat( int iDelay, int iInterval );
	void RegisterListener( IInputListenerPtr pListener );
    void RemoveListener( IInputListenerPtr pListener );

private:

	void KeyEvent( int iKey, bool bDown );

private:

    /// Container to catalog all variables created through this class.
    vector<IInputListenerPtr> m_Listeners;
	SDL_Event m_Event;
	bool m_bKeysHeld[323];
};

#endif // _INPUTTASK_H_
