#pragma once


// CTask2 对话框

class CTask2 : public CDialogEx
{
	DECLARE_DYNAMIC(CTask2)

public:
	CTask2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTask2();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

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
