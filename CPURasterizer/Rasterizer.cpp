#include "stdafx.h"
#include "Rasterizer.h"
#include "WMath.h"
#include <stdint.h>

typedef uint8_t uint8;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint64_t uint64;

const int BytesPerPixel = 4;

CRasterizer::CRasterizer()
{
	_xOffset = 0;
}

CRasterizer::~CRasterizer()
{
	if (_bitmapMemory)
	{
		VirtualFree(_bitmapMemory, NULL, MEM_RELEASE);
	}
}

void CRasterizer::Update()
{
	_xOffset++;
}

void CRasterizer::Draw()
{
	ClearToColor(0, 128, 0);
	//DrawWeirdGradient(0, 0);
#pragma region OldDrawCode
	// Draw blue filled square
	DrawFilledSquare(_xOffset + 100, 100, 50, RGB(0, 0, 255));

	// Draw lines showing all horizontal, vertical, diagonal and all octants
	// Horizontal left
	DrawLine(400, 300, 200, 300, RGB(255, 0, 0));
	// Octant top-left-left
	DrawLine(400, 300, 200, 200, RGB(255, 0, 0));
	// Diagonal up-left
	DrawLine(400, 300, 200, 100, RGB(255, 0, 0));
	// Octant top-left-top
	DrawLine(400, 300, 300, 100, RGB(255, 0, 0));
	// Vertical up
	DrawLine(400, 300, 400, 100, RGB(255, 0, 0));
	// Octant top-right-top
	DrawLine(400, 300, 500, 100, RGB(255, 0, 0));
	// Diagonal up-right
	DrawLine(400, 300, 600, 100, RGB(255, 0, 0));
	// Octant top-right-right
	DrawLine(400, 300, 600, 200, RGB(255, 0, 0));
	// Horizontal right
	DrawLine(400, 300, 600, 300, RGB(255, 0, 0));
	// Octant bottom-right-right
	DrawLine(400, 300, 600, 400, RGB(255, 0, 0));
	// Diagonal down-right
	DrawLine(400, 300, 600, 500, RGB(255, 0, 0));
	// Octant bottom-right-bottom
	DrawLine(400, 300, 500, 500, RGB(255, 0, 0));
	// Vertical down
	DrawLine(400, 300, 400, 500, RGB(255, 0, 0));
	// Octant bottom-left-bottom
	DrawLine(400, 300, 300, 500, RGB(255, 0, 0));
	// Diagonal down-left
	DrawLine(400, 300, 200, 500, RGB(255, 0, 0));
	// Octant bottom-left-left
	DrawLine(400, 300, 200, 400, RGB(255, 0, 0));
#pragma endregion
}

void CRasterizer::ClearToColor(int r, int g, int b)
{
	int pitch = _bitmapInfo.bmiHeader.biWidth * BytesPerPixel;
	uint8* row = (uint8*)_bitmapMemory;
	for (int y = 0; y < _bitmapInfo.bmiHeader.biHeight; y++)
	{
		uint32* pixel = (uint32*)row;
		for (int x = 0; x < _bitmapInfo.bmiHeader.biWidth; x++)
		{
			uint8 red = (uint8)r;
			uint8 green = (uint8)g;
			uint8 blue = (uint8)b;
			uint8 alpha = 0;

			*pixel++ = ((alpha << 24) | (red << 16) | (green << 8) | blue);
		}

		row += pitch;
	}
}

void CRasterizer::DrawPixel(int x, int y, int r, int g, int b)
{
	int pitch = _bitmapInfo.bmiHeader.biWidth * BytesPerPixel;

	uint8* row = ((uint8*)_bitmapMemory) + (pitch * y);
	uint32* pixel = ((uint32*)row) + x;
	*pixel = ((255 << 24) | (r << 16) | (g << 8) | b);
}

