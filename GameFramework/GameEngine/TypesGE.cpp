#include "Types.h"
#include "../Core/MemGuard.hpp"
#include "../Core/Events.hpp"
#ifdef DEBUG
#include "../MemGuard.h"
#endif

GF::GameEngine::Box::Box(const Box & rhs)
{
	x = rhs.x; y = rhs.y; z = rhs.z;
	width = rhs.width; height = rhs.height; depth = rhs.depth;
}

GF::GameEngine::Box::Box(Vector3D v, Size s)
{
	x = v.x; y = v.y; z = v.z; width = s.width; height = s.height; depth = s.depth;
}

GF::GameEngine::Box::Box(float v1, float v2, float v3, float v4, float v5, float v6)
{
	x = v1; y = v2; z = v3; width = v4; height = v5; depth = v6;
}

GF::GameEngine::Box::Box(float x, float y, float w, float h)
{
	this->x = x;	this->y = y;	width = w;	height = h;
}

GF::GameEngine::Vector3D::Vector3D(float v1, float v2, float v3)
{
	x = v1; y = v2; z = v3;
}

GF::GameEngine::Vector3D::Vector3D(float v1, float v2)
{
	x = v1; y = v2;
}

GF::GameEngine::Vector3D GF::GameEngine::Vector3D::operator-(const Vector3D & rhs)
{
		Vector3D ret;
		ret.x = x - rhs.x; ret.y = y - rhs.y; ret.z = z - rhs.z;
		return ret;
}

GF::GameEngine::Vector3D GF::GameEngine::Vector3D::operator+(const Vector3D & rhs)
{
	Vector3D ret;
	ret.x = x + rhs.x; ret.y = y + rhs.y; ret.z = z + rhs.z;
	return ret;
}

GF::GameEngine::Vector3D GF::GameEngine::Vector3D::operator*(float s)
{
	Vector3D ret;
	ret.x = x*s; ret.y = y*s; ret.z = z* s;
	return ret;
}

bool GF::GameEngine::Vector3D::operator==(const Vector3D &rhs)
{
	return (x==rhs.x&&y==rhs.y&&z==rhs.z);
}

bool GF::GameEngine::Vector3D::operator!=(const Vector3D &rhs)
{
	return !operator==(rhs);
}

GF::GameEngine::Vector3Di::Vector3Di(int v1, int v2, int v3)
{
	x = v1; y = v2; z = v3;
}

GF::GameEngine::Vector3Di::Vector3Di(int v1, int v2)
{
	x = v1; y = v2;
}

GF::GameEngine::Vector3Di GF::GameEngine::Vector3Di::operator-(const Vector3Di & rhs)
{
	Vector3Di ret;
	ret.x = x - rhs.x; ret.y = y - rhs.y; ret.z = z - rhs.z;
	return ret;
}

GF::GameEngine::Vector3Di GF::GameEngine::Vector3Di::operator+(const Vector3Di & rhs)
{
	Vector3Di ret;
	ret.x = x + rhs.x; ret.y = y + rhs.y; ret.z = z + rhs.z;
	return ret;
}

GF::GameEngine::Vector3Di GF::GameEngine::Vector3Di::operator*(int s)
{
	Vector3Di ret;
	ret.x = x*s; ret.y = y*s; ret.z = z* s;
	return ret;
}

bool GF::GameEngine::Vector3Di::operator==(const Vector3Di &rhs)
{
	return (x == rhs.x&&y == rhs.y&&z == rhs.z);
}

bool GF::GameEngine::Vector3Di::operator!=(const Vector3Di &rhs)
{
	return !operator==(rhs);
}

GF::GameEngine::Size::Size(float v1, float v2, float v3)
{
	width = v1; height = v2; depth = v3;
}

GF::GameEngine::Size::Size(float w, float h)
{
	width = w; height = h;
}


