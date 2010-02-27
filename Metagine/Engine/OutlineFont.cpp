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

#include "OutlineFont.h"
#include "Engine.h"
#include "Renderer.h"

MOutlineFont::MOutlineFont( void ) :
MFont()
{
	m_ColourBG.r = 0;
	m_ColourBG.g = 0;
	m_ColourBG.b = 0;
}

MOutlineFont::MOutlineFont( const char *pszName, int iSize, int iRed, int iGreen, int iBlue, int iStep, float fDepth ) :
MFont(pszName,iSize,iRed,iGreen,iBlue,fDepth),
m_SurfaceBG(NULL),
m_iStep(iStep)
{
}

MOutlineFont::~MOutlineFont( void )
{
	printf(" -> MOutlineFont object destructed.\n");
}

void MOutlineFont::SetColourBG( int iRed, int iGreen, int iBlue )
{
	m_ColourBG.r = iRed;
	m_ColourBG.g = iGreen;
	m_ColourBG.b = iBlue;
}

void MOutlineFont::SetText( const string& sText )
{
	if( !sText.c_str() ) {
		printf(" -! ERROR invalid message string in MOutlineFont::SetText().\n");
		return;
	} else if( !m_Font ) {
		printf(" -! ERROR attempting to set font text without valid surface object in MOutlineFont::SetText().\n");
		return;
	}

	// Quick hack to fix memory leakage.
	if( m_Surface )
		SDL_FreeSurface(m_Surface);
	if( m_SurfaceBG )
		SDL_FreeSurface(m_SurfaceBG);
	
	m_Surface = TTF_RenderText_Blended(m_Font,sText.c_str(),m_Colour);
	m_SurfaceBG = TTF_RenderText_Blended(m_Font,sText.c_str(),m_ColourBG);
}

void MOutlineFont::Render( void* pSurface )
{
	if( !m_Surface || !m_SurfaceBG ) {
		printf(" -! ERROR invalid surfaces in MOutlineFont::Render().\n");
		return;
	}
	
	SDL_Rect Rect;
	SDL_Rect RectBG;

	Rect.x = m_Coords[0];
	Rect.y = m_Coords[1];
	SDL_SetAlpha(m_SurfaceBG,SDL_RLEACCEL|SDL_SRCALPHA,m_iAlpha);
	SDL_SetAlpha(m_Surface,SDL_RLEACCEL|SDL_SRCALPHA,m_iAlpha);

	// o o o
	// x o o
	// o o o
	RectBG.x = m_Coords[0] - m_iStep;
	RectBG.y = m_Coords[1];
	SDL_BlitSurface(m_SurfaceBG,NULL,(SDL_Surface*)pSurface,&RectBG);
	
	// o o o
	// o o x
	// o o o
	RectBG.x = m_Coords[0] + m_iStep;
	RectBG.y = m_Coords[1];
	SDL_BlitSurface(m_SurfaceBG,NULL,(SDL_Surface*)pSurface,&RectBG);
	
	// o x o
	// o o o
	// o o o
	RectBG.x = m_Coords[0];
	RectBG.y = m_Coords[1] - m_iStep;
	SDL_BlitSurface(m_SurfaceBG,NULL,(SDL_Surface*)pSurface,&RectBG);
	
	// o o o
	// o o o
	// o x o
	RectBG.x = m_Coords[0];
	RectBG.y = m_Coords[1] + m_iStep;
	SDL_BlitSurface(m_SurfaceBG,NULL,(SDL_Surface*)pSurface,&RectBG);

	// x o o
	// o o o
	// o o o
	RectBG.x = m_Coords[0] - m_iStep;
	RectBG.y = m_Coords[1] - m_iStep;
	SDL_BlitSurface(m_SurfaceBG,NULL,(SDL_Surface*)pSurface,&RectBG);

	// o o x
	// o o o
	// o o o
	RectBG.x = m_Coords[0] + m_iStep;
	RectBG.y = m_Coords[1] - m_iStep;
	SDL_BlitSurface(m_SurfaceBG,NULL,(SDL_Surface*)pSurface,&RectBG);

	// o o o
	// o o o
	// o o x
	RectBG.x = m_Coords[0] + m_iStep;
	RectBG.y = m_Coords[1] + m_iStep;
	SDL_BlitSurface(m_SurfaceBG,NULL,(SDL_Surface*)pSurface,&RectBG);

	// o o o
	// o o o
	// x o o
	RectBG.x = m_Coords[0] - m_iStep;
	RectBG.y = m_Coords[1] + m_iStep;
	SDL_BlitSurface(m_SurfaceBG,NULL,(SDL_Surface*)pSurface,&RectBG);
	
	// o o o
	// o x o
	// o o o
	SDL_BlitSurface(m_Surface,NULL,(SDL_Surface*)pSurface,&Rect);
}
