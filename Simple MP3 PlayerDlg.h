// Simple MP3 PlayerDlg.h : ヘッダー ファイル
//

#if !defined(AFX_SIMPLEMP3PLAYERDLG_H__CF0B0763_84E5_4EDC_ADE9_23D6132FF6D9__INCLUDED_)
#define AFX_SIMPLEMP3PLAYERDLG_H__CF0B0763_84E5_4EDC_ADE9_23D6132FF6D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define MY_NOTIFYICON (WM_APP + 100)

#define VERSION_INFO		"Denka's Simple MP3 Player Version 1.13 (July 1st 2012)"
#define RESUME_FILE_NAME	"default.lst"
#define MEM_FILE_NAME1		"mem1.lst"
#define MEM_FILE_NAME2		"mem2.lst"
#define MEM_FILE_NAME3		"mem3.lst"
#define MEM_FILE_NAME4		"mem4.lst"
#define MEM_FILE_NAME5		"mem5.lst"

#include <dshow.h>
#include "MemSelect.h"

/////////////////////////////////////////////////////////////////////////////
// CSimpleMP3PlayerDlg ダイアログ

class CSimpleMP3PlayerDlg : public CDialog
{
// 構築
public:
	CSimpleMP3PlayerDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ
	CString m_CmdLine;

// ダイアログ データ
	//{{AFX_DATA(CSimpleMP3PlayerDlg)
	enum { IDD = IDD_SIMPLEMP3PLAYER_DIALOG };
	CSliderCtrl	m_Slider;
	CListBox	m_ListBox;
	CString	m_Status;
	CString	m_Timer;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSimpleMP3PlayerDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	void GetFileName(LPCSTR fname,LPCSTR buffer);
	BOOL CheckDirOrFile(LPCSTR fname);
	BOOL PlayMP3(int nCount);

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSimpleMP3PlayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDblclkList();
	afx_msg void OnWindowclose();
#ifdef _WIN64
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#else
	afx_msg void OnTimer(UINT nIDEvent);
#endif
	afx_msg void OnPlay();
	afx_msg void OnStop();
	afx_msg void OnDelete();
	afx_msg void OnDeleteAll();
	afx_msg void OnBefore();
	afx_msg void OnNext();
	afx_msg void OnMoveUp();
	afx_msg void OnMoveBottom();
	afx_msg void OnReleasedcaptureSlider(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    NOTIFYICONDATA m_nIcon;
	BOOL m_bDlgShow;
	CMenu m_Menu;
	CMenu* m_pPopup;
	int m_nPlayingNumber;
	int m_nResumePlayNumber;
	CString m_PlayingFileName;
	CMemSelect m_MemDlg;
	int m_TimerNum;

    IMediaControl *pMediaControl;
    IMediaEvent   *pEvent;
	IGraphBuilder *pGraph;
	IMediaSeeking *pSeek;

	void SetShowDialog(BOOL b);
	bool MemFileRead(char *fname);

public:
	afx_msg void OnBnClickedPreset();
	afx_msg void OnBnClickedCh1();
	afx_msg void OnBnClickedCh2();
	afx_msg void OnBnClickedCh3();
	afx_msg void OnBnClickedCh4();
	afx_msg void OnBnClickedCh5();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SIMPLEMP3PLAYERDLG_H__CF0B0763_84E5_4EDC_ADE9_23D6132FF6D9__INCLUDED_)
