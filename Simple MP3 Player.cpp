// Simple MP3 Player.cpp : �A�v���P�[�V�����p�N���X�̒�`���s���܂��B
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
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleMP3PlayerApp �N���X�̍\�z

CSimpleMP3PlayerApp::CSimpleMP3PlayerApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CSimpleMP3PlayerApp �I�u�W�F�N�g

CSimpleMP3PlayerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSimpleMP3PlayerApp �N���X�̏�����

BOOL CSimpleMP3PlayerApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// �W���I�ȏ���������
	// ���������̋@�\���g�p�����A���s�t�@�C���̃T�C�Y��������������
	//  ��Έȉ��̓���̏��������[�`���̒�����s�K�v�Ȃ��̂��폜����
	//  ���������B

	// �A�v���P�[�V�����̓�d�N���h�~
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
			// TODO: �_�C�A���O�� <OK> �ŏ����ꂽ���̃R�[�h��
			//       �L�q���Ă��������B
		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: �_�C�A���O�� <��ݾ�> �ŏ����ꂽ���̃R�[�h��
			//       �L�q���Ă��������B
		}
	}
	// �_�C�A���O�������Ă���A�v���P�[�V�����̃��b�Z�[�W �|���v���J�n������́A
	// �A�v���P�[�V�������I�����邽�߂� FALSE ��Ԃ��Ă��������B
	return FALSE;
}
