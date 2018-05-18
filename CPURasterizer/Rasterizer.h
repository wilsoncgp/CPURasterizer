#pragma once
#include <cmath>
#include <thread>

class CRasterizer
{
public:
	CRasterizer();
	~CRasterizer();

	void ResizeDIBSection(int width, int height);
	void UpdateWindow(HDC hdc, RECT* windowRect, int x, int y, int width, int height);

	void Update();
	void Draw();

	void ClearToColor(int r, int g, int b);
	void DrawLine(int x1, int y1, int x2, int y2, COLORREF color);
	void DrawFilledSquare(int x, int y, int size, COLORREF color);
	void DrawWeirdGradient(int blueOffset, int greenOffset);
private:
	void DrawPixel(int x, int y, int r, int g, int b);

	BITMAPINFO _bitmapInfo;
	void* _bitmapMemory;

	HDC _hdc;

	int _xOffset;
};

