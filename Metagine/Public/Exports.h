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

#ifndef _EXPORTS_H_
#define _EXPORTS_H_

#include "../Interfaces/IEngine.h"
#include "../Interfaces/IRenderTask.h"
#include "../Interfaces/IVarManager.h"

typedef struct EngineExports_s
{
	IRenderTask* pRenderer;
	IVarManager* pVarManager;
} EngineExports_t;

typedef bool (*InitGameModule_t)( IEngine* pEngine );

#endif // _EXPORTS_H_
