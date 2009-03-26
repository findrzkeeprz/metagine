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
	m_Font = NULL;
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
	} else if( ( m_Screen = SDL_SetVideoMode(1024,768,32,SDL_SWSURFACE) ) == NULL ) {
		printf(" -! ERROR setting SDL video mode.\n");
		return false;
	} else if( TTF_Init() == -1 ) {
		printf(" -! ERROR initialising SDL_TTF subsystem.\n");
		return false;
	}

	// Load the in-game font.
	if( ( m_Font = TTF_OpenFont("tahoma.ttf",12) ) == NULL ) {
		printf(" -! ERROR loading game font: %s.\n",TTF_GetError());
		return false;
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
	TTF_CloseFont(m_Font);
	TTF_Quit();
}

void MRenderer::Frame( void )
{

}