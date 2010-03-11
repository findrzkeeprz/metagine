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

typedef struct MTexture_s
{
	unsigned int iTexture;
	int iWidth;
	int iHeight;
} MTexture_t;

class MSprite : public ISprite
{
public:

	/// Default constructor (takes no arguments).
	MSprite( void );
	MSprite( const char* pszFileName, int iWidth, int iHeight, float fDepth );
	MSprite( const char* pszFileName, int x, int y, int iWidth, int iHeight, int r, int g, int b, float fDepth );
	MSprite( const char* pszXmlFile );

	/// Destructor method.
	~MSprite( void );
	
	// Documented in ISprite.h
	void SetPosition( const float x, const float y );
	const float GetPositionX( void ) const;
	const float GetPositionY( void ) const;
	void SetRotation( double iAngle );
	void SetFrame( const int iFrame );
	const int GetFrame( void ) const;
	const int GetNumFrames( void ) const;
	const bool Animate( const bool bLoop );
	const int GetWidth( void ) const;
	const int GetHeight( void ) const;
	unsigned int GetSurface( void );

	// Documented in IDrawable.h
	bool GetActive( void );
	float GetDepth( void );
	virtual void Render( void );

private:

	bool ParseFromXml( const char* pszXmlFile );

private:

	vector<MTexture_t> m_FramesCache;
	MTimer m_FrameTimer;
	int m_iFrame;
	int m_iFrameDelay;
	float m_fCoords[2];
	bool m_bActive;
	float m_fDepth;
};

#endif // _SPRITE_H_
