#pragma once


// CTask2 �Ի���

class CTask2 : public CDialogEx
{
	DECLARE_DYNAMIC(CTask2)

public:
	CTask2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTask2();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
