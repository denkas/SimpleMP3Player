// Simple MP3 Player.h : SIMPLE MP3 PLAYER �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_SIMPLEMP3PLAYER_H__A6F09964_BEC7_4D52_8D46_ED98EA48DC4A__INCLUDED_)
#define AFX_SIMPLEMP3PLAYER_H__A6F09964_BEC7_4D52_8D46_ED98EA48DC4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CSimpleMP3PlayerApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� Simple MP3 Player.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CSimpleMP3PlayerApp : public CWinApp
{
public:
	CSimpleMP3PlayerApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSimpleMP3PlayerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CSimpleMP3PlayerApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SIMPLEMP3PLAYER_H__A6F09964_BEC7_4D52_8D46_ED98EA48DC4A__INCLUDED_)
