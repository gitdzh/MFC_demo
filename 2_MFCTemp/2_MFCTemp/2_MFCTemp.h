
// 2_MFCTemp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy2_MFCTempApp: 
// �йش����ʵ�֣������ 2_MFCTemp.cpp
//

class CMy2_MFCTempApp : public CWinApp
{
public:
	CMy2_MFCTempApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy2_MFCTempApp theApp;