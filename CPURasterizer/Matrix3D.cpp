#include "stdafx.h"
#include "Matrix3D.h"


CMatrix3D::CMatrix3D()
{
}


CMatrix3D::~CMatrix3D()
{
}

CMatrix3D CMatrix3D::Identity()
{
	return CMatrix3D(1, 0, 0,
					 0, 1, 0,
					 0, 0, 1);
}

CMatrix3D::CMatrix3D(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22)
{
	_m00 = m00; _m01 = m00; _m02 = m00;
	_m10 = m00; _m11 = m00; _m12 = m00;
	_m20 = m00; _m21 = m00; _m22 = m00;
}