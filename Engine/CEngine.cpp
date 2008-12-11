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
#include <assert.h>
#include "CEngine.h"

CEngine::CEngine( void )
{
    printf(" -> CEngine object created.\n");
    
    m_pVarManager = NULL;
}

CEngine::~CEngine( void )
{
    printf(" -> CEngine object destructed.\n");
    
    Shutdown();
}

bool CEngine::Init( void )
{
    printf(" -> CEngine::Init() called.\n");
    
    if( !( m_pVarManager = VarManager::GetInstance() ) ) {
        printf(" -! ERROR creating CVarManager object.\n");
        return false;
    }
    
    return true;
}

void CEngine::Shutdown( void )
{
    printf(" -> CEngine::Shutdown() called.\n");
    
    // Delete allocated objects.
    if( m_pVarManager ) {
        delete m_pVarManager;
    }
}

const IVarManager* CEngine::GetVarManager( void )
{
    assert(m_pVarManager);
    return m_pVarManager;
}
