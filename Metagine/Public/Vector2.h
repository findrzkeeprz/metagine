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

#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <math.h>

class MVector2
{
public:

	MVector2( void ) 
	{
		x = 0.0f;
		y = 0.0f;
	}
	
	MVector2( float _x, float _y )
	{
		x = _x;
		y = _y;
	}

	MVector2 &operator = (const MVector2& vec)
	{
		x = vec.x;
		y = vec.y;

		return *this;
	}

	// Equals.
	bool operator == (const MVector2& vec) const
	{
		return x == vec.x && y == vec.y;
	}

	// Does not equal.
	bool operator != (const MVector2& vec) const
	{
		return x != vec.x && y != vec.y;
	}

	// Get the negative of the vector.
	MVector2 operator - (void) const
	{
		return MVector2(-x,-y);
	}

	// Add a vector.
	MVector2 operator + (const MVector2& vec) const
	{
		return MVector2(x + vec.x,y + vec.y);
	}

	// Subtract a vector.
	MVector2 operator - (const MVector2& vec) const
	{
		return MVector2(x - vec.x,y - vec.y);
	}

	MVector2 operator * ( const float fScalar ) 
	{
		return MVector2(x * fScalar,y * fScalar);
	}

	MVector2 operator / ( const float fScalar )
	{
		float fOneOverScalar = 1.0f / fScalar;
		return MVector2(x * fOneOverScalar,y * fOneOverScalar);
	}

	// Addition assignment.
	MVector2 &operator += (MVector2& vec)
	{
		x += vec.x;
		y += vec.y;

		return *this;
	}

	// Subtraction assignment.
	MVector2 &operator -= (const MVector2& vec)
	{
		x -= vec.x;
		y -= vec.y;

		return *this;
	}

	// Multiplication assignment.
	MVector2 &operator *= (float fScalar)
	{
		x *= fScalar;
		y *= fScalar;

		return *this;
	}

	// Division assignment.
	MVector2 &operator /= (float fScalar)
	{
		float fOneOverScalar = 1.0f / fScalar;

		x *= fOneOverScalar;
		y *= fOneOverScalar;

		return *this;
	}

	// Normalize the vector.
	void Normalise( void )
	{
		float fMagSq = (x * x) + (y * y);

		if( fMagSq == 0.0f ) {
			return;
		}

		float fOneOverMag = 1.0f / sqrt(fMagSq);
		x *= fOneOverMag;
		y *= fOneOverMag;
	}

	MVector2 Normalised( void )
	{
		MVector2 ret(*this);
		ret.Normalise();
		return ret;
	}

	float Magnitude( void ) const 
	{
		return sqrt((x * x) + (y * y));
	}

	// Set vector to zero.
	void Zero( void )
	{
		x = 0.0f;
		y = 0.0f;
	}

	float x;
	float y;
};

#endif // _VECTOR2_H_