// Simple MP3 PlayerDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "Simple MP3 Player.h"
#include "Simple MP3 PlayerDlg.h"
#include "KeyHook.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// アプリケーションのバージョン情報で使われている CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// メッセージ ハンドラがありません。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleMP3PlayerDlg ダイアログ

CSimpleMP3PlayerDlg::CSimpleMP3PlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSimpleMP3PlayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSimpleMP3PlayerDlg)
	m_Status = _T("");
	m_Timer = _T("停止");
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_CmdLine = _T("");
	m_TimerNum = 1;
}

void CSimpleMP3PlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSimpleMP3PlayerDlg)
	DDX_Control(pDX, IDC_SLIDER, m_Slider);
	DDX_Control(pDX, IDC_LIST, m_ListBox);
	DDX_Text(pDX, IDC_STATUS, m_Status);
	DDX_Text(pDX, IDC_TIME, m_Timer);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSimpleMP3PlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CSimpleMP3PlayerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_DBLCLK(IDC_LIST, OnDblclkList)
	ON_BN_CLICKED(IDC_WINDOWCLOSE, OnWindowclose)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_DELETE_ALL, OnDeleteAll)
	ON_BN_CLICKED(IDC_BEFORE, OnBefore)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_MOVE_UP, OnMoveUp)
	ON_BN_CLICKED(IDC_MOVE_BOTTOM, OnMoveBottom)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER, OnReleasedcaptureSlider)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_PRESET, &CSimpleMP3PlayerDlg::OnBnClickedPreset)
	ON_BN_CLICKED(IDC_CH1, &CSimpleMP3PlayerDlg::OnBnClickedCh1)
	ON_BN_CLICKED(IDC_CH2, &CSimpleMP3PlayerDlg::OnBnClickedCh2)
	ON_BN_CLICKED(IDC_CH3, &CSimpleMP3PlayerDlg::OnBnClickedCh3)
	ON_BN_CLICKED(IDC_CH4, &CSimpleMP3PlayerDlg::OnBnClickedCh4)
	ON_BN_CLICKED(IDC_CH5, &CSimpleMP3PlayerDlg::OnBnClickedCh5)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleMP3PlayerDlg メッセージ ハンドラ

BOOL CSimpleMP3PlayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "バージョン情報..." メニュー項目をシステム メニューへ追加します。

	// IDM_ABOUTBOX はコマンド メニューの範囲でなければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定

	VERIFY(m_Menu.LoadMenu(IDR_MENU));
	m_pPopup = m_Menu.GetSubMenu(0);
	ASSERT(m_pPopup != NULL);
	m_bDlgShow = TRUE;
	m_nPlayingNumber = -1;
	m_nResumePlayNumber = -1;

	m_Status = VERSION_INFO;
	UpdateData(FALSE);

	DragAcceptFiles(TRUE);
	m_ListBox.SetHorizontalExtent(2048);

	m_nIcon.cbSize = sizeof(m_nIcon);
	m_nIcon.hWnd = this->m_hWnd;
	m_nIcon.uID = 0;
	m_nIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nIcon.uCallbackMessage = MY_NOTIFYICON;
	m_nIcon.hIcon = m_hIcon;
	m_nIcon.uTimeout = 10000;
	m_nIcon.dwInfoFlags = NIIF_INFO | NIIF_NOSOUND;
	strcpy_s(m_nIcon.szTip, sizeof(m_nIcon.szTip), "停止中");
	Shell_NotifyIcon(NIM_ADD  , &m_nIcon);

	CFileFind finder;
	char filebuf[1024];
	BOOL bAutoPlay = FALSE;

	if (strlen(m_CmdLine) > 0)
	{
		if ( CheckDirOrFile(m_CmdLine.GetBuffer(256)) )
		{
			m_ListBox.AddString(m_CmdLine.GetBuffer(256));
			bAutoPlay = TRUE;
		}
		else
		{
			sprintf_s(filebuf,"%s\\*.mp3",m_CmdLine.GetBuffer(256));
			BOOL bWorking = finder.FindFile(filebuf);
			while (bWorking)
			{
				bWorking = finder.FindNextFile();
//				m_ListBox.InsertString(-1,finder.GetFilePath());
				m_ListBox.AddString(finder.GetFilePath());
				bAutoPlay = TRUE;
			}
			sprintf_s(filebuf,"%s\\*.wav",m_CmdLine.GetBuffer(256));
			bWorking = finder.FindFile(filebuf);
			while (bWorking)
			{
				bWorking = finder.FindNextFile();
//				m_ListBox.InsertString(-1,finder.GetFilePath());
				m_ListBox.AddString(finder.GetFilePath());
			}
			finder.Close();
		}
	}

	if (!bAutoPlay)
	{
		CStdioFile f;
		if (f.Open(RESUME_FILE_NAME, CFile::modeRead))
		{
			char name[1024];
			while (f.ReadString(name,1024) != NULL)
			{
				name[strlen(name)-1] = '\0';
				m_ListBox.InsertString(-1,name);
				bAutoPlay = TRUE;
			}
			f.Close();
		}
	}

	CoInitialize(NULL);
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
                    IID_IGraphBuilder, (void **)&pGraph);
    pGraph->QueryInterface(IID_IMediaControl, (void **)&pMediaControl);
    pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);
    pGraph->QueryInterface(IID_IMediaSeeking , (void **)&pSeek);

	if (bAutoPlay) PlayMP3(0);
	setHook(this->m_hWnd);

	while (1)
		if (m_TimerNum == SetTimer(m_TimerNum,250,NULL)) break;

	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

