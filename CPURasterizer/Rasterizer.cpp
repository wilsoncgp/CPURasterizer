#include "stdafx.h"
#include "Rasterizer.h"


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
	DrawFilledSquare(_hdc, 50, 30, 50, RGB(0, 0, 255));
}

void CRasterizer::DrawFilledSquare(HDC hdc, int x, int y, int size, COLORREF color)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			SetPixel(hdc, i + x, j + y, color);
		}
	}
}