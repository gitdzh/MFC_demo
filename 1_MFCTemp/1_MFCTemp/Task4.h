#pragma once


// CTask4 �Ի���

class CTask4 : public CDialogEx
{
	DECLARE_DYNAMIC(CTask4)

public:
	CTask4(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTask4();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
