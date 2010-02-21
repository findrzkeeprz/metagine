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


/*class vec2
{
public:
	double 	elem[2];

public:
	vec2(){}
	vec2(double x, double y){elem[0]=x; elem[1]=y;}
	vec2(double x){elem[0]=elem[1]=x;}

	double operator()(int x) const {return elem[x];}
	double &operator()(int x) {return elem[x];}

	vec2 operator *(const double x) const {vec2 res(*this); res.elem[0]*=x; res.elem[1]*=x; return res;}
	vec2 operator /(const double x) const {vec2 res(*this); res.elem[0]/=x; res.elem[1]/=x; return res;}
	vec2 operator +(const vec2 &x) const {vec2 res(*this); res.elem[0]+=x.elem[0]; res.elem[1]+=x.elem[1]; return res;}
	vec2 operator -(const vec2 &x) const {vec2 res(*this); res.elem[0]-=x.elem[0]; res.elem[1]-=x.elem[1]; return res;}
	vec2 operator -() const {vec2 res(*this); res.elem[0] = - res.elem[0]; res.elem[1] = -res.elem[1]; return res;}
	vec2 &operator *=(const double x) {elem[0]*=x; elem[1]*=x; return (*this);}
	vec2 &operator /=(const double x) {elem[0]/=x; elem[1]/=x; return (*this);}
	vec2 &operator +=(const vec2 &x) {elem[0]+=x.elem[0]; elem[1]+=x.elem[1]; return (*this);}
	vec2 &operator -=(const vec2 &x) {elem[0]-=x.elem[0]; elem[1]-=x.elem[1]; return (*this);}
	bool operator ==(const vec2 &x) const {return((elem[0] == x.elem[0])&&(elem[1] == x.elem[1]));}

	double Magnitude(void) const {return(sqrt((elem[0]*elem[0])+(elem[1]*elem[1])));}
	double Magnitude2(void) const {return((elem[0]*elem[0])+(elem[1]*elem[1]));}
	double Normalise(void) { double x = Magnitude(); elem[0]/=x; elem[1]/=x; return x;}
	vec2 Normalised(void) const {vec2 res(*this); res.Normalise(); return res;}

	double Dot(const vec2 &x) const {return ( (elem[0]*x.elem[0]) + (elem[1]*x.elem[1]) );}
};*/

#endif // _VECTOR2_H_