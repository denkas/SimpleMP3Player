// MemSelect.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "Simple MP3 Player.h"
#include "MemSelect.h"


// CMemSelect �_�C�A���O

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


// CMemSelect ���b�Z�[�W �n���h��

void CMemSelect::OnBnClickedOk()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	UpdateData(true);
	OnOK();
}
