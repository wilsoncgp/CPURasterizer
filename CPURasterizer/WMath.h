#pragma once
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"

class WMath
{
public:
	static float Dot(CVector2D v1, CVector2D v2);
	static float Dot(CVector3D v1, CVector3D v2);
	static float Dot(CVector4D v1, CVector4D v2);
	static float Cross(CVector2D v1, CVector2D v2);
	static CVector3D Cross(CVector3D v1, CVector3D v2);
	static CVector4D Cross(CVector4D v1, CVector4D v2);
	static int Sign(int x);
private:
	WMath();
};