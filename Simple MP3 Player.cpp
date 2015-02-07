// Simple MP3 Player.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "Simple MP3 Player.h"
#include "Simple MP3 PlayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimpleMP3PlayerApp

BEGIN_MESSAGE_MAP(CSimpleMP3PlayerApp, CWinApp)
	//{{AFX_MSG_MAP(CSimpleMP3PlayerApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleMP3PlayerApp クラスの構築

CSimpleMP3PlayerApp::CSimpleMP3PlayerApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CSimpleMP3PlayerApp オブジェクト

CSimpleMP3PlayerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSimpleMP3PlayerApp クラスの初期化

BOOL CSimpleMP3PlayerApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さくしたけ
	//  れば以下の特定の初期化ルーチンの中から不必要なものを削除して
	//  ください。

	// アプリケーションの二重起動防止
	::CreateMutex(NULL, TRUE, m_pszExeName);
	if( GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CWnd* pWnd = CWnd::FindWindow(NULL,"Denka's Simple MP3 Player");
		if( pWnd ) pWnd->SetForegroundWindow();
	}
	else
	{
		CCommandLineInfo cmdInfo;
		ParseCommandLine(cmdInfo);
//		AfxMessageBox(cmdInfo.m_strFileName);

		CSimpleMP3PlayerDlg dlg;
		m_pMainWnd = &dlg;

		if (cmdInfo.m_strFileName != "")
			dlg.m_CmdLine += cmdInfo.m_strFileName;
		int nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
			// TODO: ダイアログが <OK> で消された時のコードを
			//       記述してください。
		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: ダイアログが <ｷｬﾝｾﾙ> で消された時のコードを
			//       記述してください。
		}
	}
	// ダイアログが閉じられてからアプリケーションのメッセージ ポンプを開始するよりは、
	// アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}
