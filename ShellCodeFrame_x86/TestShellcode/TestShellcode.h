
// TestShellcode.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestShellcodeApp:
// �йش����ʵ�֣������ TestShellcode.cpp
//

class CTestShellcodeApp : public CWinAppEx
{
public:
	CTestShellcodeApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestShellcodeApp theApp;