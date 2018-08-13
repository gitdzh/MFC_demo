#pragma once


// CTask3 对话框

class CTask3 : public CDialogEx
{
	DECLARE_DYNAMIC(CTask3)

public:
	CTask3(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTask3();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
