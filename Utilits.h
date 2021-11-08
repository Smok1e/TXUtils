#pragma once

//-------------------

#include <shlwapi.h>

//-------------------

namespace txu
{

//-------------------

#define WS_NOFRAME ((WS_POPUP | WS_BORDER | WS_CAPTION | WS_SYSMENU) & ~WS_CAPTION)

//-------------------

int _Init ();

//-------------------

namespace shellapi
{
	#define __dll_name "Shlwapi"
	_TX_DLLIMPORT (__dll_name, LPCSTR, PathFindExtensionA, (LPCSTR));
	#undef __dll_name
}

namespace gdi
{
	#define __dll_name "Gdi32"
	_TX_DLLIMPORT (__dll_name, int,   AddFontResourceExA,  (LPCSTR, DWORD, PVOID)                                                                   );
	_TX_DLLIMPORT (__dll_name, HFONT, CreateFontA,         (int, int, int, int, int, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, LPCSTR));
	_TX_DLLIMPORT (__dll_name, BOOL,  RemoveFontResourceA, (LPCSTR));
	#undef __dll_name
}

namespace winmm
{
	#define __dll_name "Winmm"
	_TX_DLLIMPORT (__dll_name, BOOL, PlaySoundA, (LPCSTR, HMODULE, DWORD));
	#undef __dll_name
}

namespace comdlg
{
	#define __dll_name "Comdlg32"
	_TX_DLLIMPORT (__dll_name, BOOL, ChooseColorA, (LPCHOOSECOLOR));
	#undef __dll_name
}

//-------------------

volatile int _MouseWheelDelta      = 0;
volatile int _WasExitButtonPressed = false;

volatile bool    _CursorVisible = true;
volatile HCURSOR _CursorHandle  = nullptr;

bool _InitResult = _Init ();

//-------------------

LRESULT CALLBACK WndProc (HWND wnd, UINT message, WPARAM wpar, LPARAM lpar);
bool WndProc_OnCLOSE      ();
bool WndProc_OnMOUSEWHEEL (WPARAM wpar);
bool WndProc_OnSETCURSOR  (LPARAM lpar);

bool WasExitButtonPressed    ();
int  GetMouseWheel           ();

void SetConsoleOutputEnabled (bool enable);
bool IsConsoleOutputEnabled  ();

bool SetWindowIcon (const char* filename);

void SetWindowCursor  (HCURSOR cursor);
void SetCursorVisible (bool visible);
bool IsCursorVisible  ();

//-------------------

int _Init ()
{
	txSetWindowsHook (WndProc);
	return true;
}

//-------------------

LRESULT CALLBACK WndProc (HWND wnd, UINT message, WPARAM wpar, LPARAM lpar)
{
	if (wnd != txWindow ())
		return false;

	switch (message)
	{
		case WM_CLOSE:      { if (WndProc_OnCLOSE      ()    ) return true; }
		case WM_MOUSEWHEEL: { if (WndProc_OnMOUSEWHEEL (wpar)) return true; }
		case WM_SETCURSOR:  { if (WndProc_OnSETCURSOR  (lpar)) return true; }

		default: break;
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

bool WndProc_OnSETCURSOR (LPARAM lpar)
{
	if (LOWORD (lpar) != HTCLIENT) return false;

	if (_CursorVisible)
	{
		if (_CursorHandle) SetCursor (_CursorHandle);
		else return false;
	}
	else SetCursor (nullptr);

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

	SendMessageA (txWindow (), WM_SETICON, ICON_SMALL, (LPARAM) icon);
	SendMessageA (txWindow (), WM_SETICON, ICON_BIG,   (LPARAM) icon);

	return true;
}

//-------------------

void SetWindowCursor (HCURSOR cursor)
{
	_CursorHandle = cursor;
	SendMessageA (txWindow (), WM_SETCURSOR, 0, MAKELPARAM (HTCLIENT, 0));
}

void SetCursorVisible (bool visible)
{
	_CursorVisible = visible;
	SendMessageA (txWindow (), WM_SETCURSOR, 0, MAKELPARAM (HTCLIENT, 0));
}

bool IsCursorVisible ()
{
	return _CursorVisible;
}

//-------------------

} // namespace txu