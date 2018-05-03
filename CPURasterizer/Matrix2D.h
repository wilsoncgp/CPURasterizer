#pragma once
class CMatrix2D
{
public:
	CMatrix2D();
	~CMatrix2D();

	static CMatrix2D Identity();
private:
	CMatrix2D(float m00, float m01, float m10, float m11);
	float _m00, _m01;
	float _m10, _m11;
};

