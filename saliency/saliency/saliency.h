
// saliency.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CsaliencyApp:
// �йش����ʵ�֣������ saliency.cpp
//

class CsaliencyApp : public CWinAppEx
{
public:
	CsaliencyApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CsaliencyApp theApp;