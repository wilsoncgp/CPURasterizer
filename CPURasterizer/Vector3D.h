#pragma once
class CVector2D;
class CVector4D;

class CVector3D
{
public:
	CVector3D();
	CVector3D(float n);
	CVector3D(float x, float y, float z);
	CVector3D(CVector2D& v, float z);
	CVector3D(CVector3D& other);
	CVector3D(CVector4D& other);
	~CVector3D();

	float GetX() { return _x; }
	void SetX(float x) { _x = x; }
	float GetY() { return _y; }
	void SetY(float y) { _y = y; }
	float GetZ() { return _z; }
	void SetZ(float z) { _z = z; }
private:
	float _x, _y, _z;
};

