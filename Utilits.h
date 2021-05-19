#pragma once

//-------------------

#include <shlwapi.h>

//-------------------

namespace txu
{

//-------------------

#define WS_NOFRAME ((WS_POPUP | WS_BORDER | WS_CAPTION | WS_SYSMENU) & ~WS_CAPTION)

//-------------------

#define _TXU_INIT_INITIALIZED   1
#define _TXU_INIT_FAILED		2
#define _TXU_INIT_UNINITIALIZED	3

//-------------------

int  _Init   ();
void _Uninit ();

//-------------------

volatile HINSTANCE _ShellApi = nullptr;

typedef LPCSTR (WINAPI* _ShellApi_GetFileExtentionFunc) (LPCSTR);
_ShellApi_GetFileExtentionFunc _ShellApi_GetFileExtention = nullptr;

volatile HINSTANCE _Gdi32 = nullptr;

typedef int (WINAPI* _Gdi32_AddFontResourceExAFunc) (LPCSTR, DWORD, PVOID);
_Gdi32_AddFontResourceExAFunc _Gdi32_AddFontResourceExA = nullptr;

typedef HFONT (WINAPI* _Gdi32_CreateFontAFunc) (int, int, int, int, int, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, LPCSTR);
_Gdi32_CreateFontAFunc _Gdi32_CreateFontA = nullptr;

typedef BOOL (WINAPI* _Gdi32_RemoveFontResourceAFunc) (LPCSTR);
_Gdi32_RemoveFontResourceAFunc _Gdi32_RemoveFontResourceA = nullptr;

//-------------------

volatile int _MouseWheelDelta      = 0;
volatile int _WasExitButtonPressed = false;

int _InitResult = _Init ();

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
	int result = _TXU_INIT_INITIALIZED;

	if (_InitResult == _TXU_INIT_INITIALIZED)
		return result;

	txSetWindowsHook (WndProc);
	
	_ShellApi = LoadLibraryA ("Shlwapi.dll");
	if (_ShellApi)
		(FARPROC&) _ShellApi_GetFileExtention = GetProcAddress (_ShellApi, "PathFindExtensionA");

	else
	{
		printf ("Warning! Failed to load Shlwapi.dll, some functions may crash\n");
		result = _TXU_INIT_FAILED;
	}

	_Gdi32 = LoadLibraryA ("Gdi32.dll");
	if (_Gdi32)
	{
		(FARPROC&) _Gdi32_AddFontResourceExA  = GetProcAddress (_Gdi32, "AddFontResourceExA" );
		(FARPROC&) _Gdi32_CreateFontA         = GetProcAddress (_Gdi32, "CreateFontA"        );
		(FARPROC&) _Gdi32_RemoveFontResourceA = GetProcAddress (_Gdi32, "RemoveFontResourceA");
	}

	else
	{
		printf ("Warning! Failed to load Gdi32.dll, some functions may crash\n");
		result = _TXU_INIT_FAILED; 
	}

	atexit (_Uninit);
	return result;
}

//-------------------

void _Uninit ()
{
	if (_ShellApi)
		FreeLibrary (_ShellApi);

	if (_Gdi32)
		FreeLibrary (_Gdi32);

	_InitResult = _TXU_INIT_UNINITIALIZED;
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

	return true;
}

//-------------------

}