void CSimpleMP3PlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CSimpleMP3PlayerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CSimpleMP3PlayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSimpleMP3PlayerDlg::OnDblclkList() 
{
	PlayMP3(m_ListBox.GetCurSel());
}

BOOL CSimpleMP3PlayerDlg::CheckDirOrFile(LPCSTR fname)
{
	CString buf = fname;
	char tail[8];

	strcpy_s(tail,buf.Right(4));
	for (int i=0;i<4;i++) tail[i] = tolower(tail[i]);

	if (strcmp(tail,".mp3") == 0) return TRUE;
	else if (strcmp(tail,".wav") == 0) return TRUE;
	else return FALSE;
}

void CSimpleMP3PlayerDlg::GetFileName(LPCSTR fname,LPCSTR buffer)
{
	int counter = 0;

	memset((char*)buffer,0,sizeof(buffer));
	for (int i=0;i<(int)strlen(fname);i++)
	{
		if (*(fname+i) == '\\')
		{
			memset((char*)buffer,0,sizeof(buffer));
			counter = 0;
		}
		else
		{
			if (
				( (unsigned char)(*(fname+i)) >= 0x81 && ((unsigned char)(*(fname+i)) <= 0x9f) ) ||
				( (unsigned char)(*(fname+i)) >= 0xe0 && ((unsigned char)(*(fname+i)) <= 0xfc) )
			   )
			{
				::strncpy_s((char*)(buffer+counter),sizeof(buffer),(const char*)fname+i,1);
				counter ++; i++;
				::strncpy_s((char*)(buffer+counter),sizeof(buffer),(const char*)fname+i,1);
				counter ++;
			}
			else
			{
				::strncpy_s((char*)(buffer+counter),sizeof(buffer),(const char*)fname+i,1);
				counter ++;
			}
		}
	}
//	*((char*)(buffer+counter)) = '\0';
	*((char*)(buffer+counter-4)) = '\0';
}

