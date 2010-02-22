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

#include "ThirdParty.h"
#include "Sprite.h"
#include "Renderer.h"

MSprite::MSprite( void ) :
m_dAngle(0.0),
m_bActive(false),
m_iRotateSteps(0),
m_fDepth(0.0f),
m_iFrame(0),
m_iFrameDelay(0)
{
	m_Coords[0] = 0;
	m_Coords[1] = 0;
	
	printf(" -> MSprite object created (default).\n");
}

MSprite::MSprite( const char *pszFileName, int iRotateSteps, bool bSmooth, float fDepth ) :
m_dAngle(0.0),
m_bActive(true),
m_iRotateSteps(iRotateSteps),
m_fDepth(fDepth),
m_iFrame(0),
m_iFrameDelay(0)
{
	m_Coords[0] = 0;
	m_Coords[1] = 0;

	SDL_Surface* pSurface = NULL;
	if( ( pSurface = SurfFromFile(pszFileName) ) == NULL ) {
		printf(" -! ERROR unable to load image file in MSprite().\n");
		return;
	}

	// Add to the frame list and rendering queue.
	m_FramesCache.push_back(pSurface);
	Renderer::GetInstance()->RegisterDrawable(this);
}

MSprite::MSprite( const char* pszFileName, int iRotateSteps, bool bSmooth, 
				 int x, int y, int iWidth, int iHeight, int r, int g, int b, float fDepth ) :
m_dAngle(0.0),
m_bActive(true),
m_iRotateSteps(iRotateSteps),
m_fDepth(fDepth),
m_iFrame(0),
m_iFrameDelay(0)
{
	m_Coords[0] = 0;
	m_Coords[1] = 0;
	
	SDL_Surface* pSurface = NULL;
	if( ( pSurface = ClippedSurfFromFile(pszFileName,x,y,iWidth,iHeight,r,g,b) ) == NULL ) {
		printf(" -! ERROR unable to load image file in MSprite().\n");
		return;
	}

	// Add to the frame list and rendering queue.
	m_FramesCache.push_back(pSurface);
	Renderer::GetInstance()->RegisterDrawable(this);
}

MSprite::MSprite( const char* pszXmlFile ) :
m_dAngle(0.0),
m_bActive(true),
m_iRotateSteps(0),
m_fDepth(0.0f),
m_iFrame(0),
m_iFrameDelay(0)
{
	if( !ParseFromXml(pszXmlFile) ) {
		printf(" -! ERROR unable to parse XML file in MSprite().\n");
		return;
	}
	
	Renderer::GetInstance()->RegisterDrawable(this);

	m_FrameTimer.Start();
}

MSprite::~MSprite( void )
{
	Renderer::GetInstance()->RemoveDrawable(this);
	//SDL_FreeSurface(m_Surface);

	// We skip [0] since it points to m_Surface.
	//if( m_iRotateSteps > 0 ) {
	//	for( int i = 0; i < m_iRotateSteps; i++ ) {
	//		SDL_FreeSurface(m_RotSurfaces[i]);
	//	}
	//	delete[] m_RotSurfaces;
	//}
	int iFrames = 0;
	std::vector<SDL_Surface*>::iterator it;
	for( it = m_FramesCache.begin(); it < m_FramesCache.end(); ++it ) {
		if( *it ) {
			SDL_FreeSurface(*it);
			iFrames++;
		}
	}

	printf(" -> MSprite object destructed (%i frames).\n",iFrames);
}

void MSprite::SetPosition( int x, int y )
{
	m_Coords[0] = x;
	m_Coords[1] = y;
}

