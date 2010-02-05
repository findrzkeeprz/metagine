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
	m_iAngle = 0;
	m_bActive = false;
	m_bRotatable = false;
}

MSprite::MSprite( const char *pszFileName, bool bRotate, bool bSmooth )
{
	m_Coords[0] = 0;
	m_Coords[1] = 0;
	m_iAngle = 0;
	m_bActive = true;
	m_bRotatable = true;

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

	// We skip [0] since it points to m_Surface.
	if( m_bRotatable ) {
		for( int i = 1; i < 359; i++ ) {
			SDL_FreeSurface(m_RotSurfaces[i]);
		}
		delete[] m_RotSurfaces;
	}

	printf(" -> MSprite object destructed.\n");
}

void MSprite::SetPosition( int x, int y )
{
	m_Coords[0] = x;
	m_Coords[1] = y;
}

void MSprite::SetRotation( int iAngle )
{
	m_iAngle = iAngle;
}

bool MSprite::LoadImageFile( const std::string& sFileName )
{
	if( !sFileName.c_str() ) {
		printf(" -! ERROR invalid file name in MSprite::LoadImageFile().\n");
		return false;
	}

	SDL_Surface* TempSurf = NULL;
	if( ( TempSurf = SDL_LoadBMP(sFileName.c_str()) ) == NULL ) {
		printf(" -! ERROR SDL_LoadBMP() returned a NULL object.\n");
		return false;
	}

	m_Surface = SDL_DisplayFormat(TempSurf);
	SDL_FreeSurface(TempSurf);

	if( m_bRotatable ) {
		m_RotSurfaces = new SDL_Surface* [360];
		m_RotSurfaces[0] = m_Surface;

		for( int i = 1; i < 360; i++ ) {
			m_RotSurfaces[i] = rotozoomSurface(m_RotSurfaces[0],(double)i,1.0,0);
		}
	}

	return true;
}

bool MSprite::GetActive( void )
{
	return m_bActive;
}

void MSprite::Render( void* pSurface )
{
	SDL_Rect Rect;
	
	// Scale to give impression of rotation around the center.
	Rect.x = m_bRotatable? m_Coords[0] - (m_RotSurfaces[m_iAngle]->w / 2): m_Coords[0];
	Rect.y = m_bRotatable? m_Coords[1] - (m_RotSurfaces[m_iAngle]->h / 2): m_Coords[1];

	if( !m_bRotatable ) SDL_BlitSurface(m_Surface,NULL,(SDL_Surface*)pSurface,&Rect);
	else SDL_BlitSurface(m_RotSurfaces[m_iAngle],NULL,(SDL_Surface*)pSurface,&Rect);
}