LRESULT CSimpleMP3PlayerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    switch (message)
	{
        case WM_DROPFILES:
		{
			int count = DragQueryFile((HDROP)wParam,0xFFFFFFFF,NULL,0);
			for (int i=0;i<count;i++)
			{
				CFileFind finder;
				char dirbuf[1024],filebuf[1024];

				DragQueryFile((HDROP)wParam,i,dirbuf,sizeof(dirbuf));

				if (CheckDirOrFile(dirbuf))
				{
					m_ListBox.InsertString(-1,dirbuf);
				}
				else
				{
					sprintf_s(filebuf,"%s\\*.mp3",dirbuf);
					BOOL bWorking = finder.FindFile(filebuf);
					while (bWorking)
					{
						bWorking = finder.FindNextFile();
//						m_ListBox.InsertString(-1,finder.GetFilePath());
						m_ListBox.AddString(finder.GetFilePath());
					}
					sprintf_s(filebuf,"%s\\*.wav",dirbuf);
					bWorking = finder.FindFile(filebuf);
					while (bWorking)
					{
						bWorking = finder.FindNextFile();
//						m_ListBox.InsertString(-1,finder.GetFilePath());
						m_ListBox.AddString(finder.GetFilePath());
					}
					finder.Close();
				}
			}
			break;
		}
	    case MY_NOTIFYICON:
		{
	        switch (lParam)
			{
		        case WM_RBUTTONDOWN:
					POINT p; GetCursorPos((LPPOINT)(&p));
					SetForegroundWindow();
					m_pPopup->TrackPopupMenu(TPM_RIGHTALIGN,p.x,p.y,AfxGetMainWnd());
			        break;
		        case WM_LBUTTONDOWN:
					SetShowDialog(TRUE);
			        break;
	        }
	        break;
		}
	}

	return CDialog::WindowProc(message, wParam, lParam);
}

BOOL CSimpleMP3PlayerDlg::DestroyWindow() 
{
	CFile f;
	f.Open(RESUME_FILE_NAME,CFile::modeCreate | CFile::modeWrite);
	for (int i=0;i<m_ListBox.GetCount();i++)
	{
		CString name;
		m_ListBox.GetText(i,(CString&)name);
		f.Write(name.GetBuffer(name.GetLength()),name.GetLength());
		f.Write("\r\n",2);
	}
	f.Close();

	KillTimer(m_TimerNum);
	Shell_NotifyIcon(NIM_DELETE  , &m_nIcon);

	return CDialog::DestroyWindow();
}

void CSimpleMP3PlayerDlg::SetShowDialog(BOOL b)
{
	m_bDlgShow = b;
	if (b) { ShowWindow(SW_SHOW); SetForegroundWindow(); } else ShowWindow(SW_HIDE);
}

void CSimpleMP3PlayerDlg::OnWindowclose() 
{
	SetShowDialog(FALSE);
}

BOOL CSimpleMP3PlayerDlg::PlayMP3(int nCount)
{
	LONGLONG pCurrent,pStop;
    long evCode;
	char filebuf[1024];

    pMediaControl->Stop();
	pCurrent = 0;
	pStop = 1;
	pSeek->SetPositions (&pCurrent,AM_SEEKING_AbsolutePositioning,&pStop,AM_SEEKING_AbsolutePositioning);
    pEvent->WaitForCompletion(INFINITE, &evCode);

    pMediaControl->Release();
    pEvent->Release();
    pGraph->Release();
    CoUninitialize();

	CoInitialize(NULL);
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
                    IID_IGraphBuilder, (void **)&pGraph);
    pGraph->QueryInterface(IID_IMediaControl, (void **)&pMediaControl);
    pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);
    pGraph->QueryInterface(IID_IMediaSeeking , (void **)&pSeek);

	m_ListBox.GetText(nCount,(CString&)m_PlayingFileName);
	int len = m_PlayingFileName.GetLength();
	WCHAR *fname = new WCHAR[len];
	MultiByteToWideChar( GetACP(),MB_PRECOMPOSED,m_PlayingFileName.GetBuffer(len),-1,fname,sizeof(WCHAR) * len);
	pGraph->RenderFile(fname, NULL);
	delete fname;

	pMediaControl->Run();

	m_nPlayingNumber = nCount;
	m_ListBox.SetCurSel(m_nPlayingNumber);

	pSeek->GetPositions (&pCurrent,&pStop);
	m_Slider.SetRangeMax((int)(pStop/1000000));
	m_Slider.SetPos((int)(pCurrent/1000000));
	m_Slider.SetPageSize(50);

	GetFileName(m_PlayingFileName.GetBuffer(1024),filebuf);
	strcpy_s(m_nIcon.szInfoTitle, sizeof(m_nIcon.szInfoTitle),"再生中のファイル");
	strcpy_s(m_nIcon.szInfo, filebuf);
	m_nIcon.cbSize = NOTIFYICONDATA_V2_SIZE;
	m_nIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_INFO;
	m_nIcon.uTimeout = 10000;
	m_nIcon.dwInfoFlags = NIIF_INFO | NIIF_NOSOUND;

	Shell_NotifyIcon(NIM_MODIFY , &m_nIcon);

	return TRUE;
}

