#include "stdafx.h"
#include "Matrix2D.h"


CMatrix2D::CMatrix2D()
{
}


CMatrix2D::~CMatrix2D()
{
}

CMatrix2D CMatrix2D::Identity()
{
	return CMatrix2D(1, 0,
					 0, 1);
}

CMatrix2D::CMatrix2D(float m00, float m01, float m10, float m11)
{
	_m00 = m00; _m01 = m01;
	_m10 = m10; _m11 = m11;
}