
// 3_MFCTemp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy3_MFCTempApp: 
// �йش����ʵ�֣������ 3_MFCTemp.cpp
//

class CMy3_MFCTempApp : public CWinApp
{
public:
	CMy3_MFCTempApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy3_MFCTempApp theApp;