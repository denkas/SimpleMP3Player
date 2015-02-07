// MemSelect.cpp : 実装ファイル
//

#include "stdafx.h"
#include "Simple MP3 Player.h"
#include "MemSelect.h"


// CMemSelect ダイアログ

IMPLEMENT_DYNAMIC(CMemSelect, CDialog)

CMemSelect::CMemSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CMemSelect::IDD, pParent)
	, m_MemSelect(0)
{
}

CMemSelect::~CMemSelect()
{
}

void CMemSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_MemSelect);
}


BEGIN_MESSAGE_MAP(CMemSelect, CDialog)
	ON_BN_CLICKED(IDOK, &CMemSelect::OnBnClickedOk)
END_MESSAGE_MAP()


// CMemSelect メッセージ ハンドラ

void CMemSelect::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	UpdateData(true);
	OnOK();
}
