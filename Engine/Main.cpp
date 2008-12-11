#include <stdio.h>
#include "CEngine.h"

int main( int argc, char *argv[] )
{
    // Start the main engine.
    if( !Engine::GetInstance()->Init() ) {
        printf("Something has gone terribly wrong!\n");
        return 0;
    }    
    
    return 0;
}
