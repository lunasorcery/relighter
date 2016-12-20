#ifndef RELIGHTER_MATH_VEC3_H
#define RELIGHTER_MATH_VEC3_H

struct vec3
{
	float x,y,z;

	vec3();
	vec3(float xyz);
	vec3(float x, float y, float z);
	vec3(const vec3& rhs);
	vec3& operator=(const vec3& rhs);
	
	float length() const;
	bool isZero() const;
	
	static vec3 normalize(const vec3& a);
	static vec3 cross(const vec3& a, const vec3& b);
	static float dot(const vec3& a, const vec3& b);
	static vec3 reflect(const vec3& incident, const vec3& normal);
};

vec3 operator -(const vec3& a);

vec3 operator *(const vec3& a, const vec3& b);
vec3 operator /(const vec3& a, const vec3& b);
vec3 operator +(const vec3& a, const vec3& b);
vec3 operator -(const vec3& a, const vec3& b);

vec3& operator *=(vec3& a, const vec3& b);
vec3& operator /=(vec3& a, const vec3& b);
vec3& operator +=(vec3& a, const vec3& b);
vec3& operator -=(vec3& a, const vec3& b);

#endif
