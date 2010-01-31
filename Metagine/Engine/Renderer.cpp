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

#include <stdio.h>
#include "Renderer.h"

MRenderer::MRenderer( void )
{
    printf(" -> MRenderer object created.\n");

	m_Screen = NULL;
	m_bFontLibLoaded = false;
}

MRenderer::~MRenderer( void )
{
    printf(" -> MRenderer object destructed.\n");
}

bool MRenderer::Init( void )
{
	printf(" -> Initialising SDL subsystem.\n");

	if( SDL_Init(SDL_INIT_EVERYTHING) == -1 ) {
		printf(" -! ERROR initialising SDL.\n");
		return false;
	} else if( ( m_Screen = SDL_SetVideoMode(640,480,32,SDL_SWSURFACE) ) == NULL ) {
		printf(" -! ERROR setting SDL video mode.\n");
		return false;
	} else if( TTF_Init() == -1 ) {
		printf(" -! ERROR initialising SDL_TTF subsystem.\n");
		m_bFontLibLoaded = false;
		return false;
	} else {
		m_bFontLibLoaded = true;
	}

	// Set the window caption.
	SDL_WM_SetCaption("Metagine",NULL); 
	
	return true;
}

void MRenderer::Shutdown( void )
{
	printf(" -> MRenderer::Shutdown() called.\n");
	
	// Do some housekeeping.
	SDL_Quit();
	TTF_Quit();
}

bool MRenderer::FontLibLoaded( void )
{
	return m_bFontLibLoaded;
}

void MRenderer::RegisterDrawable( IDrawable* pDrawable )
{
	if( !pDrawable ) {
		// Error msg here
		return;
	}

	m_RenderQueue.push_back(pDrawable);
	printf(" -> Registered object (0x%X) with rendering queue.\n",pDrawable);
}

void MRenderer::RemoveDrawable( IDrawable* pDrawable )
{
	/*std::vector<IDrawable*>::iterator it;
	for( it = m_RenderQueue.begin(); it < m_RenderQueue.end(); it++ ) {
		if( (*it) == pDrawable ) {
			printf(" -> Removing object (0x%X) from rendering queue.\n",pDrawable);
			it = m_RenderQueue.erase(it);
		}
	}*/

	std::vector<IDrawable*>::iterator it = m_RenderQueue.begin();
	while( it != m_RenderQueue.end() ) {
		if( *it == pDrawable )
			it = m_RenderQueue.erase(it);
		else ++it;
	}
}

void MRenderer::Frame( void )
{
	SDL_FillRect(m_Screen,&m_Screen->clip_rect,SDL_MapRGB(m_Screen->format,0,0,0));
	
	// Render all queued objects.
	std::vector<IDrawable*>::iterator it;
	for( it = m_RenderQueue.begin(); it < m_RenderQueue.end(); it++ )
		if( (*it)->GetActive() )
			(*it)->Render((void*)m_Screen);

	SDL_Flip(m_Screen);
}
