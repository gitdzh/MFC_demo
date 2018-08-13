
// 2_MFCTempDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "2_MFCTemp.h"
#include "2_MFCTempDlg.h"
#include "afxdialogex.h"
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\core\core.hpp>
#include "TipDlg.h"
using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ȫ�ֱ�������
Mat g_srcImage;
bool g_load = false;
bool g_gaussian = false;

// CMy2_MFCTempDlg �Ի���



CMy2_MFCTempDlg::CMy2_MFCTempDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy2_MFCTempDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pTipDlg = NULL;
}

void CMy2_MFCTempDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTONHELP, m_Menu1);
	DDX_Control(pDX, IDC_BUTTONEXIT, m_Menu2);
	DDX_Control(pDX, IDC_STATIC1, m_Menu4);
}

BEGIN_MESSAGE_MAP(CMy2_MFCTempDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONEXIT, &CMy2_MFCTempDlg::OnBnClickedButtonexit)
	ON_BN_CLICKED(IDC_BUTTONLOAD, &CMy2_MFCTempDlg::OnBnClickedButtonload)
	ON_BN_CLICKED(IDC_BUTTONGAUSSIAN, &CMy2_MFCTempDlg::OnBnClickedButtongaussian)
	ON_BN_CLICKED(IDC_BUTTONFINDCENTERLINE, &CMy2_MFCTempDlg::OnBnClickedButtonfindcenterline)
	ON_BN_CLICKED(IDC_BUTTONHELP, &CMy2_MFCTempDlg::OnBnClickedButtonhelp)
END_MESSAGE_MAP()


// CMy2_MFCTempDlg ��Ϣ�������

BOOL CMy2_MFCTempDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	// �˵�����ʼ��
	m_hIcon1 = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICONHELP), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	m_hIcon2 = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICONEXIT), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	m_hIcon3 = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICONTITLE), IMAGE_ICON, 210, 40, LR_DEFAULTCOLOR);
	m_Menu1.SetIcon(m_hIcon1);
	m_Menu2.SetIcon(m_hIcon2);
	m_Menu4.SetIcon(m_hIcon3);

	// ��ť��ʼ��
	m_btnload.SubclassDlgItem(IDC_BUTTONLOAD, this);
	m_btnload.SetIcon(IDI_ICONLOADIMAGE);
	m_btnload.SetAlign(CButtonST::ST_ALIGN_VERT);


	m_btngaussian.SubclassDlgItem(IDC_BUTTONGAUSSIAN, this);
	m_btngaussian.SetIcon(IDI_ICONGAUSSIAN);
	m_btngaussian.SetAlign(CButtonST::ST_ALIGN_VERT);

	m_btnfindcenterline.SubclassDlgItem(IDC_BUTTONFINDCENTERLINE, this);
	m_btnfindcenterline.SetIcon(IDI_ICONFINDCENTERLINE);
	m_btnfindcenterline.SetAlign(CButtonST::ST_ALIGN_VERT);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy2_MFCTempDlg::OnPaint()
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
HCURSOR CMy2_MFCTempDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy2_MFCTempDlg::OnBnClickedButtonexit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CMy2_MFCTempDlg::OnCancel();
}


void CMy2_MFCTempDlg::OnBnClickedButtonload()  // ������ṹ��ԭͼ
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	g_srcImage = imread("srcImage.bmp");
	if (g_srcImage.empty())
	{
		MessageBox(_T("����ԭͼʧ�ܣ�������..."), NULL, MB_ICONWARNING); // ����ʧ�ܵ���Ӧ
	}
	imshow("����ṹ��ԭͼ��", g_srcImage);

	g_load = true;
}


void CMy2_MFCTempDlg::OnBnClickedButtongaussian() // ��ԭͼ����и�˹�˲�
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (g_load == true)
	{
		if (3 == g_srcImage.channels())
			cvtColor(g_srcImage, g_srcImage, CV_RGB2GRAY);
		GaussianBlur(g_srcImage, g_srcImage, Size(7, 7), 1.5, 1.5);
		imshow("����˹�˲�Ч��ͼ��", g_srcImage);
	}
	else
	{
		MessageBox(_T("��������ԭͼ�ٵ����˹�˲�..."), NULL, MB_ICONWARNING); // δ����ԭͼ�͵��˹�˲�
	}
	g_gaussian = true;
}


