; CLW ファイルは MFC ClassWizard の情報を含んでいます。

[General Info]
Version=1
LastClass=CSimpleMP3PlayerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Simple MP3 Player.h"

ClassCount=3
Class1=CSimpleMP3PlayerApp
Class2=CSimpleMP3PlayerDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SIMPLEMP3PLAYER_DIALOG
Resource4=IDR_MENU

[CLS:CSimpleMP3PlayerApp]
Type=0
HeaderFile=Simple MP3 Player.h
ImplementationFile=Simple MP3 Player.cpp
Filter=N
LastObject=CSimpleMP3PlayerApp

[CLS:CSimpleMP3PlayerDlg]
Type=0
HeaderFile=Simple MP3 PlayerDlg.h
ImplementationFile=Simple MP3 PlayerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CSimpleMP3PlayerDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=Simple MP3 PlayerDlg.h
ImplementationFile=Simple MP3 PlayerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SIMPLEMP3PLAYER_DIALOG]
Type=1
Class=CSimpleMP3PlayerDlg
ControlCount=19
Control1=IDC_LIST,listbox,1353781251
Control2=IDC_PLAY,button,1342242817
Control3=IDC_STOP,button,1342242816
Control4=IDC_WINDOWCLOSE,button,1342242816
Control5=IDC_STATUS,static,1342312960
Control6=IDC_DELETE_ALL,button,1342242816
Control7=IDC_DELETE,button,1342242816
Control8=IDC_TIME,static,1342312961
Control9=IDC_NEXT,button,1342242816
Control10=IDC_BEFORE,button,1342242816
Control11=IDC_MOVE_UP,button,1342242816
Control12=IDC_MOVE_BOTTOM,button,1342242816
Control13=IDC_SLIDER,msctls_trackbar32,1342242840
Control14=IDC_CH1,button,1342242816
Control15=IDC_CH2,button,1342242816
Control16=IDC_CH3,button,1342242816
Control17=IDC_CH4,button,1342242816
Control18=IDC_CH5,button,1342242816
Control19=IDC_PRESET,button,1342242816

[MNU:IDR_MENU]
Type=1
Class=?
Command1=IDC_PLAY
Command2=IDC_BEFORE
Command3=IDC_NEXT
Command4=IDC_STOP
Command5=IDOK
CommandCount=5

