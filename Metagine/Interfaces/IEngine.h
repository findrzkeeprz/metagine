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

#ifndef _IENGINE_H_
#define _IENGINE_H_

#include "../Public/Public.h"
#include "../Interfaces/ITask.h"
#include "../Interfaces/IConsole.h"
#include "../Interfaces/IVarManager.h"
#include "../Interfaces/IRenderer.h"
#include "../Interfaces/IInputManager.h"
#include "../Interfaces/ICollisionResolver.h"
#include "../Interfaces/ISurfaceCache.h"
#include "../Interfaces/IEntityManager.h"

/// Public interface for the MEngine class.
class IEngine
{
public:
    
    virtual ~IEngine( void ) { };
	virtual IConsolePtr Console( void ) = 0;
	virtual IVarManagerPtr VarManager( void ) = 0;
	virtual IRendererPtr Renderer( void ) = 0;
	virtual IInputManagerPtr InputManager( void ) = 0;
	virtual ISurfaceCachePtr SurfaceCache( void ) = 0;
	virtual IEntityManagerPtr EntityManager( void ) = 0;
};

typedef shared_ptr<IEngine> IEnginePtr;

#endif // _IENGINE_H_
