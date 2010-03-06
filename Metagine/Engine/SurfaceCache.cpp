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

#include "SurfaceCache.h"
	
MSurfaceCache::MSurfaceCache( void )
{
}

MSurfaceCache::~MSurfaceCache( void )
{
	map<string,unsigned int>::iterator it = m_Surfaces.begin();
	for( it = m_Surfaces.begin(); it != m_Surfaces.end(); ++it ) {
		glDeleteTextures(1,&it->second);
	}

	m_Surfaces.clear();
}

unsigned int MSurfaceCache::SurfFromFile( string sFileName )
{
	if( !sFileName.c_str() ) {
		printf(" -! ERROR invalid file name in MSprite::LoadImageFile().\n");
		return NULL;
	}

	map<string,unsigned int>::iterator it = m_Surfaces.find(sFileName);
	if( it == m_Surfaces.end() ) {
		
		printf(" -> Allocating surface: %s in MSurfaceCache::SurfFromFile().\n",sFileName.c_str());
		
		SDL_Surface* pTemp[2];
		unsigned int iTexture = 0;
	
		if( ( pTemp[0] = IMG_Load(sFileName.c_str()) ) == NULL ) {
			printf(" -! ERROR IMG_LoadBMP() returned a NULL object.\n");
			return false;
		}

		int iColKey = SDL_MapRGB(pTemp[0]->format,0xFF,0,0xFF);
		SDL_SetColorKey(pTemp[0],SDL_SRCCOLORKEY,iColKey);
		pTemp[1] = SDL_DisplayFormat(pTemp[0]);

		glGenTextures(1,&iTexture);
		glBindTexture(GL_TEXTURE_2D,iTexture);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D,0,pTemp[1]->format->BytesPerPixel, pTemp[1]->w, pTemp[1]->h, 0,
                      GL_BGRA,GL_UNSIGNED_BYTE,pTemp[1]->pixels);

		for( int i = 0; i < 2; i++ ) if( pTemp[i] ) { SDL_FreeSurface(pTemp[i]); pTemp[i] = NULL; }
		m_Surfaces.insert(make_pair(sFileName,iTexture));
		
		return iTexture;
	}
	
	return it->second;
}

unsigned int MSurfaceCache::ClippedSurfFromFile( string sFileName, int x, int y, int iWidth, int iHeight, int r, int g, int b )
{
	
	size_t split;
	string sName = sFileName;

	if( !sFileName.c_str() ) {
		printf(" -! ERROR invalid file name in MSprite::ClippedSurfFromFile().\n");
		return NULL;
	} else if( ( split = sName.find_first_of("+") ) != string::npos ) {
		// Trim anything past the + character.
		sName = sName.erase(split);
	} else sName = sFileName;

	map<string,unsigned int>::iterator it = m_Surfaces.find(sFileName);
	if( it == m_Surfaces.end() ) {
		printf(" -> Allocating surface: %s in MSurfaceCache::ClippedSurfFromFile().\n",sFileName.c_str());
		
		SDL_Surface* pTemp[3];
		unsigned int iTexture = 0;

		if( ( pTemp[0] = IMG_Load(sName.c_str()) ) == NULL ) {
			printf(" -! ERROR IMG_Load() returned a NULL object.\n");
			return NULL;
		}

		SDL_Rect srcRect = { x, y, iWidth, iHeight };
		SDL_Rect dstRect = { 0, 0, iWidth, iHeight };

		// Create an empty surface and blit clipped surface to it.
		pTemp[2] = SDL_CreateRGBSurface(SDL_SWSURFACE,iWidth,iHeight,32,0,0,0,0);
		SDL_BlitSurface(pTemp[0],&srcRect,pTemp[2],&dstRect);

		// Set the colour key to enable transparency.
		int iColKey = SDL_MapRGB(pTemp[2]->format,r,g,b);
		SDL_SetColorKey(pTemp[2],SDL_SRCCOLORKEY,iColKey);
		pTemp[1] = SDL_DisplayFormatAlpha(pTemp[2]);

		glGenTextures(1,&iTexture);
		glBindTexture(GL_TEXTURE_2D,iTexture);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D,0,pTemp[1]->format->BytesPerPixel, pTemp[1]->w, pTemp[1]->h, 0,
                      GL_BGRA,GL_UNSIGNED_BYTE,pTemp[1]->pixels);

		for( int i = 0; i < 3; i++ ) if( pTemp[i] ) { SDL_FreeSurface(pTemp[i]); pTemp[i] = NULL; }
		m_Surfaces.insert(make_pair(sFileName,iTexture));
		
		return iTexture;
	}

	return it->second;
}