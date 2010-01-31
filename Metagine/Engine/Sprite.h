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

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "../Includes/SDL/SDL.h"
#include "../Interfaces/IDrawable.h"

class MSprite : public IDrawable
{
public:

	/// Default constructor (takes no arguments).
	MSprite( void );

	MSprite( const char* pszFileName );

	/// Destructor method.
	~MSprite( void );

	bool LoadImageFile( const char *pszFileName );

	void SetPosition( int x, int y );

	bool GetActive( void );

	// Render the drawable object.
	virtual void Render( void* pSurface );

private:

	SDL_Surface* m_Surface;
	int m_Coords[2];
	bool m_bActive;
};

#endif // _SPRITE_H_
