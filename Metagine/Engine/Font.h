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

#ifndef _FONT_H_
#define _FONT_H_

#include "ThirdParty.h"
#include "../Public/Public.h"
#include "../Public/BaseTypes.h"

class MFont : public IDrawable
{
public:

	/// Default constructor (takes no arguments).
	MFont( void );

	MFont( const char* pszName, int iSize, int iRed, int iGreen, int iBlue, float fDepth );

	/// Destructor method.
	~MFont( void );

	void SetColour( int iRed, int iGreen, int iBlue );
	void SetAlpha( int iAlpha );

	void SetText( string& sMsg );

	virtual void SetPosition( int x, int y );

	void SetActive( bool bActive ) { m_bActive = bActive; }
	bool GetActive( void );
	float GetDepth( void );

	// Render the drawable object.
	virtual void Render( void );

protected:

	// Private font variables.
	SDL_Surface* m_Surface;
	SDL_Color m_Colour;
	TTF_Font* m_Font;
	int m_Coords[2];
	int m_iAlpha;
	bool m_bActive;
	float m_fDepth;
	string m_sLastMsg;
};

#endif // _FONT_H_
