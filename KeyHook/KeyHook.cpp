// KeyHook.cpp : DLL �̏��������[�`���ł��B
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

/* DLL �̃C���X�^���X �n���h�� */

#ifdef __cplusplus
  }
#endif

extern HINSTANCE GetThisHInst(void);

/* �t�b�N�v���V�[�W���Ŏg�p����ϐ��͋��L�������ɂ��� */
/*                                                    */
/* ����� Visual C++ �̏ꍇ��                         */
/* �����J�̃I�v�V������ /SECTION:.share,RWS ��ǉ�    */
#pragma data_seg(".share")

HHOOK _hHook = NULL;
HWND  _hWnd  = NULL;
WPARAM wp	= 0;
BOOL   bUpdate = false;
void (*parent)(void);

#pragma data_seg()

/* �t�b�N �v���V�[�W�� */
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
	if (_hHook == NULL) AfxMessageBox(L"�t�b�N���s");
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