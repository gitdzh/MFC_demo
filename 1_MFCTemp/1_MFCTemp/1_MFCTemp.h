
// 1_MFCTemp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy1_MFCTempApp: 
// �йش����ʵ�֣������ 1_MFCTemp.cpp
//

class CMy1_MFCTempApp : public CWinApp
{
public:
	CMy1_MFCTempApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy1_MFCTempApp theApp;