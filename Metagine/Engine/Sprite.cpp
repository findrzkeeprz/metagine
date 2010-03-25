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
#include "RenderTask.h"
#include "Engine.h"

MSprite::MSprite( MEngine* pEngine ) :
m_pEngine(pEngine),
m_bActive(false),
m_fDepth(0.0f),
m_iFrame(0),
m_iFrameDelay(0)
{
	m_fCoords[0] = 0;
	m_fCoords[1] = 0;
	
	printf(" -> MSprite object created (default).\n");
}

MSprite::MSprite( MEngine* pEngine, const char *pszFileName, int iWidth, int iHeight, float fDepth ) :
m_pEngine(pEngine),
m_bActive(true),
m_fDepth(fDepth),
m_iFrame(0),
m_iFrameDelay(0)
{
	m_fCoords[0] = 0;
	m_fCoords[1] = 0;

	unsigned int pSurface = NULL;
	if( ( pSurface = m_pEngine->SurfaceCache()->SurfFromFile(pszFileName) ) == 0 ) {
		printf(" -! ERROR unable to load image file in MSprite().\n");
		return;
	}

	// Add to the frame list and rendering queue.
	MTexture_t texture;
	texture.iTexture = pSurface;
	texture.iWidth = iWidth;
	texture.iHeight = iHeight;
	m_FramesCache.push_back(texture);
	//Engine::GetInstance()->Renderer()->RegisterDrawable(shared_from_this());
}

MSprite::MSprite( MEngine* pEngine, const char* pszFileName, int x, int y, int iWidth, int iHeight, int r, int g, int b, float fDepth ) :
m_pEngine(pEngine),
m_bActive(true),
m_fDepth(fDepth),
m_iFrame(0),
m_iFrameDelay(0)
{
	m_fCoords[0] = 0;
	m_fCoords[1] = 0;
	
	unsigned int pSurface = NULL;
	string sFileFrame = pszFileName;
	sFileFrame.append((boost::format("+%1%,%2%,%3%,%4%") % x % y % iWidth % iHeight).str());
	if( ( pSurface = m_pEngine->SurfaceCache()->ClippedSurfFromFile(sFileFrame,x,y,iWidth,iHeight,r,g,b) ) == 0 ) {
		printf(" -! ERROR unable to load image file in MSprite().\n");
		return;
	}

	// Add to the frame list and rendering queue.
	MTexture_t texture;
	texture.iTexture = pSurface;
	texture.iWidth = iWidth;
	texture.iHeight = iHeight;
	m_FramesCache.push_back(texture);
	//Engine::GetInstance()->Renderer()->RegisterDrawable(shared_from_this());
}

MSprite::MSprite( MEngine* pEngine, const char* pszXmlFile ) :
m_pEngine(pEngine),
m_bActive(true),
m_fDepth(0.0f),
m_iFrame(0),
m_iFrameDelay(0)
{
	if( !ParseFromXml(pszXmlFile) ) {
		printf(" -! ERROR unable to parse XML file in MSprite().\n");
		return;
	}
	
	//Engine::GetInstance()->Renderer()->RegisterDrawable(shared_from_this());

	m_FrameTimer.Start();
}

MSprite::~MSprite( void )
{
	m_FramesCache.clear();

	printf(" -> MSprite object destructed.\n");
}

void MSprite::SetPosition( const float x, const float y )
{
	m_fCoords[0] = x;
	m_fCoords[1] = y;
}

const float MSprite::GetPositionX( void ) const
{
	return m_fCoords[0];
}

const float MSprite::GetPositionY( void ) const
{
	return m_fCoords[1];
}

void MSprite::SetRotation( double iAngle )
{
}

void MSprite::SetFrame( const int iFrame )
{
	if( iFrame > (GetNumFrames() - 1) ) {
		printf(" -! ERROR specified sprite frame out of bounds in MSprite::SetFrame().\n");
		return;
	}
}

const int MSprite::GetFrame( void ) const
{
	return m_iFrame;
}

const int MSprite::GetNumFrames( void ) const
{
	return (int)m_FramesCache.size();
}

const bool MSprite::Animate( const bool bLoop )
{
	bool bResult = true;
	
	if( m_FrameTimer.GetTicks() > m_iFrameDelay ) {
		if( m_iFrame < ( GetNumFrames() - 1 ) ) {
			++m_iFrame;
			bResult = true;
		} else {
			if( bLoop ) m_iFrame = 0;
			bResult = false;
		}
		
		m_FrameTimer.Start();
	}
	
	return bResult;
}

void MSprite::AnimateCycle( void )
{
	static bool bReverse = false;
	
	if( m_FrameTimer.GetTicks() > m_iFrameDelay ) {
		if( !bReverse ) {
			if( m_iFrame < ( GetNumFrames() - 1 ) )
				++m_iFrame;
			else bReverse = true;
		} else {
			if( m_iFrame > 0 )
				--m_iFrame;
			else bReverse = false;
		}

		m_FrameTimer.Start();
	}
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
	pRoot->QueryFloatAttribute("depth",&m_fDepth);
	m_iFrameDelay = atoi(pRoot->Attribute("frameDelay"));
	string sFileName = pRoot->Attribute("fileName");
	int r = atoi(pRoot->Attribute("keyR"));
	int g = atoi(pRoot->Attribute("keyG"));
	int b = atoi(pRoot->Attribute("keyB"));

	int iCount = 0;

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

		// Load into/retrieve from cache with "File+x,y,w,h" format.
		string sFileFrame = sFileName;
		sFileFrame.append((boost::format("+%1%,%2%,%3%,%4%") % x % y % w % h).str());

		unsigned int pSurface = NULL;
		if( ( pSurface = m_pEngine->SurfaceCache()->ClippedSurfFromFile(sFileFrame,x,y,w,h,r,g,b) ) == 0 ) {
			printf(" -! ERROR unable to load sprite file in MSprite::ParseFromXml().\n");
			return false;
		}

		MTexture_t texture;
		texture.iTexture = pSurface;
		texture.iWidth = w;
		texture.iHeight = h;
		m_FramesCache.push_back(texture);
		iCount++;
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

const int MSprite::GetWidth( void ) const
{
	return m_FramesCache[m_iFrame].iWidth;
}

const int MSprite::GetHeight( void ) const
{
	return m_FramesCache[m_iFrame].iHeight;
}

unsigned int MSprite::GetSurface( void )
{
	return m_FramesCache[m_iFrame].iTexture;
}

void MSprite::Render( void )
{
	glPushMatrix();
	glTranslatef((float)MMath::Round(m_fCoords[0]),
		(float)MMath::Round(m_fCoords[1]),m_fDepth);
	glBindTexture(GL_TEXTURE_2D,m_FramesCache[m_iFrame].iTexture);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_QUADS);
		glTexCoord2i(0,1);
		glVertex2i(0,0);
		glTexCoord2i(1,1);
		glVertex2i(m_FramesCache[m_iFrame].iWidth,0);
		glTexCoord2i(1,0);
		glVertex2i(m_FramesCache[m_iFrame].iWidth,m_FramesCache[m_iFrame].iHeight);
		glTexCoord2i(0,0);
		glVertex2i(0,m_FramesCache[m_iFrame].iHeight);
	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
}