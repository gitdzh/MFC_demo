
// 2_MFCTempDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\core\core.hpp>
#include "TipDlg.h"
// CMy2_MFCTempDlg 对话框
class CMy2_MFCTempDlg : public CDialogEx
{
// 构造
public:
	CMy2_MFCTempDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CMy2_MFCTempDlg();
// 对话框数据
	enum { IDD = IDD_MY2_MFCTEMP_DIALOG };

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
	// 菜单成员
	CButton m_Menu1;
	CButton m_Menu2;
	CButton m_Menu3;
	HICON m_hIcon1, m_hIcon2, m_hIcon3;
	CTipDlg  *m_pTipDlg;
	// 按钮成员
	CButtonST m_btnload;
	CButtonST m_btngaussian;
	CButtonST m_btnfindcenterline;

	afx_msg void OnBnClickedButtonexit();
	afx_msg void OnBnClickedButtonload();
	afx_msg void OnBnClickedButtongaussian();
	afx_msg void OnBnClickedButtonfindcenterline();
	CStatic m_title;
	afx_msg void OnBnClickedButtonhelp();
	CStatic m_Menu4;
};
