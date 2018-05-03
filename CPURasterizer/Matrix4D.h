#pragma once
class CMatrix4D
{
public:
	CMatrix4D();
	~CMatrix4D();

	static CMatrix4D Identity();
private:
	CMatrix4D(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);

	float _m00, _m01, _m02, _m03;
	float _m10, _m11, _m12, _m13;
	float _m20, _m21, _m22, _m23;
	float _m30, _m31, _m32, _m33;
};

