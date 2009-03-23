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
#include "Engine.h"

int main( int argc, char *argv[] )
{
    IEngine* pEngine = NULL;
    
    printf(" -> Starting Metagine.\n");
    
    if( !( pEngine = Engine::GetInstance() ) ) {
        printf(" >! ERROR creating CEngine object.\n");
        return 0;
    }
    
    // Start the main engine.
    if( !pEngine->Init() ) {
        printf(" ... Something has gone terribly wrong!\n");
        return 0;
    }
    
    delete pEngine;
    
    return 0;
}
