#pragma once
class CMatrix3D
{
public:
	CMatrix3D();
	~CMatrix3D();

	static CMatrix3D Identity();
private:
	CMatrix3D(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22);

	float _m00, _m01, _m02;
	float _m10, _m11, _m12;
	float _m20, _m21, _m22;
};

