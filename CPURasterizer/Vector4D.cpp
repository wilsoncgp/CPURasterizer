#include "stdafx.h"
#include "Vector4D.h"
#include "Vector2D.h"
#include "Vector3D.h"


CVector4D::CVector4D()
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
	_w = 0.0f;
}

CVector4D::CVector4D(float n)
{
	_x = n;
	_y = n;
	_z = n;
	_w = n;
}

CVector4D::CVector4D(float x, float y, float z, float w)
{
	_x = x;
	_y = y;
	_z = z;
	_w = w;
}

CVector4D::CVector4D(CVector2D v1, CVector2D v2)
{
	_x = v1.GetX();
	_y = v1.GetY();
	_z = v2.GetX();
	_w = v2.GetY();
}

CVector4D::CVector4D(CVector3D v, float w)
{
	_x = v.GetX();
	_y = v.GetY();
	_z = v.GetZ();
	_w = w;
}

CVector4D::CVector4D(CVector4D& other)
{
	_x = other.GetX();
	_y = other.GetY();
	_z = other.GetZ();
	_w = other.GetW();
}

CVector4D::~CVector4D()
{
}