void CSimpleMP3PlayerDlg::OnPlay() 
{
	if (m_ListBox.GetCurSel() == LB_ERR)
	{
		int ret = m_ListBox.GetCount();
		if (m_ListBox.GetCount() > 0)
		{
			if (m_nPlayingNumber == -1)
				PlayMP3(0);
			else
				PlayMP3(m_nPlayingNumber);
		}
	}
	else
	{
		PlayMP3(m_ListBox.GetCurSel());
	}
}

void CSimpleMP3PlayerDlg::OnBefore() 
{
	if (m_ListBox.GetCount() == 0) return;
	if (m_nPlayingNumber == -1) m_nPlayingNumber = m_nResumePlayNumber;
	if (--m_nPlayingNumber < 0) m_nPlayingNumber = m_ListBox.GetCount()-1;
	PlayMP3(m_nPlayingNumber);
}

void CSimpleMP3PlayerDlg::OnNext() 
{
	if (m_ListBox.GetCount() == 0) return;
	if (m_nPlayingNumber == -1) m_nPlayingNumber = m_nResumePlayNumber;
	if (++m_nPlayingNumber >= m_ListBox.GetCount()) m_nPlayingNumber = 0;
	PlayMP3(m_nPlayingNumber);
}

void CSimpleMP3PlayerDlg::OnStop() 
{
	LONGLONG pCurrent,pStop;
    long evCode;

    pMediaControl->Stop();
	pCurrent = 0;
	pStop = 1;
	pSeek->SetPositions (&pCurrent,AM_SEEKING_AbsolutePositioning,&pStop,AM_SEEKING_AbsolutePositioning);
    pEvent->WaitForCompletion(INFINITE, &evCode);
	m_Slider.SetPos(0);

	strcpy_s(m_nIcon.szTip, sizeof(m_nIcon.szTip),"停止中");
	Shell_NotifyIcon(NIM_MODIFY , &m_nIcon);

	m_Status = VERSION_INFO;
	m_Timer = _T("停止");
	UpdateData(FALSE);

	m_nIcon.uFlags = NIF_ICON | NIF_MESSAGE;
	m_nIcon.uTimeout = 10000;
	m_nIcon.dwInfoFlags = NIIF_INFO | NIIF_NOSOUND;
	m_nIcon.dwInfoFlags = 0;

	Shell_NotifyIcon(NIM_MODIFY , &m_nIcon);

	m_nResumePlayNumber = m_nPlayingNumber;
	m_nPlayingNumber = -1;
}

void CSimpleMP3PlayerDlg::OnDelete() 
{
	int sel = m_ListBox.GetCurSel();
	if (sel != LB_ERR)
	{
		m_ListBox.DeleteString(sel);
	}
	if (sel >= m_ListBox.GetCount()) sel = m_ListBox.GetCount() - 1;
	m_ListBox.SetCurSel(sel);
}

void CSimpleMP3PlayerDlg::OnDeleteAll() 
{
	m_ListBox.ResetContent();
}

