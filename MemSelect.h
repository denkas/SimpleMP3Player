#pragma once


// CMemSelect ダイアログ

class CMemSelect : public CDialog
{
	DECLARE_DYNAMIC(CMemSelect)

public:
	CMemSelect(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CMemSelect();

// ダイアログ データ
	enum { IDD = IDD_MEMDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int m_MemSelect;
};
