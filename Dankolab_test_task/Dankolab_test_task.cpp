#include "Game_field.h"
#include "Painting.h"
#include <windowsx.h>

void InitWndClass(WNDCLASS& wnd, HBRUSH BGColor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure);

LRESULT CALLBACK Procedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

//Пока оставлю это здесь для себя:            MessageBoxA(hWnd, "Hey Hey!!", "Paint opened", MB_OK);

Game_field field(start_lines, start_columns);
Painter painter;
bool active = true;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	WNDCLASS window_class = { 0 };
	InitWndClass(window_class, (HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(NULL, IDI_QUESTION),
		L"MainWndClass", Procedure);
	if (!RegisterClassW(&window_class)) {
		return -1;
	}
	HWND hWnd = CreateWindowExW(0, L"MainWndClass", L"Dankolab test task", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		window_start_x, window_start_y, window_start_width, window_start_height, NULL, NULL, NULL, NULL);
	
	painter.init_hWnd(hWnd);

	MSG main_msg;
	while (active) {
		//cond.process_game();
		GetMessageW(&main_msg, NULL, NULL, NULL);
		TranslateMessage(&main_msg);
		DispatchMessageW(&main_msg);
	}

	return 0;
}




LRESULT CALLBACK Procedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg)
	{
	case WM_CREATE:
		break;
	case WM_DESTROY:
		active = false;
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
	{
		int x = GET_X_LPARAM(lp), y = GET_Y_LPARAM(lp);
		if (x >= button_start_x0 && x <= button_start_x1 && y >= button_start_y0 && y <= button_start_y1) {
			field.reboot(start_lines, start_columns);
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
			break;
		}
		if (field.change_by_click(x, y)) {
			RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
		}
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		painter.init_hdc(ps);
		painter.paint(field);
		EndPaint(hWnd, &ps);
		break;
	}
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}




void InitWndClass(WNDCLASS& wnd, HBRUSH BGColor, HCURSOR cursor, HINSTANCE hInst, HICON icon, LPCWSTR name, WNDPROC procedure) {
	wnd.hIcon = icon;
	wnd.hCursor = cursor;
	wnd.hInstance = hInst;
	wnd.lpszClassName = name;
	wnd.hbrBackground = CreateSolidBrush(BG_color);
	wnd.lpfnWndProc = procedure;
}