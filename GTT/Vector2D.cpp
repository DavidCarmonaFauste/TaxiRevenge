#include "Vector2D.h"
#include <SDL_assert.h>

// needed for visual studio
#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

Vector2D Vector2D::ApplyRotation( float32 rotation)
{
	Vector2D v;
	float32 rad = rotation * M_PI / 180;
	v.x = v.x * cos(rad) - v.y * sin(rad);
	v.y = v.x * sin(rad) + v.y * cos(rad);
	return v;
}//Degrees

Vector2D Vector2D::operator/(float32 d) const
{
	Vector2D v;
	v.x = v.x / d;
	v.y = v.y / d;
	return v;
}

Vector2D Vector2D::operator*(float32 d) const
{
	Vector2D v;
	v.x = v.x * d;
	v.y = v.y * d;
	return v;
}

Vector2D Vector2D::operator+(float32 d) const
{
	Vector2D v;
	v.x = v.x + d;
	v.y = v.y + d;
	return v;;
}

Vector2D Vector2D::operator-(float32 d) const
{
	Vector2D v;
	v.x = v.x - d;
	v.y = v.y - d;
	return v;
}
