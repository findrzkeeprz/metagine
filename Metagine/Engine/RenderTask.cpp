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

#include "RenderTask.h"

MRenderTask::MRenderTask( void ) :
m_Screen(NULL),
m_bFontLibLoaded(false)
{
	printf(" -> MRenderTask object created.\n");
}

MRenderTask::~MRenderTask( void )
{
	printf(" -> MRenderTask object destructed.\n");
}

void MRenderTask::VInit( void )
{
	printf(" -> MRenderTask::VInit() called.\n");
	printf(" -> Initialising SDL subsystem.\n");

	m_iResolution[0] = 1024;
	m_iResolution[1] = 576;
	
	if( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) == -1 ) {
		printf(" -! ERROR initialising SDL.\n");
		return;
	} else if( ( m_Screen = SDL_SetVideoMode(m_iResolution[0],m_iResolution[1],32,SDL_OPENGL) ) == NULL ) {
		printf(" -! ERROR setting SDL video mode.\n");
		return;
	} else if( TTF_Init() == -1 ) {
		printf(" -! ERROR initialising SDL_TTF subsystem.\n");
		m_bFontLibLoaded = false;
		return;
	} else {
		m_bFontLibLoaded = true;
	}

	// Set the window caption.
	SDL_WM_SetCaption("Able in Space",NULL);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

	glEnable( GL_TEXTURE_2D );
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glViewport(0,0,m_iResolution[0],m_iResolution[1]);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f,m_iResolution[0],m_iResolution[1],0.0f,-1.0f,1.0f);
	glMatrixMode(GL_TEXTURE);
	glRotatef(180.0f,0.0f,0.0f,1.0f);
	glScalef(-1.0f,1.0f,1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

void MRenderTask::VKill( void )
{
	printf(" -> MRenderTask::VKill() called.\n");
	
	vector<IDrawablePtr>::iterator it = m_RenderQueue.begin();
	for( it = m_RenderQueue.begin(); it < m_RenderQueue.end(); ++it ) {
		if( *it ) {
			printf(" -> Releasing queued drawable object (0x%X).\n",(*it).get());
			it->reset();
		}
	}

	// Do some housekeeping.
	m_RenderQueue.clear();
	SDL_Quit();
	TTF_Quit();
}

void MRenderTask::VFrame( const float fDelta )
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	
	// Render all queued objects.
	vector<IDrawablePtr>::iterator it;
	for( it = m_RenderQueue.begin(); it < m_RenderQueue.end(); ++it )
		if( (*it)->GetActive() ) (*it)->Render();
	
	SDL_GL_SwapBuffers();
	glFinish();
}


bool MRenderTask::FontLibLoaded( void )
{
	return m_bFontLibLoaded;
}

void MRenderTask::RegisterDrawable( IDrawablePtr pDrawable )
{
	if( !pDrawable ) {
		// Error msg here
		return;
	}

	// Push back and then re-sort the container based on depth.
	// Sprites need to be drawn back-to-front otherwise areas
	// with transparency will appear as the background colour.
	m_RenderQueue.push_back(IDrawablePtr(pDrawable));
	sort(m_RenderQueue.begin(),m_RenderQueue.end(),MRenderTask::SpriteSortFunc);
	
	printf(" -> Registered object (0x%X) with rendering queue.\n",pDrawable);
}

void MRenderTask::RemoveDrawable( IDrawablePtr pDrawable )
{
	vector<IDrawablePtr>::iterator it = m_RenderQueue.begin();
	while( it != m_RenderQueue.end() ) {
		if( (*it) && ((*it) == pDrawable) ) {
			printf(" -> Removing object (0x%X) from rendering queue.\n",pDrawable);
			it = m_RenderQueue.erase(it);
		} else ++it;
	}

	// Resort based on depth.
	sort(m_RenderQueue.begin(),m_RenderQueue.end(),MRenderTask::SpriteSortFunc);
}

bool MRenderTask::SpriteSortFunc( IDrawablePtr pData1, IDrawablePtr pData2 )
{
	return pData1->GetDepth() < pData2->GetDepth();
}

int MRenderTask::GetScreenWidth( void )
{
	return m_iResolution[0];
}

int MRenderTask::GetScreenHeight( void )
{
	return m_iResolution[1];
}

int MRenderTask::GetDrawableCount( void )
{
	return (int)m_RenderQueue.size();
}