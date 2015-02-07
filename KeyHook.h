#ifndef __KEY_HOOK_H__
#define __KEY_HOOK_H__

LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam);
BOOL WINAPI setHook(HWND hWnd);
BOOL WINAPI unsetHook(void);
WPARAM WINAPI getKeyCD();
BOOL WINAPI IsUpdate(void);

#endif	//__KEY_HOOK_H__	
