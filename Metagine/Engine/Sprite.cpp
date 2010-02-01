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

#include "Sprite.h"
#include "Renderer.h"

MSprite::MSprite( void )
{
	printf(" -> MSprite object created (default).\n");

	m_Surface = NULL;
	m_Coords[0] = 0;
	m_Coords[1] = 0;
	m_bActive = false;
}

MSprite::MSprite( const char *pszFileName )
{
	m_Coords[0] = 0;
	m_Coords[1] = 0;
	m_bActive = true;

	if( !this->LoadImageFile(pszFileName)) {
		printf(" -! ERROR unable to load image file in MSprite().\n");
		return;
	}

	// Push back to the renderer queue.
	Renderer::GetInstance()->RegisterDrawable(this);
}

MSprite::~MSprite( void )
{
	Renderer::GetInstance()->RemoveDrawable(this);
	SDL_FreeSurface(m_Surface);

	printf(" -> MSprite object destructed.\n");
}

void MSprite::SetPosition( int x, int y )
{
	m_Coords[0] = x;
	m_Coords[1] = y;
}

bool MSprite::LoadImageFile( const std::string& sFileName )
{
	if( !sFileName.c_str() ) {
		printf(" -! ERROR invalid file name in MSprite::LoadImageFile().\n");
		return false;
	}

	SDL_Surface* TempSurf = NULL;
	TempSurf = SDL_LoadBMP(sFileName.c_str());
	/*if( ( TempSurf = SDL_LoadBMP(pszFileName) ) == NULL ) {
		printf(" -! ERROR SDL_LoadBMP() returned a NULL object.\n");
		return false;
	}*/

	m_Surface = SDL_DisplayFormat(TempSurf);
	SDL_FreeSurface(TempSurf);

	return true;
}

bool MSprite::GetActive( void )
{
	return m_bActive;
}

void MSprite::Render( void* pSurface )
{
	SDL_Rect Rect;
	Rect.x = m_Coords[0];
	Rect.y = m_Coords[1];

	SDL_BlitSurface(m_Surface,NULL,(SDL_Surface*)pSurface,&Rect);
}
