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
	DrawLine(50, 50, 150, 150, RGB(255, 0, 0));
	DrawFilledSquare(150, 150, 50, RGB(0, 0, 255));
}

//NOTE(Liam): Line drawing using Bresenham's algorithm. Not working
//	in each octant yet, keep going mo'fo!
void CRasterizer::DrawLine(int x1, int y1, int x2, int y2, COLORREF color)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	bool vertical = dx == 0;
	bool up = dy < 0;

	int yTop = up ? y2 : y1;
	int yBottom = up ? y1 : y2;
	
	if (vertical)
	{
		for (int y = yBottom; y <= yTop; y++)
		{
			SetPixel(_hdc, x1, y, color);
		}
	}
	else
	{
		float deltaErr = fabs((float)dy / (float)dx);
		bool right = dx > 0;
		int xRight = right ? x2 : x1;
		int xLeft = right ? x1 : x2;
		int y = yTop;

		float error = 0.0f;
		for (int x = xLeft; x <= xRight; x++)
		{
			SetPixel(_hdc, x, y, color);
			error += deltaErr;
			while (error >= 0.5f)
			{
				y += WMath::Sign(dy);
				error -= 1.0f;
			}
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