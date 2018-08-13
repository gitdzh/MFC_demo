#pragma once


// CTask4 对话框

class CTask4 : public CDialogEx
{
	DECLARE_DYNAMIC(CTask4)

public:
	CTask4(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTask4();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
