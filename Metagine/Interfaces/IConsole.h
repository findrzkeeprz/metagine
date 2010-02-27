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

#ifndef _ICONSOLE_H_
#define _ICONSOLE_H_

#include "../Public/Public.h"
#include "../Interfaces/ITask.h"
#include "../Interfaces/IInputListener.h"
#include "../Interfaces/IDrawable.h"

/// Public interface for the IConsole class.
class IConsole : public IInputListener, public IDrawable
{
public:

	virtual ~IConsole( void ) { };

	virtual bool Init( void ) = 0;
	virtual void Shutdown( void ) = 0;
	virtual void Echo( const char* pszText, ... ) = 0;
};

typedef shared_ptr<IConsole> IConsolePtr;

#endif // _ICONSOLE_H_
