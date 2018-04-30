#pragma once
#include <cmath>

class CRasterizer
{
public:
	CRasterizer();
	~CRasterizer();

	void BeginPaint(HDC hdc);
	void EndPaint();
	void Draw();
	void DrawLine(int x1, int y1, int x2, int y2, COLORREF color);
	void DrawFilledSquare(int x, int y, int size, COLORREF color);
private:
	HDC _hdc;
};

