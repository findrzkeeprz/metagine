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

#ifndef _RENDERER_H_
#define _RENDERER_H_

#define RENDERER_NAME "MRenderer"
#define RENDERER_VERSION "01"

#include <sdl.h>
#include <sdl_ttf.h>
#include "../Public/Singleton.h"
#include "../Interfaces/IRenderer.h"

class MRenderer : public IRenderer
{
public:

	/// Default constructor (takes no arguments).
	MRenderer( void );

	/// Destructor method.
	~MRenderer( void );

	/// Return the class interface's public name.
	const char* GetName( void ) { return RENDERER_NAME; }

	/// Return the class interface's version string.    
	const char* GetVersion( void ) { return RENDERER_VERSION; }

	bool Init( void );

	void Shutdown( void );

	// Called once per game frame.
	void Frame( void );

private:

	// Private render variables.
	SDL_Surface* m_Screen;
	TTF_Font* m_Font;
};

typedef MSingleton<MRenderer> Renderer;

#endif // _RENDERER_H_