#ifdef _WIN64
void CSimpleMP3PlayerDlg::OnTimer(UINT_PTR nIDEvent) 
#else
void CSimpleMP3PlayerDlg::OnTimer(UINT nIDEvent) 
#endif
{
	LONGLONG pCurrent,pStop;
	char filebuf[1024],timebuf[16],tmpbuf[2048];

	if (m_nPlayingNumber != -1)
	{
		pSeek->GetPositions (&pCurrent,&pStop);

		if (pCurrent == pStop)
		{
			if ((m_ListBox.GetCount()) > ++m_nPlayingNumber)
			{
				PlayMP3(m_nPlayingNumber);
			}
			else
			{
				if (m_ListBox.GetCount() == 0)
				{
					OnStop();
				}
				else PlayMP3(0);
			}
		}
		else
		{
			int t = (int)(pCurrent / 10000000);

			GetFileName(m_PlayingFileName.GetBuffer(1024),filebuf);
			sprintf_s(timebuf,"%02d:%02d",t/60,t%60);
			sprintf_s(tmpbuf,"%s [%s]",filebuf,timebuf);
			tmpbuf[60] = '\0';
			strcpy_s(m_nIcon.szTip, sizeof(m_nIcon.szTip),tmpbuf);
			m_nIcon.cbSize = NOTIFYICONDATA_V2_SIZE;
			m_nIcon.uFlags = NIF_TIP;

			Shell_NotifyIcon(NIM_MODIFY , &m_nIcon);

			pSeek->GetPositions (&pCurrent,&pStop);
			if ( abs((int)(pCurrent/1000000) - m_Slider.GetPos()) < 50 )
			{
				m_Slider.SetPos((int)(pCurrent/1000000));
			}
			else
			{
				sprintf_s(timebuf,"%02d:%02d",m_Slider.GetPos()/600,(m_Slider.GetPos()/10)%60);
			}
			m_Status = filebuf;
			m_Timer  = timebuf;
			UpdateData(FALSE);
		}
	}

	if (IsUpdate())
	{
		switch(getKeyCD())
		{
			case VK_MEDIA_NEXT_TRACK:
				OnNext();
				break;
			case VK_MEDIA_PREV_TRACK:
				OnBefore();
				break;
			case VK_MEDIA_STOP:
				OnStop();
				break;
			case VK_MEDIA_PLAY_PAUSE:
				OnPlay();
				break;
			default:
				break;
		}
	}

	CDialog::OnTimer(nIDEvent);
}

void CSimpleMP3PlayerDlg::OnMoveUp() 
{
	int CurSel = m_ListBox.GetCurSel();
	CString name1,name2;

	if (CurSel != LB_ERR)
	{
		if ( CurSel-1 >= 0 )
		{
			m_ListBox.GetText(CurSel  ,(CString&)name1);
			m_ListBox.GetText(CurSel-1,(CString&)name2);
			m_ListBox.DeleteString(CurSel);
			m_ListBox.InsertString(CurSel  ,name2.GetBuffer(256));
			m_ListBox.DeleteString(CurSel-1);
			m_ListBox.InsertString(CurSel-1,name1.GetBuffer(256));
			m_ListBox.SetCurSel(CurSel-1);
		}
		else
		{
			m_ListBox.GetText(CurSel,(CString&)name1);
			m_ListBox.DeleteString(CurSel);
			m_ListBox.InsertString(m_ListBox.GetCount(),name1.GetBuffer(256));
			m_ListBox.SetCurSel(m_ListBox.GetCount()-1);
		}
	}
}

