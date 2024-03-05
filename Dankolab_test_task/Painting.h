#pragma once
#include "Game_field.h"

class Painter {
	HWND hWnd = NULL;
	HDC hdc = NULL;
	bool its_first_painting = true;
public:
	void init_hWnd(HWND hwnd) {
		hWnd = hwnd;
	}
	void init_hdc(PAINTSTRUCT& ps_) {
		hdc = ps_.hdc;
	}
	void paint(Game_field& field);
};

