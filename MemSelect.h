#pragma once


// CMemSelect �_�C�A���O

class CMemSelect : public CDialog
{
	DECLARE_DYNAMIC(CMemSelect)

public:
	CMemSelect(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CMemSelect();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_MEMDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int m_MemSelect;
};
