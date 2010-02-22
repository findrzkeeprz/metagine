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

#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

#include "../Public/Public.h"
#include "../Public/BaseTypes.h"
#include "../Public/Interfaces.h"

#define INPUTMANAGER_NAME "MInputManager"
#define INPUTMANAGER_VERSION "01"

class MInputManager : public IInputManager
{
public:

    /// Default constructor (takes no arguments).
	MInputManager( void );

    /// Destructor method.
    ~MInputManager( void );

    /// Return the class interface's public name.
    const char* GetName( void ) { return INPUTMANAGER_NAME; }

    /// Return the class interface's version string.
    const char* GetVersion( void ) { return INPUTMANAGER_VERSION; }

	bool Init( void );
	void SetKeyRepeat( int iDelay, int iInterval );
	void RegisterListener( IInputListener* pListener );
    void RemoveListener( IInputListener* pListener );

    void Update( int iKey, bool bKeyDown );

private:

    /// Container to catalog all variables created through this class.
    std::vector<IInputListener*> m_Listeners;
	bool m_bKeysHeld[323];
};

typedef MSingleton<MInputManager> InputManager;

#endif // _INPUTMANAGER_H_
