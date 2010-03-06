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

#ifndef _SURFACECACHE_H_
#define _SURFACECACHE_H_

#include "../Public/Public.h"
#include "ThirdParty.h"
#include "../Interfaces/ISurfaceCache.h"

/// Fix me.
class MSurfaceCache : public ISurfaceCache
{
public:

	MSurfaceCache( void );
	~MSurfaceCache( void );

	unsigned int SurfFromFile( string sFileName );
	unsigned int ClippedSurfFromFile( string sFileName, int x, int y, int iWidth, int iHeight, int r, int g, int b );

private:

	map<string,unsigned int> m_Surfaces;
};

typedef shared_ptr<MSurfaceCache> MSurfaceCachePtr;

#endif // _SURFACECACHE_H_
