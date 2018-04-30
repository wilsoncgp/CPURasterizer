#include "stdafx.h"
#include "Vector3D.h"
#include "Vector2D.h"
#include "Vector4D.h"

CVector3D::CVector3D()
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
}

CVector3D::CVector3D(float n)
{
	_x = n;
	_y = n;
	_z = n;
}

CVector3D::CVector3D(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

CVector3D::CVector3D(CVector2D& v, float z)
{
	_x = v.GetX();
	_y = v.GetY();
	_z = z;
}

CVector3D::CVector3D(CVector3D& other)
{
	_x = other.GetX();
	_y = other.GetY();
	_z = other.GetZ();
}

CVector3D::CVector3D(CVector4D& other)
{
	_x = other.GetX();
	_y = other.GetY();
	_z = other.GetZ();
}

CVector3D::~CVector3D()
{
}
