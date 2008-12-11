#include <stdio.h>
#include "CEngine.h"

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
        printf("Something has gone terribly wrong!\n");
        return 0;
    }
    
    delete pEngine;
    
    return 0;
}
