#include "stdafx.h"
#include "Matrix4D.h"


CMatrix4D::CMatrix4D()
{
}


CMatrix4D::~CMatrix4D()
{
}

CMatrix4D CMatrix4D::Identity()
{
	return CMatrix4D(1, 0, 0, 0,
					 0, 1, 0, 0,
					 0, 0, 1, 0,
					 0, 0, 0, 1);
}

CMatrix4D::CMatrix4D(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
{
	_m00 = m00; _m01 = m00; _m02 = m00; _m03 = m00;
	_m10 = m00; _m11 = m00; _m12 = m00; _m13 = m00;
	_m20 = m00; _m21 = m00; _m22 = m00; _m23 = m00;
	_m30 = m00; _m31 = m00; _m32 = m00; _m33 = m00;
}