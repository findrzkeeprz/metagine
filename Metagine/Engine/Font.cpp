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
#include "Engine.h"
#include "RenderTask.h"

MFont::MFont( void ) :
m_Surface(NULL),
m_Font(NULL),
m_bActive(false),
m_fDepth(0.0f),
m_iAlpha(255)
{
	printf(" -> MFont object created (default).\n");

	m_Colour.r = 0;
	m_Colour.g = 0;
	m_Colour.b = 0;
	m_Coords[0] = 0;
	m_Coords[1] = 0;
}

MFont::MFont( const char *pszName, int iSize, int iRed, int iGreen, int iBlue, float fDepth ) :
m_Surface(NULL),
m_Font(NULL),
m_bActive(false),
m_fDepth(fDepth),
m_iAlpha(255)
{
	printf(" -> MFont object created (%s,%i,%i,%i,%i).\n",
			pszName,iSize,iRed,iGreen,iBlue);

	if( !Engine::GetInstance()->Renderer()->FontLibLoaded() ) {
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

	// Push back to the renderer queue.
	//Engine::GetInstance()->Renderer()->RegisterDrawable(shared_from_this());
}

MFont::~MFont( void )
{
	//Engine::GetInstance()->Renderer()->RemoveDrawable(shared_from_this());
    
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

void MFont::SetAlpha( int iAlpha )
{
	m_iAlpha = iAlpha;
}

void MFont::SetText( string& sMsg )
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

	m_Surface = TTF_RenderText_Blended(m_Font,sMsg.c_str(),m_Colour);
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

float MFont::GetDepth( void )
{
	return m_fDepth;
}

void MFont::Render( void* pSurface )
{
	if( !m_Surface ) {
		printf(" -! ERROR invalid surface in MFont::Render().\n");
		return;
	}
	
	SDL_Rect Rect;
	Rect.x = m_Coords[0];
	Rect.y = m_Coords[1];

	SDL_SetAlpha(m_Surface,SDL_RLEACCEL|SDL_SRCALPHA,m_iAlpha);
	SDL_BlitSurface(m_Surface,NULL,(SDL_Surface*)pSurface,&Rect);
}