void CRasterizer::DrawLine(int x1, int y1, int x2, int y2, COLORREF color)
{
	// dy/dx = m = gradient of the line
	// if:
	//	m = 0 or dy = 0, horizontal line
	//	m = 1 or dy = dx, diagonal line
	//	m = infinite or dx = 0, vertical line
	// therefore if m > 0 & m < 1, increase x every loop
	//		and if m > 1, increase y every loop
	// Also, if dy = 0, draw horizontal
	//	& if dx = 0, draw vertical (basically don't do calc)

	int dx = x2 - x1;
	int dy = y2 - y1;

	// Both points are the same, just set one pixel
	if (dx == 0 && dy == 0)
	{
		//SetPixel(_hdc, x1, y1, color);
		DrawPixel(x1, y1, GetRValue(color), GetGValue(color), GetBValue(color));
	}
	// Horizontal line, y stays the same
	else if (dy == 0)
	{
		int xStart = dx > 0 ? x1 : x2;
		int xEnd = dx > 0 ? x2 : x1;

		for (int x = xStart; x <= xEnd; x++)
		{
			//SetPixel(_hdc, x, y1, color);
			DrawPixel(x, y1, GetRValue(color), GetGValue(color), GetBValue(color));
		}
	}
	// Vertical line, x stays the same
	else if (dx == 0)
	{
		int yStart = dy > 0 ? y1 : y2;
		int yEnd = dy > 0 ? y2 : y1;

		for (int y = yStart; y <= yEnd; y++)
		{
			//SetPixel(_hdc, x1, y, color);
			DrawPixel(x1, y, GetRValue(color), GetGValue(color), GetBValue(color));
		}
	}
	// Diagonal line, x changes exact same time as y
	else if (abs(dy) == abs(dx))
	{
		int xStart = x1;
		int xEnd = x2;
		int yStart = y1;

		int absDX = abs(dx);

		for (int i = 0; i <= absDX; i++)
		{
			int x = xStart + (i * WMath::Sign(dx));
			int y = yStart + (i * WMath::Sign(dy));
			//SetPixel(_hdc, x, y, color);
			DrawPixel(x, y, GetRValue(color), GetGValue(color), GetBValue(color));
		}
	}
	// Within one of the octants
	else
	{
		// First, define which octant we're in
		// if dy > 0, we're in the bottom half
		bool bottom = dy > 0;

		// if dx > 0, we're in the right half
		bool right = dx > 0;

		// Grab gradient and absolute value
		float m = (float)dy / (float)dx;
		float mAbs = fabs(m);

		// if m > 1, we're in the octant where y changes more than x
		bool mGreaterThan1 = mAbs > 1.0f;

		// If m > 1:
		//	- The delta error is dx/dy.
		//	- Y moves from start to end by 1 each loop.
		// If m < 1:
		//	- The delta error is dy/dx.
		//	- X moves from start to end by 1 each loop.
		float deltaErr = mGreaterThan1 ? fabs((float)dx / (float)dy) : mAbs;
		float err = 0.0f;

		int start = mGreaterThan1 ? y1 : x1;
		int end = mGreaterThan1 ? y2 : x2;
		int val1 = mGreaterThan1 ? x1 : y1;
		int val2 = start;
		while (val2 != end)
		{
			/*SetPixel(_hdc,
				mGreaterThan1 ? val1 : val2,
				mGreaterThan1 ? val2 : val1,
				color);*/
			int x = mGreaterThan1 ? val1 : val2;
			int y = mGreaterThan1 ? val2 : val1;
			DrawPixel(x, y, GetRValue(color), GetGValue(color), GetBValue(color));

			err += deltaErr;
			if (err >= 1.0f)
			{
				val1 += WMath::Sign(mGreaterThan1 ? dx : dy);
				err -= 1.0f;
			}

			val2 += WMath::Sign(mGreaterThan1 ? dy : dx);
		}
	}
}

void CRasterizer::DrawFilledSquare(int x, int y, int size, COLORREF color)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			//SetPixel(_hdc, i + x, j + y, color);
			DrawPixel(i + x, j + y, GetRValue(color), GetGValue(color), GetBValue(color));
		}
	}
}

void CRasterizer::DrawWeirdGradient(int blueGradient, int greenGradient)
{
	int pitch = _bitmapInfo.bmiHeader.biWidth * BytesPerPixel;
	uint8* row = (uint8*)_bitmapMemory;
	for (int y = 0; y < _bitmapInfo.bmiHeader.biHeight; y++)
	{
		uint32* pixel = (uint32*)row;
		for (int x = 0; x < _bitmapInfo.bmiHeader.biWidth; x++)
		{
			//uint8 r = (uint8)0;
			uint8 g = (uint8)y;
			uint8 b = (uint8)x;
			//uint8 a = 0;

			*pixel++ = (/*(a << 24) | (r << 16) | */(g << 8) | b);
		}

		row += pitch;
	}
}

void CRasterizer::ResizeDIBSection(int width, int height)
{
	if (_bitmapMemory)
	{
		VirtualFree(_bitmapMemory, NULL, MEM_RELEASE);
	}

	_bitmapInfo.bmiHeader.biSize = sizeof(_bitmapInfo.bmiHeader);
	_bitmapInfo.bmiHeader.biWidth = width;
	_bitmapInfo.bmiHeader.biHeight = height;
	_bitmapInfo.bmiHeader.biPlanes = 1;
	_bitmapInfo.bmiHeader.biBitCount = 32;
	_bitmapInfo.bmiHeader.biCompression = BI_RGB;

	int bitmapMemorySize = (width * height) * BytesPerPixel;
	_bitmapMemory = VirtualAlloc(NULL, bitmapMemorySize, MEM_COMMIT, PAGE_READWRITE);
}

void CRasterizer::UpdateWindow(HDC hdc, RECT* windowRect, int x, int y, int width, int height)
{
	int windowWidth = windowRect->right - windowRect->left;
	int windowHeight = windowRect->bottom - windowRect->top;
	StretchDIBits(
		hdc,
		0, 0, _bitmapInfo.bmiHeader.biWidth, _bitmapInfo.bmiHeader.biHeight,
		0, 0, windowWidth, windowHeight,
		_bitmapMemory,
		&_bitmapInfo,
		DIB_RGB_COLORS, SRCCOPY);
}