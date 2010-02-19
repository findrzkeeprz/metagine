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

#include "Renderer.h"

MRenderer::MRenderer( void ) :
m_Screen(NULL),
m_bFontLibLoaded(false)
{
    printf(" -> MRenderer object created.\n");
}

MRenderer::~MRenderer( void )
{
    printf(" -> MRenderer object destructed.\n");
}

bool MRenderer::Init( int iWidth, int iHeight )
{
	printf(" -> Initialising SDL subsystem.\n");

	m_iResolution[0] = iWidth;
	m_iResolution[1] = iHeight;
	
	if( SDL_Init(SDL_INIT_EVERYTHING) == -1 ) {
		printf(" -! ERROR initialising SDL.\n");
		return false;
	} else if( ( m_Screen = SDL_SetVideoMode(m_iResolution[0],m_iResolution[1],32,SDL_SWSURFACE) ) == NULL ) {
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

	std::vector<IDrawable*> DelQueue;
	std::vector<IDrawable*>::iterator it = m_RenderQueue.begin();
	
	for( it = m_RenderQueue.begin(); it < m_RenderQueue.end(); it++ ) {
		if( (*it) ) {
			printf(" -> Scheduling drawable object for deletion (0x%X).\n",(*it));
			DelQueue.push_back((*it));
		}
	}

	// We do this so that the actual render queue is not modified while iterating
	// as it was causing some nasty NULL pointer bugs.
	it = DelQueue.begin();
	for( it = DelQueue.begin(); it < DelQueue.end(); it++ ) {
		if( *it ) {
			printf(" -> Deleting queued drawable object (0x%X).\n",(*it));
			delete (*it);
		}
	}
	
	m_RenderQueue.clear();
	DelQueue.clear();
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

	// Push back and then re-sort the container based on depth.
	m_RenderQueue.push_back(pDrawable);
	std::sort(m_RenderQueue.begin(),m_RenderQueue.end(),MRenderer::SpriteSortFunc);
	
	printf(" -> Registered object (0x%X) with rendering queue.\n",pDrawable);
}

void MRenderer::RemoveDrawable( IDrawable* pDrawable )
{
	std::vector<IDrawable*>::iterator it = m_RenderQueue.begin();
	while( it != m_RenderQueue.end() ) {
		if( (*it) && (*it == pDrawable) ) {
			printf(" -> Removing object (0x%X) from rendering queue.\n",pDrawable);
			it = m_RenderQueue.erase(it);
		} else ++it;
	}

	// Resort based on depth.
	std::sort(m_RenderQueue.begin(),m_RenderQueue.end(),MRenderer::SpriteSortFunc);
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

bool MRenderer::SpriteSortFunc( IDrawable* pData1, IDrawable* pData2 )
{
	return pData1->GetDepth() > pData2->GetDepth();
}

int MRenderer::GetScreenWidth( void )
{
	return m_iResolution[0];
}

int MRenderer::GetScreenHeight( void )
{
	return m_iResolution[1];
}
