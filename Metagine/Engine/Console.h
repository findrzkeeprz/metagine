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

#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#define CONSOLE_NAME "MConsole"
#define CONSOLE_VERSION "01"

#include "GlobalIncludes.h"
#include "OutlineFont.h"
#include "../Public/Singleton.h"
#include "../Interfaces/IConsole.h"
#include "../Interfaces/IInputListener.h"
#include "../Interfaces/IDrawable.h"

/// Fix me.
class MConsole : public IConsole, public IInputListener, public IDrawable
{
public:

	/// Default constructor.
	MConsole( void );

	/// Destructor method.
	/// Perform required cleanup operations on graphical subsystems and free
	/// any allocated resources.
	~MConsole( void );

	// Documented in IBaseInterface.h
	const char* GetName( void ) { return CONSOLE_NAME; }
	const char* GetVersion( void ) { return CONSOLE_VERSION; }

	// Documented in IConsole.h
	bool Init( void );
	void Shutdown( void );
	void Echo( const char* pszText );
	//bool RegisterCommand( IConCommand* pCommand );

	// Documented in IDrawable.h
	void Render( void* pSurface );
	bool GetActive( void );

	// Documented in IInputListener.h
	void UpdateInput( bool bKeys[] );

private:

	// Documented in IConsole.h
	void Execute( const char* pszString );

private:

	bool m_bActive;								///< Determines whether visible/receiving input.
	bool m_bToggleAnimUp;						///< Toggle the scroll iout animation.
	bool m_bToggleAnimDown;						///< Toggle the scroll in animation.
	bool m_bToggling;							///< Currently toggling animation - don't interrupt.
	std::vector<std::string> m_BackBuffer;		///< Main console buffer storage.
	std::vector<std::string> m_CmdHistory;		///< Previously executed command storage.
	std::string m_sCurrentBuffer;				///< Current command input buffer.
	MOutlineFont* m_Font;						///< Font to draw the console buffer.
	int m_iScrollPoint;
};

typedef MSingleton<MConsole> Console;

#endif // _CONSOLE_H_