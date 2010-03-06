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

#ifndef _TIMER_H_
#define _TIMER_H_

/// Simple timer class.
class MTimer
{
public:

	/// Default constructor.
	MTimer( void );

	/// Destructor method.
	~MTimer( void );

	/// Start the timer.
	void Start( void );
	
	/// Stop the timer.
	void Stop( void );
	
	/// Pause the timer.
	void Pause( void );
	
	/// Resume the timer.
	void Resume( void );

	/// Get the number of elapsed ticks.
	float GetTicks( void ) const;
	
	/// Determines whether the the timer is paused.
	bool GetPaused( void ) const;
	
	/// Determines whether the timer is currently running.
	bool GetActive( void ) const;

private:

	double m_dFrequency;
    unsigned __int64 m_iStartTicks;
	unsigned __int64 m_iPausedTicks;
	bool m_bPaused;						///< Whether the timer is paused or not.
	bool m_bActive;						///< Whether the time is currently running.
};

#endif // _TIMER_H_