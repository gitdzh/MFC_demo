#pragma once
#include "afxwin.h"


// CTipDlg 对话框

class CTipDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTipDlg)

public:
	CTipDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTipDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_1;
	CStatic m_2;
	virtual BOOL OnInitDialog();
	HICON m_hIconLedRed, m_hIconLedGreen;
};
