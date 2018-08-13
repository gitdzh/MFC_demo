// TipDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3_MFCTemp.h"
#include "TipDlg.h"
#include "afxdialogex.h"


// CTipDlg 对话框

IMPLEMENT_DYNAMIC(CTipDlg, CDialogEx)

CTipDlg::CTipDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTipDlg::IDD, pParent)
{

}

CTipDlg::~CTipDlg()
{
}

void CTipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_1);
	DDX_Control(pDX, IDC_STATIC2, m_2);
}


BEGIN_MESSAGE_MAP(CTipDlg, CDialogEx)
END_MESSAGE_MAP()


// CTipDlg 消息处理程序


BOOL CTipDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_hIconLedRed = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICONRED), IMAGE_ICON, 20, 20, LR_DEFAULTCOLOR);
	m_hIconLedGreen = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICONGREEN), IMAGE_ICON, 20, 20, LR_DEFAULTCOLOR);
	m_1.SetIcon(m_hIconLedGreen);
	m_2.SetIcon(m_hIconLedRed);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
