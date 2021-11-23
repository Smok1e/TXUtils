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

volatile int   _MouseWheelDelta                  = 0;
volatile int   _WasExitButtonPressed             = false;
volatile int   _LastWasExitButtonPressedCallTime = GetTickCount ();
volatile int   _WasWindowResized                 = false;
         POINT _NewWindowSize                    = {};

volatile bool    _CursorVisible = true;
volatile HCURSOR _CursorHandle  = nullptr;

WNDPROC _AltWndProc = nullptr;

bool _InitResult = _Init ();

//-------------------

LRESULT CALLBACK WndProc  (HWND wnd, UINT message, WPARAM wpar, LPARAM lpar);
bool WndProc_OnCLOSE      ();
bool WndProc_OnMOUSEWHEEL (WPARAM wpar);
bool WndProc_OnSETCURSOR  (LPARAM lpar);
bool WndProc_OnSIZE       (LPARAM lpar);

WNDPROC _SetTxWindowsHook (WNDPROC new_proc = nullptr);

bool WasExitButtonPressed    ();
int  GetMouseWheel           ();

void SetConsoleOutputEnabled (bool enable);
bool IsConsoleOutputEnabled  ();

bool SetWindowIcon (const char* filename);

void SetWindowCursor  (HCURSOR cursor);
void SetCursorVisible (bool visible);
bool IsCursorVisible  ();

void SetWindowResizingEnabled (bool enable, HWND wnd = txWindow ());
bool IsWindowResizingEnabled  (             HWND wnd = txWindow ());
bool WasWindowResized         ();
bool GetNewWindowSize         (POINT* size);

//-------------------

int _Init ()
{
	_AltWndProc = txSetWindowsHook (WndProc);
	return true;
}

//-------------------

LRESULT CALLBACK WndProc (HWND wnd, UINT message, WPARAM wpar, LPARAM lpar)
{
	if (wnd != txWindow ())
		return false;

	if (_AltWndProc) if (_AltWndProc (wnd, message, wpar, lpar)) return true;

	switch (message)
	{
		case WM_CLOSE:      { if (WndProc_OnCLOSE      ()    ) return true; break; }
		case WM_MOUSEWHEEL: { if (WndProc_OnMOUSEWHEEL (wpar)) return true; break; }
		case WM_SETCURSOR:  { if (WndProc_OnSETCURSOR  (lpar)) return true; break; }
		case WM_SIZE:       { if (WndProc_OnSIZE       (lpar)) return true; break; }

		default: break;
	}

	return false;
}

//-------------------

bool WndProc_OnCLOSE ()
{
	_WasExitButtonPressed = true;
	return (GetTickCount () - _LastWasExitButtonPressedCallTime) < 200;
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

bool WndProc_OnSIZE (LPARAM lpar)
{
	unsigned new_x = LOWORD (lpar);
	unsigned new_y = HIWORD (lpar);
	if (!new_x || !new_y) return false;

	_WasWindowResized = true;
	_NewWindowSize.x  = new_x;
	_NewWindowSize.y  = new_y;

	HDC tmp0 = _txBuffer_Create (txWindow (), &_NewWindowSize);
	HDC tmp1 = _txBuffer_Create (txWindow (), &_NewWindowSize);

	txBitBlt (tmp0, 0, 0, new_x, new_y, _txCanvas_BackBuf[0]);
	txBitBlt (tmp1, 0, 0, new_x, new_y, _txCanvas_BackBuf[1]);

	std::swap (tmp0, _txCanvas_BackBuf[0]);
	std::swap (tmp1, _txCanvas_BackBuf[1]);

	_txBuffer_Delete (&tmp0);
	_txBuffer_Delete (&tmp1);

	return true;
}

//-------------------

WNDPROC _SetTxWindowsHook (WNDPROC new_proc /*= nullptr*/)
{
	WNDPROC old_proc = _AltWndProc;
	_AltWndProc = new_proc;

	return old_proc;
}

//-------------------

bool WasExitButtonPressed ()
{
	bool pressed = _WasExitButtonPressed;
	_WasExitButtonPressed = false;

	_LastWasExitButtonPressedCallTime = GetTickCount ();

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

void SetWindowResizingEnabled (bool enable, HWND wnd /*= txWindow ()*/)
{
	if (!wnd) return;

	int style = GetWindowLongA (wnd, GWL_STYLE);
	            SetWindowLongA (wnd, GWL_STYLE, enable? style | WS_SIZEBOX: style & ~WS_SIZEBOX);
}

bool IsWindowResizingEnabled (HWND wnd /*= txWindow ()*/)
{
	if (!wnd) return false;
	return GetWindowLongA (wnd, GWL_STYLE) & WS_SIZEBOX;
}

bool WasWindowResized ()
{
	bool resized = _WasWindowResized;
	_WasWindowResized = false;

	return resized;
}

bool GetNewWindowSize (POINT* size)
{
	*size = _NewWindowSize;
	return WasWindowResized ();
}

//-------------------

} // namespace txu

//-------------------

#ifdef txSetWindowsHook
	#undef txSetWindowsHook
#endif
#define txSetWindowsHook(...) txu::_SetTxWindowsHook (__VA_ARGS__)

//-------------------