void CSimpleMP3PlayerDlg::OnMoveBottom() 
{
	int CurSel = m_ListBox.GetCurSel();
	CString name1,name2;

	if (CurSel != LB_ERR)
	{
		if ( m_ListBox.GetCount() > CurSel+1 )
		{
			m_ListBox.GetText(CurSel  ,(CString&)name1);
			m_ListBox.GetText(CurSel+1,(CString&)name2);
			m_ListBox.DeleteString(CurSel);
			m_ListBox.InsertString(CurSel  ,name2.GetBuffer(256));
			m_ListBox.DeleteString(CurSel+1);
			m_ListBox.InsertString(CurSel+1,name1.GetBuffer(256));
			m_ListBox.SetCurSel(CurSel+1);
		}
		else
		{
			m_ListBox.GetText(CurSel,(CString&)name1);
			m_ListBox.DeleteString(CurSel);
			m_ListBox.InsertString(0,name1.GetBuffer(256));
			m_ListBox.SetCurSel(0);
		}
	}
}

void CSimpleMP3PlayerDlg::OnReleasedcaptureSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LONGLONG pCurrent,pStop;

	pSeek->GetPositions (&pCurrent,&pStop);
	pCurrent = m_Slider.GetPos() * (LONGLONG)1000000;
	pSeek->SetPositions (&pCurrent,AM_SEEKING_AbsolutePositioning,&pStop,AM_SEEKING_AbsolutePositioning);
	m_Slider.SetPos((int)(pCurrent/1000000));

	*pResult = 0;
}

void CSimpleMP3PlayerDlg::OnBnClickedPreset()
{
	CMemSelect dlg;

	if (dlg.DoModal() == IDOK)
	{
		CFile f;
		
		switch (dlg.m_MemSelect)
		{
			case 0:
				f.Open(MEM_FILE_NAME1,CFile::modeCreate | CFile::modeWrite);
				break;
			case 1:
				f.Open(MEM_FILE_NAME2,CFile::modeCreate | CFile::modeWrite);
				break;
			case 2:
				f.Open(MEM_FILE_NAME3,CFile::modeCreate | CFile::modeWrite);
				break;
			case 3:
				f.Open(MEM_FILE_NAME4,CFile::modeCreate | CFile::modeWrite);
				break;
			case 4:
				f.Open(MEM_FILE_NAME5,CFile::modeCreate | CFile::modeWrite);
				break;
		}

		for (int i=0;i<m_ListBox.GetCount();i++)
		{
			CString name;
			m_ListBox.GetText(i,(CString&)name);
			f.Write(name.GetBuffer(name.GetLength()),name.GetLength());
			f.Write("\r\n",2);
		}
		f.Close();
	}
}

void CSimpleMP3PlayerDlg::OnBnClickedCh1()
{
	char tmp[256];
	sprintf_s(tmp,"%s",MEM_FILE_NAME1);
	MemFileRead(tmp);
}

void CSimpleMP3PlayerDlg::OnBnClickedCh2()
{
	char tmp[256];
	sprintf_s(tmp,"%s",MEM_FILE_NAME2);
	MemFileRead(tmp);
}

void CSimpleMP3PlayerDlg::OnBnClickedCh3()
{
	char tmp[256];
	sprintf_s(tmp,"%s",MEM_FILE_NAME3);
	MemFileRead(tmp);
}

void CSimpleMP3PlayerDlg::OnBnClickedCh4()
{
	char tmp[256];
	sprintf_s(tmp,"%s",MEM_FILE_NAME4);
	MemFileRead(tmp);
}

void CSimpleMP3PlayerDlg::OnBnClickedCh5()
{
	char tmp[256];
	sprintf_s(tmp,"%s",MEM_FILE_NAME5);
	MemFileRead(tmp);
}

bool CSimpleMP3PlayerDlg::MemFileRead(char *fname)
{
	CStdioFile f;

	if (f.Open(fname, CFile::modeRead))
	{
		OnStop();
		OnDeleteAll();
		char name[1024];
		while (f.ReadString(name,1024) != NULL)
		{
			name[strlen(name)-1] = '\0';
			m_ListBox.InsertString(-1,name);
		}
		f.Close();
		PlayMP3(0);
	}
	else
	{
		return false;
	}

	return true;
}
