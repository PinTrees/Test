#pragma once
#include <windows.h>
#include "tstring.h"

class IDraw {
public:
	virtual void DrawCall(HDC hdc) = 0;
};


class Player : public IDraw {
public:
	int size = 40;
	int x = 0;
	int y = 0;

	void SetPositin(int X, int Y) {
		x =  X;
		y =  Y;
	}

	RECT* GetRect() {
		RECT* rect = new RECT();
		SetRect(rect, x, y, x + size, y + size);
		return rect;
	}

    void DrawCall(HDC hdc) override {
		HBRUSH hBrush, hOldBrush;
		hBrush = CreateSolidBrush(RGB(200, 200, 200));
		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		Rectangle(hdc, x, y, x + 40, y + 40);
		DeleteObject(SelectObject(hdc, hOldBrush));
	}

	Player() {
	}
	Player(int) {
	}
};