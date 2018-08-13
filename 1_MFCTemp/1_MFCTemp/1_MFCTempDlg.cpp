
// 1_MFCTempDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "1_MFCTemp.h"
#include "1_MFCTempDlg.h"
#include "afxdialogex.h"
#include<iostream>
#include "Task1.h"
#include "Task2.h"
#include "Task3.h"
#include "Task4.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CMy1_MFCTempDlg 对话框



CMy1_MFCTempDlg::CMy1_MFCTempDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy1_MFCTempDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy1_MFCTempDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_Menu1);
	DDX_Control(pDX, IDC_BUTTON1, m_Menu2);
	DDX_Control(pDX, IDC_BUTTON2, m_Menu3);
	DDX_Control(pDX, IDC_BUTTON17, m_Menu4);
}

BEGIN_MESSAGE_MAP(CMy1_MFCTempDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_BUTTON2, &CMy1_MFCTempDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy1_MFCTempDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMy1_MFCTempDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMy1_MFCTempDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMy1_MFCTempDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CMy1_MFCTempDlg 消息处理程序

BOOL CMy1_MFCTempDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_hIcon1 = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICONTITLE), IMAGE_ICON, 219, 46, LR_DEFAULTCOLOR);
	m_hIcon2 = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICONHELP), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	m_hIcon3 = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICONEXIT), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	m_hIcon4 = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICONREDO), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	m_Menu1.SetIcon(m_hIcon1);
	m_Menu2.SetIcon(m_hIcon2);
	m_Menu3.SetIcon(m_hIcon3);
	m_Menu4.SetIcon(m_hIcon4);

	m_task1.SubclassDlgItem(IDC_BUTTON3, this);
	m_task1.SetIcon(IDI_ICON1);
	m_task1.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_task2.SubclassDlgItem(IDC_BUTTON4, this);
	m_task2.SetIcon(IDI_ICON2);
	m_task2.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_task3.SubclassDlgItem(IDC_BUTTON5, this);
	m_task3.SetIcon(IDI_ICON3);
	m_task3.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_task4.SubclassDlgItem(IDC_BUTTON6, this);
	m_task4.SetIcon(IDI_ICON4);
	m_task4.SetAlign(CButtonST::ST_ALIGN_VERT);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy1_MFCTempDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy1_MFCTempDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMy1_MFCTempDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	CMy1_MFCTempDlg::OnCancel();
}


void CMy1_MFCTempDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	INT_PTR nRes;             // 用于保存DoModal函数的返回值   

	CTask1 tipDlg;           // 构造对话框类CTipDlg的实例   
	nRes = tipDlg.DoModal();  // 弹出对话框   
	if (IDCANCEL == nRes)     // 判断对话框退出后返回值是否为IDCANCEL，如果是则return，否则继续向下执行   
		return;
}


void CMy1_MFCTempDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	INT_PTR nRes;             // 用于保存DoModal函数的返回值   

	CTask2 tipDlg;           // 构造对话框类CTipDlg的实例   
	nRes = tipDlg.DoModal();  // 弹出对话框   
	if (IDCANCEL == nRes)     // 判断对话框退出后返回值是否为IDCANCEL，如果是则return，否则继续向下执行   
		return;
}


void CMy1_MFCTempDlg::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码
	INT_PTR nRes;             // 用于保存DoModal函数的返回值   

	CTask3 tipDlg;           // 构造对话框类CTipDlg的实例   
	nRes = tipDlg.DoModal();  // 弹出对话框   
	if (IDCANCEL == nRes)     // 判断对话框退出后返回值是否为IDCANCEL，如果是则return，否则继续向下执行   
		return;
}


void CMy1_MFCTempDlg::OnBnClickedButton6()
{
	// TODO:  在此添加控件通知处理程序代码
	INT_PTR nRes;             // 用于保存DoModal函数的返回值   

	CTask4 tipDlg;           // 构造对话框类CTipDlg的实例   
	nRes = tipDlg.DoModal();  // 弹出对话框   
	if (IDCANCEL == nRes)     // 判断对话框退出后返回值是否为IDCANCEL，如果是则return，否则继续向下执行   
		return;
}
