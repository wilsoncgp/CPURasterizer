#include "stdafx.h"
#include "Rasterizer.h"
#include "WMath.h"


CRasterizer::CRasterizer()
{
}


CRasterizer::~CRasterizer()
{
}

void CRasterizer::BeginPaint(HDC hdc)
{
	_hdc = hdc;
}

void CRasterizer::EndPaint()
{
	_hdc = nullptr;
}

void CRasterizer::Draw()
{
	// Draw blue filled square
	DrawFilledSquare(100, 100, 50, RGB(0, 0, 255));

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
		SetPixel(_hdc, x1, y1, color);
	}
	// Horizontal line, y stays the same
	else if (dy == 0)
	{
		int xStart = dx > 0 ? x1 : x2;
		int xEnd = dx > 0 ? x2 : x1;

		for (int x = xStart; x <= xEnd; x++)
		{
			SetPixel(_hdc, x, y1, color);
		}
	}
	// Vertical line, x stays the same
	else if (dx == 0)
	{
		int yStart = dy > 0 ? y1 : y2;
		int yEnd = dy > 0 ? y2 : y1;

		for (int y = yStart; y <= yEnd; y++)
		{
			SetPixel(_hdc, x1, y, color);
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
			SetPixel(_hdc, x, y, color);
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
			SetPixel(_hdc,
				mGreaterThan1 ? val1 : val2,
				mGreaterThan1 ? val2 : val1,
				color);

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
			SetPixel(_hdc, i + x, j + y, color);
		}
	}
}