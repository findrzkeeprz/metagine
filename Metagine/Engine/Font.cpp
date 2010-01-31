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

#include "Font.h"
#include "Renderer.h"

MFont::MFont( void )
{
	printf(" -> MFont object created (default).\n");

	m_Surface = NULL;
	m_Font = NULL;
	m_Colour.r = 0;
	m_Colour.g = 0;
	m_Colour.b = 0;
	m_Coords[0] = 0;
	m_Coords[1] = 0;
	m_bActive = false;
}

MFont::MFont( const char *pszName, int iSize, int iRed, int iGreen, int iBlue )
{
	printf(" -> MFont object created (%s,%i,%i,%i,%i).\n",
			pszName,iSize,iRed,iGreen,iBlue);

	if( !Renderer::GetInstance()->FontLibLoaded() ) {
	    printf(" -! ERROR trying to load font object before initializing library!\n");
	    return;
	}

	if( ( m_Font = TTF_OpenFont(pszName,iSize) ) == NULL ) {
		printf(" -! ERROR loading game font: %s.\n",TTF_GetError());
		return;
	}

	m_Colour.r = iRed;
	m_Colour.g = iGreen;
	m_Colour.b = iBlue;
	m_Coords[0] = 0;
	m_Coords[1] = 0;
	m_bActive = false;
	m_Surface = NULL;

	// Push back to the renderer queue.
	Renderer::GetInstance()->RegisterDrawable(this);
}

MFont::~MFont( void )
{
	Renderer::GetInstance()->RemoveDrawable(this);
    
	if( m_Surface ) {
		SDL_FreeSurface(m_Surface);
		m_Surface = NULL;
	}
	if( m_Font ) {
		TTF_CloseFont(m_Font);
		m_Font = NULL;
	}

    printf(" -> MFont object destructed.\n");
}

void MFont::SetColour( int iRed, int iGreen, int iBlue )
{
	m_Colour.r = iRed;
	m_Colour.g = iGreen;
	m_Colour.b = iBlue;
}

void MFont::SetText( std::string& sMsg )
{
	if( !sMsg.c_str() ) {
		printf(" -! ERROR invalid message string in MFont::SetText().\n");
		return;
	} else if( !m_Font ) {
		printf(" -! ERROR attempting to set font text without valid surface object.\n");
		return;
	}

	if( m_Surface )
		SDL_FreeSurface(m_Surface);

	m_Surface = TTF_RenderText_Solid(m_Font,sMsg.c_str(),m_Colour);
	//m_bActive = true;
}

void MFont::SetPosition( int x, int y )
{
	m_Coords[0] = x;
	m_Coords[1] = y;
}

bool MFont::GetActive( void )
{
	return m_bActive;
}

void MFont::Render( void* pSurface )
{
	SDL_Rect Rect;
	Rect.x = m_Coords[0];
	Rect.y = m_Coords[1];

	SDL_BlitSurface(m_Surface,NULL,(SDL_Surface*)pSurface,&Rect);
}