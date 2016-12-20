#ifndef RELIGHTER_MATH_VEC2_H
#define RELIGHTER_MATH_VEC2_H

struct vec2
{
	float x,y;

	vec2();
	vec2(float xy);
	vec2(float x, float y);
	vec2(const vec2& rhs);
	vec2& operator=(const vec2& rhs);
	
	float length() const;
	bool isZero() const;

	static vec2 normalize(const vec2& a);
	static float dot(const vec2& a, const vec2& b);
};

vec2 operator *(const vec2& a, const vec2& b);
vec2 operator /(const vec2& a, const vec2& b);
vec2 operator +(const vec2& a, const vec2& b);
vec2 operator -(const vec2& a, const vec2& b);

vec2& operator *=(vec2& a, const vec2& b);
vec2& operator /=(vec2& a, const vec2& b);
vec2& operator +=(vec2& a, const vec2& b);
vec2& operator -=(vec2& a, const vec2& b);

#endif
