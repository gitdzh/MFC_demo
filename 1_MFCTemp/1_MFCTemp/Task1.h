#pragma once
#include "afxwin.h"


// CTask1 对话框

class CTask1 : public CDialogEx
{
	DECLARE_DYNAMIC(CTask1)

public:
	CTask1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTask1();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CButton m_1;
	CButton m_2;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedButton4();
};
