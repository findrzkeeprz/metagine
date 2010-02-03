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

// Adapted from: http://www.lazyfoo.net/SDL_tutorials/lesson13/index.php

#include "Timer.h"
#include "../Includes/SDL/SDL.h"

MTimer::MTimer( void ) :
m_iStartTicks(0),
m_iPausedTicks(0),
m_bPaused(false),
m_bActive(false)
{
}

MTimer::~MTimer( void )
{
}

void MTimer::Start( void )
{
	m_bActive = true;
	m_bPaused = false;
	m_iStartTicks = SDL_GetTicks();
}

void MTimer::Stop( void )
{
	m_bActive = false;
	m_bPaused = false;
}

void MTimer::Pause( void )
{
	// TODO: Improve the verbosity here.
	if( !m_bActive || m_bPaused )
		return;

	m_bPaused = true;
	m_iPausedTicks = SDL_GetTicks() - m_iStartTicks;
}

void MTimer::Resume( void )
{
	// TODO: Improve the verbosity here.
	if( !m_bPaused )
		return;

	m_bPaused = false;
	m_iStartTicks = SDL_GetTicks() - m_iPausedTicks;
	m_iPausedTicks = 0;
}

int MTimer::GetTicks( void ) const
{
	if( !m_bActive ) return 0;
	else if( m_bPaused ) return m_iPausedTicks;
	else return SDL_GetTicks() - m_iStartTicks;
}

bool MTimer::GetPaused( void ) const
{
	return m_bPaused;
}

bool MTimer::GetActive( void ) const
{
	return m_bActive;
}