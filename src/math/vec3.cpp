#include <cmath>
#include "vec3.h"

vec3::vec3()
: x(0), y(0), z(0)
{ }

vec3::vec3(float xyz)
: x(xyz), y(xyz), z(xyz)
{ }

vec3::vec3(float x, float y, float z)
: x(x), y(y), z(z)
{ }

vec3::vec3(const vec3& rhs)
: x(rhs.x), y(rhs.y), z(rhs.z)
{ }

vec3& vec3::operator=(const vec3& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

float vec3::length() const
{
	return sqrtf(vec3::dot(*this, *this));
}

bool vec3::isZero() const
{
	return (x==0) && (y==0) && (z==0);
}

vec3 vec3::normalize(const vec3& a)
{
	float invLength = 1.0f / a.length();
	return a * invLength;
}

vec3 vec3::cross(const vec3& a, const vec3& b)
{
	return vec3(
		(a.y * b.z) - (a.z * b.y),
		(a.z * b.x) - (a.x * b.z),
		(a.x * b.y) - (a.y * b.x)
	);
}

float vec3::dot(const vec3& a, const vec3& b)
{
	return (a.x*b.x)+(a.y*b.y)+(a.z*b.z);
}

vec3 vec3::reflect(const vec3& i, const vec3& n)
{
	return i - 2 * vec3::dot(i, n) * n;
}

vec3 operator -(const vec3& a) { return vec3(-a.x, -a.y, -a.z); }

vec3 operator *(const vec3& a, const vec3& b) { return vec3(a.x*b.x, a.y*b.y, a.z*b.z); }
vec3 operator /(const vec3& a, const vec3& b) { return vec3(a.x/b.x, a.y/b.y, a.z/b.z); }
vec3 operator +(const vec3& a, const vec3& b) { return vec3(a.x+b.x, a.y+b.y, a.z+b.z); }
vec3 operator -(const vec3& a, const vec3& b) { return vec3(a.x-b.x, a.y-b.y, a.z-b.z); }

vec3& operator *=(vec3& a, const vec3& b) { a.x *= b.x; a.y *= b.y; a.z *= b.z; return a; }
vec3& operator /=(vec3& a, const vec3& b) { a.x /= b.x; a.y /= b.y; a.z /= b.z; return a; }
vec3& operator +=(vec3& a, const vec3& b) { a.x += b.x; a.y += b.y; a.z += b.z; return a; }
vec3& operator -=(vec3& a, const vec3& b) { a.x -= b.x; a.y -= b.y; a.z -= b.z; return a; }
