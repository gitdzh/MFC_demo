// TipDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3_MFCTemp.h"
#include "TipDlg.h"
#include "afxdialogex.h"


// CTipDlg �Ի���

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


// CTipDlg ��Ϣ�������


BOOL CTipDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_hIconLedRed = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICONRED), IMAGE_ICON, 20, 20, LR_DEFAULTCOLOR);
	m_hIconLedGreen = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICONGREEN), IMAGE_ICON, 20, 20, LR_DEFAULTCOLOR);
	m_1.SetIcon(m_hIconLedGreen);
	m_2.SetIcon(m_hIconLedRed);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
