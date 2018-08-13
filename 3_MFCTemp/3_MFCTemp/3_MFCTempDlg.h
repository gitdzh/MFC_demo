
// 3_MFCTempDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include "TipDlg.h"
using namespace cv;
// CMy3_MFCTempDlg 对话框
class CMy3_MFCTempDlg : public CDialogEx
{
// 构造
public:
	CMy3_MFCTempDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CMy3_MFCTempDlg();
// 对话框数据
	enum { IDD = IDD_MY3_MFCTEMP_DIALOG };

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
	CStatic m_Menu3;
	HICON m_hIcon1, m_hIcon2, m_hIcon3;

	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	CButton m_picture1;
	CButton m_picture2;
	CButton m_picture3;
	CButton m_picture4;

	afx_msg void OnBnClickedButton3();
	afx_msg void OnClickedButton4();

	//HICON m_hIconLedRed, m_hIconLedGreen;
	//CStatic m_DIP1;
	//CStatic m_DIP2;
	//CStatic m_DIP3;
	//CStatic m_DIP4;
	//CStatic m_DIP5;
	//CStatic m_DIP6;
	//CStatic m_DIP7;
	//CStatic m_DIP8;
	//CStatic m_DIP9;
	//CStatic m_DIP10;
	//CStatic m_DIP11;
	//CStatic m_DIP12;

	//Mat morphology(Mat &g_threImage);
	//void findpoint(Mat &g_morphImage);
	//void move(Mat &g_srcImage);
	//void rotate(Mat &g_moveImage);
	//void DIPImage(Mat &g_rotateImage);
	//void judgestatus(Mat &g_switchImage);
	CButton m_picture5;
	CButton m_picture6;
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedButton2();

	CButtonST m_btnload,m_btnidentify;

	CTipDlg  *m_pTipDlg;
	afx_msg void OnBnClickedButton1();
//	CEdit m_edit1;
//	CEdit m_edit2;
	int m_edit1;
	int m_edit2;
	CEdit m_edit11;
	CEdit m_edit22;
};
