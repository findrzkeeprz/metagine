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

#ifndef _OUTLINEFONT_H_
#define _OUTLINEFONT_H_

#include "Font.h"

class MOutlineFont : public MFont
{
public:

	/// Default constructor (takes no arguments).
	MOutlineFont( void );

	MOutlineFont( const char* pszName, int iSize, int iRed, int iGreen, int iBlue, float fDepth );

	/// Destructor method.
	~MOutlineFont( void );

	void SetColourBG( int iRed, int iGreen, int iBlue );

	void SetText( const std::string& sText );

	// Render the drawable object.
	void Render( void* pSurface );

private:

	// Private outline font variables.
	SDL_Color m_ColourBG;
	SDL_Surface* m_SurfaceBG;
};

#endif // _OUTLINEFONT_H_
