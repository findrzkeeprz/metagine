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

MSprite::MSprite( void ) :
m_Surface(NULL),
m_dAngle(0.0),
m_bActive(false),
m_iRotateSteps(0),
m_fDepth(0.0f)
{
	m_Coords[0] = 0;
	m_Coords[1] = 0;
	
	printf(" -> MSprite object created (default).\n");
}

MSprite::MSprite( const char *pszFileName, int iRotateSteps, bool bSmooth, float fDepth ) :
m_dAngle(0.0),
m_bActive(true),
m_iRotateSteps(iRotateSteps),
m_fDepth(fDepth)
{
	m_Coords[0] = 0;
	m_Coords[1] = 0;

	if( !this->LoadImageFile(pszFileName)) {
		printf(" -! ERROR unable to load image file in MSprite().\n");
		return;
	}

	// Push back to the renderer queue.
	Renderer::GetInstance()->RegisterDrawable(this);
}

MSprite::MSprite( const char* pszFileName, int iRotateSteps, bool bSmooth, int x, int y, int iWidth, int iHeight, float fDepth ) :
m_dAngle(0.0),
m_bActive(true),
m_iRotateSteps(iRotateSteps),
m_fDepth(fDepth)
{
	m_Coords[0] = 0;
	m_Coords[1] = 0;

	if( !this->LoadImageFileClipped(pszFileName,x,y,iWidth,iHeight)) {
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
	if( m_iRotateSteps > 0 ) {
		for( int i = 0; i < m_iRotateSteps; i++ ) {
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

void MSprite::SetRotation( double iAngle )
{
	/*double dFraction = 360.00 / m_iRotateSteps;
	
	
	for( int i = 0; i < m_iRotateSteps; i++ ) {
		if( iAngle > (i * dFraction) && iAngle < (i + 1) * dFraction) {
		//if(isBetween(iAngle,i * dFraction,(i + 1) * dFraction))
			m_iAngle = i;
			return;
		}
	}*/
	m_dAngle = iAngle;
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

	int iColKey = SDL_MapRGB(TempSurf->format,0xFF,0,0xFF);
	SDL_SetColorKey(TempSurf,SDL_SRCCOLORKEY,iColKey);
	m_Surface = SDL_DisplayFormat(TempSurf);
	SDL_FreeSurface(TempSurf);

	if( m_iRotateSteps > 0 ) {
		m_RotSurfaces = new SDL_Surface* [m_iRotateSteps];
		m_RotSurfaces[0] = m_Surface;

		for( int i = 1; i < m_iRotateSteps; i++ ) {
			SDL_Surface* rotSurf = rotozoomSurface(m_RotSurfaces[0],(double)i,1.0,0);
			int iColKey = SDL_MapRGB(rotSurf->format,0xFF,0,0xFF);
			SDL_SetColorKey(rotSurf,SDL_SRCCOLORKEY,iColKey);
			m_RotSurfaces[i] = SDL_DisplayFormat(rotSurf);
			SDL_FreeSurface(rotSurf);
		}
	}

	return true;
}

bool MSprite::LoadImageFileClipped( const std::string& sFileName, int x, int y, int iWidth, int iHeight )
{
	if( !sFileName.c_str() ) {
		printf(" -! ERROR invalid file name in MSprite::LoadImageFileClipped().\n");
		return false;
	}

	SDL_Surface* TempSurf = NULL;
	if( ( TempSurf = SDL_LoadBMP(sFileName.c_str()) ) == NULL ) {
		printf(" -! ERROR SDL_LoadBMP() returned a NULL object.\n");
		return false;
	}

	SDL_Rect srcRect = { x, y, iWidth, iHeight };
	SDL_Rect dstRect = { 0, 0, iWidth, iHeight };
	
	// Create an empty surface and blit clipped surface to it.
	SDL_Surface* NewSurf = SDL_CreateRGBSurface(SDL_SWSURFACE,iWidth,iHeight,32,0,0,0,0);
	SDL_BlitSurface(TempSurf,&srcRect,NewSurf,&dstRect);
	SDL_FreeSurface(TempSurf);

	// Set the colour key to enable transparency.
	int iColKey = SDL_MapRGB(NewSurf->format,0xFF,0,0xFF);
	SDL_SetColorKey(NewSurf,SDL_SRCCOLORKEY,iColKey);
	m_Surface = SDL_DisplayFormatAlpha(NewSurf);
	SDL_FreeSurface(NewSurf);

	if( m_iRotateSteps > 0 ) {
		m_RotSurfaces = new SDL_Surface* [m_iRotateSteps];
		m_RotSurfaces[0] = m_Surface;

		for( int i = 1; i < m_iRotateSteps; i++ ) {
			SDL_Surface* rotSurf = rotozoomSurface(m_RotSurfaces[0],(double)((360 / m_iRotateSteps) * i),1.0,1);
			int iColKey = SDL_MapRGB(rotSurf->format,0xFF,0,0xFF);
			SDL_SetColorKey(rotSurf,SDL_SRCCOLORKEY,iColKey);
			m_RotSurfaces[i] = SDL_DisplayFormatAlpha(rotSurf);
			SDL_FreeSurface(rotSurf);
		}
	}

	return true;
}

bool MSprite::GetActive( void )
{
	return m_bActive;
}

float MSprite::GetDepth( void )
{
	return m_fDepth;
}

void MSprite::Render( void* pSurface )
{
	// Scale to give impression of rotation around the center.
	SDL_Rect Rect;
	Rect.x = m_iRotateSteps > 0 ? m_Coords[0] - (m_RotSurfaces[(int)m_dAngle]->w / 2) : m_Coords[0];
	Rect.y = m_iRotateSteps > 0 ? m_Coords[1] - (m_RotSurfaces[(int)m_dAngle]->h / 2) : m_Coords[1];

	if( m_iRotateSteps == 0 ) SDL_BlitSurface(m_Surface,NULL,(SDL_Surface*)pSurface,&Rect);
	else SDL_BlitSurface(m_RotSurfaces[(int)m_dAngle],NULL,(SDL_Surface*)pSurface,&Rect);
}