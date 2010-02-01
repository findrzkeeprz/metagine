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
#include "Renderer.h"

MOutlineFont::MOutlineFont( void ) :
MFont()
{
	m_ColourBG.r = 0;
	m_ColourBG.g = 0;
	m_ColourBG.b = 0;
}

MOutlineFont::MOutlineFont( const char *pszName, int iSize, int iRed, int iGreen, int iBlue ) :
MFont(pszName,iSize,iRed,iGreen,iBlue),
m_SurfaceBG(NULL)
{
}

MOutlineFont::~MOutlineFont( void )
{
	Renderer::GetInstance()->RemoveDrawable(this);

	printf(" -> MOutlineFont object destructed.\n");
}

void MOutlineFont::SetColourBG( int iRed, int iGreen, int iBlue )
{
	m_ColourBG.r = iRed;
	m_ColourBG.g = iGreen;
	m_ColourBG.b = iBlue;
}

void MOutlineFont::SetText( const std::string& sText )
{
	if( !sText.c_str() ) {
		printf(" -! ERROR invalid message string in MOutlineFont::SetText().\n");
		return;
	} else if( !m_Font ) {
		printf(" -! ERROR attempting to set font text without valid surface object in MOutlineFont::SetText().\n");
		return;
	}

	m_Surface = TTF_RenderText_Solid(m_Font,sText.c_str(),m_Colour);
	m_SurfaceBG = TTF_RenderText_Solid(m_Font,sText.c_str(),m_ColourBG);
	//m_bActive = true;
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

	// Create the outline effect.
	RectBG.x = m_Coords[0] - 2;
	RectBG.y = m_Coords[1];
	SDL_BlitSurface(m_SurfaceBG,NULL,(SDL_Surface*)pSurface,&RectBG);
	RectBG.x = m_Coords[0] + 2;
	RectBG.y = m_Coords[1];
	SDL_BlitSurface(m_SurfaceBG,NULL,(SDL_Surface*)pSurface,&RectBG);
	RectBG.x = m_Coords[0];
	RectBG.y = m_Coords[1] - 2;
	SDL_BlitSurface(m_SurfaceBG,NULL,(SDL_Surface*)pSurface,&RectBG);
	RectBG.x = m_Coords[0];
	RectBG.y = m_Coords[1] + 2;

	SDL_BlitSurface(m_SurfaceBG,NULL,(SDL_Surface*)pSurface,&RectBG);
	SDL_BlitSurface(m_Surface,NULL,(SDL_Surface*)pSurface,&Rect);
}
