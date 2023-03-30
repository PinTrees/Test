#pragma once
#include "player.h"

class Box : public IDraw {
public:
	int size = 0;
	int x = 0;
	int y = 0;
	int type = 0;

	Box* SetObjectFromData(int type, int maxX, int maxY) {
		isDisbale = false;
		SetRandomPositinAndSize(maxX, maxY);

		if (type == 0) {
			SetColor(0, 0, 255);
		}
		else if (type == 1) {
			SetColor(255, 0, 0);
		}

		return this;
	}

	void SetRandomPositinAndSize(int maxX, int maxY) {
		x = rand() % maxX;
		y = rand() % maxY;
		size = rand() % 10 + 50;
	}
	void SetColor(int _r, int _g, int _b) {
		r = _r; g = _g; b = _b;
	}

	RECT* GetRect() {
		RECT* rect = new RECT();
		SetRect(rect, x, y, x + size, y + size);
		return rect;
	}

	void DrawCall(HDC hdc) override {
		if (isDisbale) return;
		HBRUSH hBrush, hOldBrush;

		hBrush = CreateSolidBrush(RGB(r, g, b));
		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		Rectangle(hdc, x, y, x + size, y + size);
		DeleteObject(SelectObject(hdc, hOldBrush));
	}

	bool isDisbale = false;

	int r;
	int g;
	int b;

	Box() {}
	Box(int) {}
};


class SSS : public IDraw {
public:
	float x;
	float y;
	float speed;
	TString* string;

	SSS() {}
	SSS(int) {}
	SSS(int maxX, int maxY, TCHAR* data) {
		isDisbale = false;
		SetRandomPositinAndSize(maxX, maxY);
		string = new TString(data);
		speed = (rand() % 5 + 1) * 0.15f;
	}

	void SetRandomPositinAndSize(int maxX, int maxY) {
		x = rand() % maxX;
		y = rand() % maxY;
	}

	void DrawCall(HDC hdc) override {
		if (isDisbale) return; 
		TextOut(hdc, x, y, string->characters, lstrlen(string->characters));
	}

	void Move() {
		y += speed;
	}

	bool isDisbale = false;


};