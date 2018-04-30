#include "stdafx.h"
#include "Vector2D.h"


CVector2D::CVector2D()
{
	_x = 0.0f;
	_y = 0.0f;
}

CVector2D::CVector2D(float n)
{
	_x = n;
	_y = n;
}

CVector2D::CVector2D(float x, float y)
{
	_x = x;
	_y = y;
}

CVector2D::CVector2D(CVector2D& other)
{
	_x = other.GetX();
	_y = other.GetY();
}

CVector2D::~CVector2D()
{
}
