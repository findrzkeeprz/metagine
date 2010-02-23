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

#include "../Public/Public.h"
#include "../Public/BaseTypes.h"
#include "../Public/Interfaces.h"

#include "OutlineFont.h"
#include "Sprite.h"

/// Fix me.
class MConsole : public IConsole, public noncopyable
{
public:

	/// Default constructor.
	MConsole( void );

	/// Destructor method.
	/// Perform required cleanup operations on graphical subsystems and free
	/// any allocated resources.
	~MConsole( void );

	// Documented in IConsole.h
	bool Init( void );
	void Shutdown( void );
	void Echo( const char* pszText, ... );
	//bool RegisterCommand( IConCommand* pCommand );

	// Documented in IDrawable.h
	void Render( void* pSurface );
	bool GetActive( void );
	float GetDepth( void );

	// Documented in IInputListener.h
	void UpdateInput( const bool bKeys[], const int iKey, const bool bKeyDown );

private:

	// Documented in IConsole.h
	void Execute( const  string& sCmd );

private:

	IVarPtr m_bActive;							///< Determines whether visible/receiving input.
	IVarPtr m_iFontSpacing;						///< Font spacing between console lines.
	IVarPtr m_iPositionX;						///< X coordinate of the console;
	IVarPtr m_iPositionYon;						///< Y coordinate of the console (on-screen);
	IVarPtr m_iPositionYoff;					///< Y coordinate of the console (off-screen);
	IVarPtr m_iScrollFactor;					///< The rate at which the console scrolls in and out.
	bool m_bToggleAnimUp;						///< Toggle the scroll out animation.
	bool m_bToggleAnimDown;						///< Toggle the scroll in animation.
	bool m_bToggling;							///< Currently toggling animation - don't interrupt.
	vector<string> m_BackBuffer;		///< Main console buffer storage.
	vector<string> m_CmdHistory;		///< Previously executed command storage.
	string m_sCurrentBuffer;				///< Current command input buffer.
	shared_ptr<MFont> m_Font;			///< Font to draw the console buffer.
	int m_iScrollPoint;
};

//typedef MSingleton<MConsole> Console;

#endif // _CONSOLE_H_
