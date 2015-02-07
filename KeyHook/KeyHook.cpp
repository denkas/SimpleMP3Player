// KeyHook.cpp : DLL の初期化ルーチンです。
//

#include "stdafx.h"
#include "KeyHook.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#ifdef __cplusplus
  extern "C"
  {
#endif

/* DLL のインスタンス ハンドル */

#ifdef __cplusplus
  }
#endif

extern HINSTANCE GetThisHInst(void);

/* フックプロシージャで使用する変数は共有メモリにおく */
/*                                                    */
/* これは Visual C++ の場合で                         */
/* リンカのオプションに /SECTION:.share,RWS を追加    */
#pragma data_seg(".share")

HHOOK _hHook = NULL;
HWND  _hWnd  = NULL;
WPARAM wp	= 0;
BOOL   bUpdate = false;
void (*parent)(void);

#pragma data_seg()

/* フック プロシージャ */
LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION && wParam == WM_KEYDOWN)
    {
		KBDLLHOOKSTRUCT *pkbdllhook = (KBDLLHOOKSTRUCT *)lParam;

		wp = pkbdllhook->vkCode;
		bUpdate = true;
	}

	return CallNextHookEx(_hHook, nCode, wParam, lParam);
}

int WINAPI setHook(HWND hWnd)
{
	HINSTANCE hi = GetThisHInst();
	_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)HookProc, GetThisHInst(), 0);
	if (_hHook == NULL) AfxMessageBox(L"フック失敗");
	_hWnd  = hWnd;

	return (_hHook != NULL);
}

BOOL WINAPI unsetHook(void)
{
	return ::UnhookWindowsHookEx(_hHook);
}

WPARAM WINAPI getKeyCD(void)
{
	bUpdate = false;
	return wp;
}

BOOL WINAPI IsUpdate(void)
{
	return bUpdate;
}