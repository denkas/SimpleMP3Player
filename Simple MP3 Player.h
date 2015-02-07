// Simple MP3 Player.h : SIMPLE MP3 PLAYER アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_SIMPLEMP3PLAYER_H__A6F09964_BEC7_4D52_8D46_ED98EA48DC4A__INCLUDED_)
#define AFX_SIMPLEMP3PLAYER_H__A6F09964_BEC7_4D52_8D46_ED98EA48DC4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル

/////////////////////////////////////////////////////////////////////////////
// CSimpleMP3PlayerApp:
// このクラスの動作の定義に関しては Simple MP3 Player.cpp ファイルを参照してください。
//

class CSimpleMP3PlayerApp : public CWinApp
{
public:
	CSimpleMP3PlayerApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CSimpleMP3PlayerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CSimpleMP3PlayerApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SIMPLEMP3PLAYER_H__A6F09964_BEC7_4D52_8D46_ED98EA48DC4A__INCLUDED_)
