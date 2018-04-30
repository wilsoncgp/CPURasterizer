#pragma once
class CVector2D
{
public:
	CVector2D();
	CVector2D(float n);
	CVector2D(float x, float y);
	CVector2D(CVector2D& other);
	~CVector2D();

	float GetX() { return _x; }
	void SetX(float x) { _x = x; }
	float GetY() { return _y; }
	void SetY(float y) { _y = y; }
private:
	float _x, _y;
};

