#pragma once

class CVector2D;
class CVector3D;

class CVector4D
{
public:
	CVector4D();
	CVector4D(float n);
	CVector4D(float x, float y, float z, float w);
	CVector4D(CVector2D v1, CVector2D v2);
	CVector4D(CVector3D v, float w);
	CVector4D(CVector4D& other);
	~CVector4D();

	float GetX() { return _x; }
	void SetX(float x) { _x = x; }
	float GetY() { return _y; }
	void SetY(float y) { _y = y; }
	float GetZ() { return _z; }
	void SetZ(float z) { _z = z; }
	float GetW() { return _w; }
	void SetW(float w) { _w = w; }
private:
	float _x, _y, _z, _w;
};

