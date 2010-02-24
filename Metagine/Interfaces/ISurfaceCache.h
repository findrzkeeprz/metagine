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

#ifndef _ISURFACECACHE_H_
#define _ISURFACECACHE_H_

#include "../Public/Public.h"

class ISurfaceCache
{
public:

	virtual ~ISurfaceCache( void ) { };

	virtual void* SurfFromFile( string sFileName ) = 0;
	virtual void* ClippedSurfFromFile( string sFileName, int x, int y, int iWidth, int iHeight, int r, int g, int b ) = 0;
};

typedef shared_ptr<ISurfaceCache> ISurfaceCachePtr;

#endif // _ISURFACECACHE_H_
