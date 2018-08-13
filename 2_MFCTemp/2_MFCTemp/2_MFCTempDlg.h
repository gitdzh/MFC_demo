
// 2_MFCTempDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\core\core.hpp>
#include "TipDlg.h"
// CMy2_MFCTempDlg �Ի���
class CMy2_MFCTempDlg : public CDialogEx
{
// ����
public:
	CMy2_MFCTempDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CMy2_MFCTempDlg();
// �Ի�������
	enum { IDD = IDD_MY2_MFCTEMP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// �˵���Ա
	CButton m_Menu1;
	CButton m_Menu2;
	CButton m_Menu3;
	HICON m_hIcon1, m_hIcon2, m_hIcon3;
	CTipDlg  *m_pTipDlg;
	// ��ť��Ա
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
