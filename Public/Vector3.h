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

#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <math.h>

class MVector3
{
public:

	// Constructors and destructor.
	MVector3::MVector3( void )
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	// Construct by copying existing vector.
	MVector3::MVector3( const MVector3* pVector )
	{
		x = pVector->x;
		y = pVector->y;
		z = pVector->z;
	}

	// Construct with 3 float values.
	MVector3::MVector3( float _x, float _y, float _z )
	{
		x = _x;
		y = _y;
		z = _z;
	}

	// Destructor.
	MVector3::~MVector3( void ) { }

	// Assignment.
	MVector3 &operator = (const MVector3* pVector)
	{
		x = pVector->x;
		y = pVector->y;
		z = pVector->z;

		return *this;
	}

	// Equals.
	bool operator == (const MVector3* pVector) const
	{
		return x == pVector->x &&
			y == pVector->y &&
			z == pVector->z;
	}

	// Does not equal.
	bool operator != (const MVector3* pVector) const
	{
		return x != pVector->x &&
			y != pVector->y &&
			z != pVector->z;
	}

	// Get the negative of the vector.
	MVector3 operator - (void) const
	{
		return MVector3(-x,-y,-z);
	}

	// Add a vector.
	MVector3 operator + (const MVector3* pVector) const
	{
		return MVector3(x + pVector->x,
			y + pVector->y,
			z + pVector->z);
	}

	// Subtract a vector.
	MVector3 operator - (const MVector3* pVector) const
	{
		return MVector3(x - pVector->x,
			y - pVector->y,
			z - pVector->z);
	}

	// Multiplication by a scalar.
	MVector3 operator * (float fScalar) const
	{
		return MVector3(x * fScalar,
			y * fScalar,
			z * fScalar);
	}

	// Division by a scalar.
	MVector3 operator / (float fScalar) const
	{
		float fOneOverScalar = 1.0f / fScalar;

		return MVector3(x * fOneOverScalar,
			y * fOneOverScalar,
			z * fOneOverScalar);
	}

	// Addition assignment.
	MVector3 &operator += (const MVector3* pVector)
	{
		x += pVector->x;
		y += pVector->y;
		z += pVector->z;

		return *this;
	}

	// Subtraction assignment.
	MVector3 &operator -= (const MVector3* pVector)
	{
		x -= pVector->x;
		y -= pVector->y;
		z -= pVector->z;

		return *this;
	}

	// Multiplication assignment.
	MVector3 &operator *= (float fScalar)
	{
		x *= fScalar;
		y *= fScalar;
		z *= fScalar;

		return *this;
	}

	// Division assignment.
	MVector3 &operator /= (float fScalar)
	{
		float fOneOverScalar = 1.0f / fScalar;
		
		x *= fOneOverScalar;
		y *= fOneOverScalar;
		z *= fOneOverScalar;

		return *this;
	}

	// Normalize the vector.
	void Normalize( void )
	{
		float fMagSq = (x * x) + (y * y) + (z * z);

		if( fMagSq == 0.0f ) {
			return;
		}

		float fOneOverMag = 1.0f / sqrt(fMagSq);
		x *= fOneOverMag;
		y *= fOneOverMag;
		z *= fOneOverMag;
	}

	// Set vector to zero.
	void Zero( void )
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	// We want these to be public.
	// Rather than accessing with 'get' functions.
	float x;
	float y;
	float z;
};

#endif // _VECTOR3_H_