void MSprite::GetPosition( int& x, int& y )
{
	x = m_Coords[0];
	y = m_Coords[1];
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

void MSprite::SetFrame( int iFrame )
{
	if( iFrame > (GetNumFrames() - 1) ) {
		printf(" -! ERROR specified sprite frame out of bounds in MSprite::SetFrame().\n");
		return;
	}
}

int MSprite::GetFrame( void )
{
	return m_iFrame;
}

int MSprite::GetNumFrames( void )
{
	return (int)m_FramesCache.size();
}

void MSprite::Animate( bool bLoop )
{
	if( m_FrameTimer.GetTicks() > m_iFrameDelay ) {
		if( m_iFrame < ( GetNumFrames() - 1 ) )
			++m_iFrame;
		else m_iFrame = 0;
		m_FrameTimer.Start();
	}
}

SDL_Surface* MSprite::SurfFromFile( const std::string& sFileName )
{
	if( !sFileName.c_str() ) {
		printf(" -! ERROR invalid file name in MSprite::LoadImageFile().\n");
		return NULL;
	}

	SDL_Surface* pTemp = NULL;
	SDL_Surface* pResult = NULL;

	
	if( ( pTemp = IMG_Load(sFileName.c_str()) ) == NULL ) {
		printf(" -! ERROR SDL_LoadBMP() returned a NULL object.\n");
		return false;
	}

	int iColKey = SDL_MapRGB(pTemp->format,0xFF,0,0xFF);
	SDL_SetColorKey(pTemp,SDL_SRCCOLORKEY,iColKey);
	pResult = SDL_DisplayFormat(pTemp);
	SDL_FreeSurface(pTemp);

	/*if( m_iRotateSteps > 0 ) {
		m_RotSurfaces = new SDL_Surface* [m_iRotateSteps];
		m_RotSurfaces[0] = m_Surface;

		for( int i = 1; i < m_iRotateSteps; i++ ) {
			SDL_Surface* rotSurf = rotozoomSurface(m_RotSurfaces[0],(double)i,1.0,0);
			int iColKey = SDL_MapRGB(rotSurf->format,0xFF,0,0xFF);
			SDL_SetColorKey(rotSurf,SDL_SRCCOLORKEY,iColKey);
			m_RotSurfaces[i] = SDL_DisplayFormat(rotSurf);
			SDL_FreeSurface(rotSurf);
		}
	}*/

	return pResult;
}

SDL_Surface* MSprite::ClippedSurfFromFile( const std::string& sFileName, int x, int y, int iWidth, int iHeight, int r, int g, int b )
{
	if( !sFileName.c_str() ) {
		printf(" -! ERROR invalid file name in MSprite::ClippedSurfFromFile().\n");
		return NULL;
	}

	SDL_Surface* pTemp = NULL;
	SDL_Surface* pResult = NULL;
	SDL_Surface* pEmpty = NULL;

	if( ( pTemp = IMG_Load(sFileName.c_str()) ) == NULL ) {
		printf(" -! ERROR SDL_LoadBMP() returned a NULL object.\n");
		return NULL;
	}

	SDL_Rect srcRect = { x, y, iWidth, iHeight };
	SDL_Rect dstRect = { 0, 0, iWidth, iHeight };
	
	// Create an empty surface and blit clipped surface to it.
	pEmpty = SDL_CreateRGBSurface(SDL_SWSURFACE,iWidth,iHeight,32,0,0,0,0);
	SDL_BlitSurface(pTemp,&srcRect,pEmpty,&dstRect);
	SDL_FreeSurface(pTemp);

	// Set the colour key to enable transparency.
	int iColKey = SDL_MapRGB(pEmpty->format,r,g,b);
	SDL_SetColorKey(pEmpty,SDL_SRCCOLORKEY,iColKey);
	pResult = SDL_DisplayFormatAlpha(pEmpty);
	SDL_FreeSurface(pEmpty);

	/*if( m_iRotateSteps > 0 ) {
		m_RotSurfaces = new SDL_Surface* [m_iRotateSteps];
		m_RotSurfaces[0] = m_Surface;

		for( int i = 1; i < m_iRotateSteps; i++ ) {
			SDL_Surface* rotSurf = rotozoomSurface(m_RotSurfaces[0],(double)((360 / m_iRotateSteps) * i),1.0,1);
			int iColKey = SDL_MapRGB(rotSurf->format,0xFF,0,0xFF);
			SDL_SetColorKey(rotSurf,SDL_SRCCOLORKEY,iColKey);
			m_RotSurfaces[i] = SDL_DisplayFormatAlpha(rotSurf);
			SDL_FreeSurface(rotSurf);
		}
	}*/

	return pResult;
}

bool MSprite::ParseFromXml( const char* pszXmlFile )
{
	TiXmlDocument xmlDoc(pszXmlFile);
	TiXmlElement* pRoot = NULL;

	if( !xmlDoc.LoadFile() ) {
		printf(" -! ERROR unable to load XML file in MSprite::ParseFromXml().\n");
		return false;
	}

	else if( ( pRoot = xmlDoc.FirstChildElement("SpriteEntry") ) == NULL ) {
		printf(" -! ERROR invalid XML format in MSprite().\n");
		return false;
	}

	// We do this here because depth is a per-sprite (not frame) attribute
	// and there is little sense in using frames from multiple files.
	m_fDepth = (float)atof(pRoot->Attribute("depth"));
	m_iFrameDelay = atoi(pRoot->Attribute("frameDelay"));
	std::string sFileName = pRoot->Attribute("fileName");
	int r = atoi(pRoot->Attribute("keyR"));
	int g = atoi(pRoot->Attribute("keyG"));
	int b = atoi(pRoot->Attribute("keyB"));

	// Recursively load every sprite frame from the XML file.
	for( TiXmlNode *pNode = pRoot->FirstChild("SpriteFrame"); pNode; 
		pNode = pNode->NextSibling("SpriteFrame") )
	{
		TiXmlElement* pSpriteFrame = NULL;
		if( ( pSpriteFrame = pNode->ToElement() ) == NULL ) {
			printf(" -! ERROR invalid SpriteFrame in MSprite::ParseFromXml().\n");
			return false;
		}

		int x = atoi(pSpriteFrame->Attribute("clipX"));
		int y = atoi(pSpriteFrame->Attribute("clipY"));
		int w = atoi(pSpriteFrame->Attribute("clipW"));
		int h = atoi(pSpriteFrame->Attribute("clipH"));

		SDL_Surface* pSurface = NULL;
		if( ( pSurface = ClippedSurfFromFile(sFileName,x,y,w,h,r,g,b) ) == NULL ) {
			printf(" -! ERROR unable to load sprite file in MSprite::ParseFromXml().\n");
			return false;
		}

		m_FramesCache.push_back(pSurface);
	}

	xmlDoc.Clear();
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

int MSprite::GetWidth( void )
{
	return m_FramesCache[m_iFrame]->w;
}

int MSprite::GetHeight( void )
{
	return m_FramesCache[m_iFrame]->w;
}

void* MSprite::GetSurface( void )
{
	return (void*)m_FramesCache[m_iFrame];
}

void MSprite::Render( void* pSurface )
{
	// Scale to give impression of rotation around the center.
	SDL_Rect Rect;
	Rect.x = m_iRotateSteps > 0 ? m_Coords[0] - (m_RotSurfaces[(int)m_dAngle]->w / 2) : m_Coords[0];
	Rect.y = m_iRotateSteps > 0 ? m_Coords[1] - (m_RotSurfaces[(int)m_dAngle]->h / 2) : m_Coords[1];

	/*if( m_iRotateSteps == 0 )*/ 
	SDL_BlitSurface(m_FramesCache[m_iFrame],NULL,(SDL_Surface*)pSurface,&Rect);
	//else SDL_BlitSurface(m_RotSurfaces[(int)m_dAngle],NULL,(SDL_Surface*)pSurface,&Rect);
}