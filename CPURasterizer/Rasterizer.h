#pragma once
class CRasterizer
{
public:
	CRasterizer();
	~CRasterizer();

	void BeginPaint(HDC hdc);
	void EndPaint();
	void Draw();
	void DrawFilledSquare(HDC hdc, int x, int y, int size, COLORREF color);
private:
	HDC _hdc;
};

