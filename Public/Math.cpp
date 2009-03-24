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

#include <math.h>
#include "Math.h"

MVector3 MMath::CrossProduct( const MVector3* pSrc, const MVector3* pDst )
{
	return MVector3(
		(pSrc->y * pDst->z) - (pSrc->z * pDst->y),
		(pSrc->z * pDst->x) - (pSrc->x * pDst->z),
		(pSrc->x * pDst->y) - (pSrc->y * pDst->x));
}

float MMath::Distance( const MVector3* pSrc, const MVector3* pDst )
{
	float x = pSrc->x - pDst->x;
	float y = pSrc->y - pDst->y;
	float z = pSrc->z - pDst->z;

	return sqrt((x * x) + (y * y) + (z * z));
}
