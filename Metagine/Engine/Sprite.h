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

#include "GlobalIncludes.h"
#include "../Includes/SDL/SDL.h"
#include "../Interfaces/ISprite.h"

class MSprite : public ISprite
{
public:

	/// Default constructor (takes no arguments).
	MSprite( void );

	MSprite( const char* pszFileName, bool bRotate, bool bSmooth );

	MSprite( const char* pszFileName, bool bRotate, bool bSmooth, int x, int y, int iWidth, int iHeight );

	/// Destructor method.
	~MSprite( void );

	// Documented in ISprite.h
	bool LoadImageFile( const std::string& sFileName );
	bool LoadImageFileClipped( const std::string& sFileName, int x, int y, int iWidth, int iHeight );
	void SetPosition( int x, int y );
	void SetRotation( int iAngle );

	bool GetActive( void );

	// Render the drawable object.
	virtual void Render( void* pSurface );

private:

	SDL_Surface* m_Surface;
	SDL_Surface** m_RotSurfaces;
	int m_Coords[2];
	int m_iAngle;
	bool m_bActive;
	bool m_bRotatable;
};

#endif // _SPRITE_H_
