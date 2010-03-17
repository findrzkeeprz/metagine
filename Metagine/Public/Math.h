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

#ifndef _MATH_H_
#define _MATH_H_

#include "Vector2.h"
#include "Vector3.h"

class MMath
{
public:

	// Vector cross product.
	static MVector3 CrossProduct( const MVector3* pSrc, const MVector3* pDst );

	// Calculate the distance between 2 vectors.
	static float Distance( const MVector3* pSrc, const MVector3* pDst );

	static long Round( float fValue );
};

#endif // _MATH_H_
