#pragma once
#include "afxwin.h"


// CTask1 �Ի���

class CTask1 : public CDialogEx
{
	DECLARE_DYNAMIC(CTask1)

public:
	CTask1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTask1();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