void CMy2_MFCTempDlg::OnBnClickedButtonfindcenterline()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (g_gaussian == true)
	{
		Mat g_centerline(g_srcImage.size(), CV_8UC1, Scalar::all(0));
		int nl = g_srcImage.rows;
		int nc = g_srcImage.cols;
		for (int j = 0; j < nl; j++)
		{
			uchar* data = g_srcImage.ptr<uchar>(j);
			uchar* data1 = g_centerline.ptr<uchar>(j);
			for (int i = 1; i < nc - 1; i++)
			{
				if ((data[i - 1]<data[i]) && (data[i]>data[i + 1]))
				{
					data1[i] = 255;
				}
			}
		}
		imshow("�������߳�����ȡЧ��ͼ��", g_centerline);

		Mat A(g_srcImage.size(), CV_8UC1, Scalar::all(0));

		Mat element = getStructuringElement(MORPH_RECT, Size(7, 7));
		Mat element2 = getStructuringElement(MORPH_RECT, Size(5, 5));
		morphologyEx(g_centerline, A, MORPH_DILATE, element);
		morphologyEx(A, A, MORPH_ERODE, element2);

		Mat element3 = getStructuringElement(MORPH_RECT, Size(2, 2));
		morphologyEx(A, A, MORPH_DILATE, element3);

		imshow("��������Ч��ͼ��", A);

		Canny(A, A, 50, 100, 3);
		imshow("��cannyЧ��ͼ��", A);

		Mat b(g_srcImage.size(), CV_8UC1, Scalar::all(0));

		int n = 0;
		for (int j = 0; j < A.rows; j++)
		{
			uchar* data = b.ptr<uchar>(j);
			uchar* data1 = A.ptr<uchar>(j);
			for (int i = 1; i < A.cols - 1; i++)
			{
				if ((data1[i]==255))
				{
					n++;
					if ((n % 2 == 1))
					{
						data[i + 1] = 255;
					}
				}
				
			}
		}
		imshow("��������Ч��ͼ��", b);


		Mat element4 = getStructuringElement(MORPH_RECT, Size(5, 5));
		Mat element5 = getStructuringElement(MORPH_RECT, Size(5, 5));
		morphologyEx(b, b, MORPH_DILATE, element4);
		morphologyEx(b, b, MORPH_ERODE, element5);
		imshow("��������Ч��ͼ��", b);

		for (int j = 0; j < b.rows; j++)
		{
			uchar* data = b.ptr<uchar>(j);
			for (int i = 1; i < b.cols - 1; i++)
			{
				if ((data[i] == 255))
				{
					if ((data[i + 1] == 255))
					{
						data[i + 1] = 0;
					}
					if (data[i + 2] == 255)
					{
						data[i + 2] = 0;
					}
					
				}
			}
		}
		imshow("������Ч��ͼ��", b);

		Mat result;
		addWeighted(g_srcImage, 1, b, 1, 0.0, result);
		imshow("��������ԭͼ��ʾ���ͼ��", result);
		imwrite("result.jpg", result);
	}
	else
	{
		MessageBox(_T("���Ƚ��и�˹�˲��ٵ����������ȡ..."), NULL, MB_ICONWARNING); // δ���и�˹�˲��͵���������ȡ
	}
	g_load = false;
	g_gaussian = false;
}


void CMy2_MFCTempDlg::OnBnClickedButtonhelp()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (NULL == m_pTipDlg)
	{
		// ������ģ̬�Ի���ʵ��   
		m_pTipDlg = new CTipDlg();
		m_pTipDlg->Create(IDD_DIALOG1, this);
	}
	// ��ʾ��ģ̬�Ի���   
	m_pTipDlg->ShowWindow(SW_SHOW);
}

CMy2_MFCTempDlg::~CMy2_MFCTempDlg()
{
	// �����ģ̬�Ի����Ѿ�������ɾ����   
	if (NULL != m_pTipDlg)
	{
		// ɾ����ģ̬�Ի������   
		delete m_pTipDlg;
	}
}

