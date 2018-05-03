#include "stdafx.h"
#include "WMath.h"

float WMath::Dot(CVector2D v1, CVector2D v2)
{
	return	(v1.GetX() * v2.GetX()) +
			(v1.GetY() * v2.GetY());
}

float WMath::Dot(CVector3D v1, CVector3D v2)
{
	return	(v1.GetX() * v2.GetX()) +
			(v1.GetY() * v2.GetY()) +
			(v1.GetZ() * v2.GetZ());
}

float WMath::Dot(CVector4D v1, CVector4D v2)
{
	return	(v1.GetX() * v2.GetX()) +
			(v1.GetY() * v2.GetY()) +
			(v1.GetZ() * v2.GetZ()) +
			(v1.GetW() * v2.GetW());
}

float WMath::Cross(CVector2D v1, CVector2D v2)
{
	return	(v1.GetX() * v2.GetY()) -
			(v1.GetY() * v2.GetX());
}

CVector3D WMath::Cross(CVector3D v1, CVector3D v2)
{
	return CVector3D(
		((v1.GetY() * v2.GetZ()) - (v1.GetZ() * v2.GetY())),
		((v1.GetZ() * v2.GetX()) - (v1.GetX() * v2.GetZ())),
		((v1.GetX() * v2.GetY()) - (v1.GetY() * v2.GetX())));
}

//NOTE: 4D cross product provided is simply 3D cross product with W.
// With it being cross product, W is provided as zero to signify a direction.
CVector4D WMath::Cross(CVector4D v1, CVector4D v2)
{
	return CVector4D(Cross(CVector3D(v1), CVector3D(v2)), 0.0f);
}

int WMath::Sign(int x)
{
	return (x > 0) - (x < 0);
}

WMath::WMath()
{
}