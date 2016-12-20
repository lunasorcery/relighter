#include <cmath>
#include "vec2.h"

vec2::vec2()
: x(0), y(0)
{ }

vec2::vec2(float xy)
: x(xy), y(xy)
{ }

vec2::vec2(float x, float y)
: x(x), y(y)
{ }

vec2::vec2(const vec2& rhs)
: x(rhs.x), y(rhs.y)
{ }

vec2& vec2::operator=(const vec2& rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}

float vec2::length() const
{
	return sqrtf(vec2::dot(*this, *this));
}

vec2 vec2::normalize(const vec2& a)
{
	float invLength = 1.0f / a.length();
	return a * invLength;
}

float vec2::dot(const vec2& a, const vec2& b)
{
	return (a.x*b.x)+(a.y*b.y);
}

vec2 operator *(const vec2& a, const vec2& b) { return vec2(a.x*b.x, a.y*b.y); }
vec2 operator /(const vec2& a, const vec2& b) { return vec2(a.x/b.x, a.y/b.y); }
vec2 operator +(const vec2& a, const vec2& b) { return vec2(a.x+b.x, a.y+b.y); }
vec2 operator -(const vec2& a, const vec2& b) { return vec2(a.x-b.x, a.y-b.y); }

vec2& operator *=(vec2& a, const vec2& b) { a.x *= b.x; a.y *= b.y; return a; }
vec2& operator /=(vec2& a, const vec2& b) { a.x /= b.x; a.y /= b.y; return a; }
vec2& operator +=(vec2& a, const vec2& b) { a.x += b.x; a.y += b.y; return a; }
vec2& operator -=(vec2& a, const vec2& b) { a.x -= b.x; a.y -= b.y; return a; }
