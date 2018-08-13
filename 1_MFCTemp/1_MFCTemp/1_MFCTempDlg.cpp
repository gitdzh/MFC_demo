
// 1_MFCTempDlg.cpp : ʵ���ļ�
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



// CMy1_MFCTempDlg �Ի���



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


// CMy1_MFCTempDlg ��Ϣ�������

BOOL CMy1_MFCTempDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
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
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy1_MFCTempDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy1_MFCTempDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMy1_MFCTempDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CMy1_MFCTempDlg::OnCancel();
}


void CMy1_MFCTempDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	INT_PTR nRes;             // ���ڱ���DoModal�����ķ���ֵ   

	CTask1 tipDlg;           // ����Ի�����CTipDlg��ʵ��   
	nRes = tipDlg.DoModal();  // �����Ի���   
	if (IDCANCEL == nRes)     // �ж϶Ի����˳��󷵻�ֵ�Ƿ�ΪIDCANCEL���������return�������������ִ��   
		return;
}


void CMy1_MFCTempDlg::OnBnClickedButton4()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	INT_PTR nRes;             // ���ڱ���DoModal�����ķ���ֵ   

	CTask2 tipDlg;           // ����Ի�����CTipDlg��ʵ��   
	nRes = tipDlg.DoModal();  // �����Ի���   
	if (IDCANCEL == nRes)     // �ж϶Ի����˳��󷵻�ֵ�Ƿ�ΪIDCANCEL���������return�������������ִ��   
		return;
}


void CMy1_MFCTempDlg::OnBnClickedButton5()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	INT_PTR nRes;             // ���ڱ���DoModal�����ķ���ֵ   

	CTask3 tipDlg;           // ����Ի�����CTipDlg��ʵ��   
	nRes = tipDlg.DoModal();  // �����Ի���   
	if (IDCANCEL == nRes)     // �ж϶Ի����˳��󷵻�ֵ�Ƿ�ΪIDCANCEL���������return�������������ִ��   
		return;
}


void CMy1_MFCTempDlg::OnBnClickedButton6()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	INT_PTR nRes;             // ���ڱ���DoModal�����ķ���ֵ   

	CTask4 tipDlg;           // ����Ի�����CTipDlg��ʵ��   
	nRes = tipDlg.DoModal();  // �����Ի���   
	if (IDCANCEL == nRes)     // �ж϶Ի����˳��󷵻�ֵ�Ƿ�ΪIDCANCEL���������return�������������ִ��   
		return;
}
