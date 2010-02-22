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

#include "ThirdParty.h"
#include "../Public/Public.h"
#include "../Public/BaseTypes.h"

class MSprite : public ISprite
{
public:

	/// Default constructor (takes no arguments).
	MSprite( void );
	MSprite( const char* pszFileName, int iRotateSteps, bool bSmooth, float fDepth );
	MSprite( const char* pszFileName, int iRotateSteps, bool bSmooth, int x, int y, int iWidth, int iHeight, int r, int g, int b, float fDepth );
	MSprite( const char* pszXmlFile );

	/// Destructor method.
	~MSprite( void );
	
	// Documented in ISprite.h
	void SetPosition( int x, int y );
	void GetPosition( int& x, int& y );
	void SetRotation( double iAngle );
	void SetFrame( int iFrame );
	int GetFrame( void );
	int GetNumFrames( void );
	void Animate( bool bLoop );
	int GetWidth( void );
	int GetHeight( void );
	void* GetSurface( void );

	// Documented in IDrawable.h
	bool GetActive( void );
	float GetDepth( void );
	virtual void Render( void* pSurface );

private:

	SDL_Surface* SurfFromFile( const std::string& sFileName );
	SDL_Surface* ClippedSurfFromFile( const std::string& sFileName, int x, int y, int iWidth, int iHeight, int r, int g, int b );
	bool ParseFromXml( const char* pszXmlFile );

private:

	SDL_Surface** m_RotSurfaces;
	std::vector<SDL_Surface*> m_FramesCache;
	MTimer m_FrameTimer;
	int m_iFrame;
	int m_iFrameDelay;
	int m_Coords[2];
	double m_dAngle;
	bool m_bActive;
	int m_iRotateSteps;
	float m_fDepth;
};

#endif // _SPRITE_H_
