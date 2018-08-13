
// 1_MFCTempDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CMy1_MFCTempDlg 对话框
class CMy1_MFCTempDlg : public CDialogEx
{
// 构造
public:
	CMy1_MFCTempDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY1_MFCTEMP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_Menu1;
	CButton m_Menu2;
	CButton m_Menu3;
	HICON m_hIcon1, m_hIcon2, m_hIcon3, m_hIcon4;
	CButton m_Menu4;

	afx_msg void OnBnClickedButton2();

	CButtonST m_task1;
	CButtonST m_task2;
	CButtonST m_task3;
	CButtonST m_task4;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};
