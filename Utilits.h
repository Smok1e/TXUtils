#pragma once

namespace txu
{

//-------------------

#define WS_NOFRAME ((WS_POPUP | WS_BORDER | WS_CAPTION | WS_SYSMENU) & ~WS_CAPTION)

//-------------------

int _Init ();

//-------------------

int _InitResult = _Init ();

volatile int _MouseWheelDelta      = 0;
volatile int _WasExitButtonPressed = false;

//-------------------

LRESULT CALLBACK WndProc (HWND wnd, UINT message, WPARAM wpar, LPARAM lpar);
	bool WndProc_OnCLOSE      ();
	bool WndProc_OnMOUSEWHEEL (WPARAM wpar);

bool WasExitButtonPressed    ();
int  GetMouseWheel           ();

void SetConsoleOutputEnabled (bool enable);
bool IsConsoleOutputEnabled  ();

bool SetWindowIcon (const char* filename);

//-------------------

int _Init ()
{
	txSetWindowsHook (WndProc);
	return true;
}

//-------------------

LRESULT CALLBACK WndProc (HWND wnd, UINT message, WPARAM wpar, LPARAM lpar)
{
	switch (message)
	{
		case WM_CLOSE:      { if (WndProc_OnCLOSE      ()    ) return true; }
		case WM_MOUSEWHEEL: { if (WndProc_OnMOUSEWHEEL (wpar)) return true; }

		default: 
			break;
	}

	return false;
}

//-------------------

bool WndProc_OnCLOSE ()
{
	_WasExitButtonPressed = true;
	return false;
}

//-------------------

bool WndProc_OnMOUSEWHEEL (WPARAM wpar)
{
	_MouseWheelDelta = GET_WHEEL_DELTA_WPARAM (wpar) / 120;
	return true;
}

//-------------------

bool WasExitButtonPressed ()
{
	bool pressed = _WasExitButtonPressed;
	_WasExitButtonPressed = false;

	return pressed;
}

//-------------------

int GetMouseWheel ()
{
	int delta = _MouseWheelDelta;
	_MouseWheelDelta = 0;

	return delta;
}

//-------------------

void SetConsoleOutputEnabled (bool enable)
{
	_txConsole = enable-1;
}

bool IsConsoleOutputEnabled ()
{
	return _txConsole >= 0;
}

//-------------------

bool SetWindowIcon (const char* filename)
{
	HICON icon = (HICON) LoadImageA (NULL, filename, IMAGE_ICON, 32, 32, LR_LOADFROMFILE | LR_SHARED);
	if (!icon) return false;

	SendMessage (txWindow (), WM_SETICON, ICON_SMALL, (LPARAM) icon);
	SendMessage (txWindow (), WM_SETICON, ICON_BIG,   (LPARAM) icon);
}

//-------------------

}