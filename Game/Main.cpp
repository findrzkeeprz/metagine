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

#include <windows.h>
#include <stdio.h>
#include "Game86.h"
#include "Game.h"
#include "../Public/Exports.h"

extern "C" GAME86_API bool InitGameModule( IEngine* pEngine )
{
	// Show-stopping error.
	if( !pEngine ) {
		printf(" -! ERROR null MEngine interface pointer.\n");
		return false;
	}

	IGame* pGame = NULL;

	if( !( pGame = Game::GetInstance() ) ) {
		printf(" >! ERROR creating MGame object.\n");
		return 0;
	}

	// Start the game module.
	if( !pGame->Init(pEngine) ) {
		printf(" ... Something has gone terribly wrong!\n");
		return false;
	}

	return true;
}