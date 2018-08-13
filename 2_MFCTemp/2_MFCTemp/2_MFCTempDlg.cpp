
// 2_MFCTempDlg.cpp : 实现文件
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

// 全局变量声明
Mat g_srcImage;
bool g_load = false;
bool g_gaussian = false;

// CMy2_MFCTempDlg 对话框



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


// CMy2_MFCTempDlg 消息处理程序

BOOL CMy2_MFCTempDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	// 菜单栏初始化
	m_hIcon1 = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICONHELP), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	m_hIcon2 = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICONEXIT), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	m_hIcon3 = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICONTITLE), IMAGE_ICON, 210, 40, LR_DEFAULTCOLOR);
	m_Menu1.SetIcon(m_hIcon1);
	m_Menu2.SetIcon(m_hIcon2);
	m_Menu4.SetIcon(m_hIcon3);

	// 按钮初始化
	m_btnload.SubclassDlgItem(IDC_BUTTONLOAD, this);
	m_btnload.SetIcon(IDI_ICONLOADIMAGE);
	m_btnload.SetAlign(CButtonST::ST_ALIGN_VERT);


	m_btngaussian.SubclassDlgItem(IDC_BUTTONGAUSSIAN, this);
	m_btngaussian.SetIcon(IDI_ICONGAUSSIAN);
	m_btngaussian.SetAlign(CButtonST::ST_ALIGN_VERT);

	m_btnfindcenterline.SubclassDlgItem(IDC_BUTTONFINDCENTERLINE, this);
	m_btnfindcenterline.SetIcon(IDI_ICONFINDCENTERLINE);
	m_btnfindcenterline.SetAlign(CButtonST::ST_ALIGN_VERT);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy2_MFCTempDlg::OnPaint()
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
HCURSOR CMy2_MFCTempDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy2_MFCTempDlg::OnBnClickedButtonexit()
{
	// TODO:  在此添加控件通知处理程序代码
	CMy2_MFCTempDlg::OnCancel();
}


void CMy2_MFCTempDlg::OnBnClickedButtonload()  // 载入面结构光原图
{
	// TODO:  在此添加控件通知处理程序代码
	g_srcImage = imread("srcImage.bmp");
	if (g_srcImage.empty())
	{
		MessageBox(_T("载入原图失败！请重试..."), NULL, MB_ICONWARNING); // 载入失败的响应
	}
	imshow("【面结构光原图】", g_srcImage);

	g_load = true;
}


void CMy2_MFCTempDlg::OnBnClickedButtongaussian() // 对原图像进行高斯滤波
{
	// TODO:  在此添加控件通知处理程序代码
	if (g_load == true)
	{
		if (3 == g_srcImage.channels())
			cvtColor(g_srcImage, g_srcImage, CV_RGB2GRAY);
		GaussianBlur(g_srcImage, g_srcImage, Size(7, 7), 1.5, 1.5);
		imshow("【高斯滤波效果图】", g_srcImage);
	}
	else
	{
		MessageBox(_T("请先载入原图再点击高斯滤波..."), NULL, MB_ICONWARNING); // 未载入原图就点高斯滤波
	}
	g_gaussian = true;
}


void CMy2_MFCTempDlg::OnBnClickedButtonfindcenterline()
{
	// TODO:  在此添加控件通知处理程序代码
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
		imshow("【中心线初步提取效果图】", g_centerline);

		Mat A(g_srcImage.size(), CV_8UC1, Scalar::all(0));

		Mat element = getStructuringElement(MORPH_RECT, Size(7, 7));
		Mat element2 = getStructuringElement(MORPH_RECT, Size(5, 5));
		morphologyEx(g_centerline, A, MORPH_DILATE, element);
		morphologyEx(A, A, MORPH_ERODE, element2);

		Mat element3 = getStructuringElement(MORPH_RECT, Size(2, 2));
		morphologyEx(A, A, MORPH_DILATE, element3);

		imshow("【闭运算效果图】", A);

		Canny(A, A, 50, 100, 3);
		imshow("【canny效果图】", A);

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
		imshow("【中心线效果图】", b);


		Mat element4 = getStructuringElement(MORPH_RECT, Size(5, 5));
		Mat element5 = getStructuringElement(MORPH_RECT, Size(5, 5));
		morphologyEx(b, b, MORPH_DILATE, element4);
		morphologyEx(b, b, MORPH_ERODE, element5);
		imshow("【闭运算效果图】", b);

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
		imshow("【最终效果图】", b);

		Mat result;
		addWeighted(g_srcImage, 1, b, 1, 0.0, result);
		imshow("【中心线原图显示结果图】", result);
		imwrite("result.jpg", result);
	}
	else
	{
		MessageBox(_T("请先进行高斯滤波再点击中心线提取..."), NULL, MB_ICONWARNING); // 未进行高斯滤波就点中心线提取
	}
	g_load = false;
	g_gaussian = false;
}


void CMy2_MFCTempDlg::OnBnClickedButtonhelp()
{
	// TODO:  在此添加控件通知处理程序代码
	if (NULL == m_pTipDlg)
	{
		// 创建非模态对话框实例   
		m_pTipDlg = new CTipDlg();
		m_pTipDlg->Create(IDD_DIALOG1, this);
	}
	// 显示非模态对话框   
	m_pTipDlg->ShowWindow(SW_SHOW);
}

CMy2_MFCTempDlg::~CMy2_MFCTempDlg()
{
	// 如果非模态对话框已经创建则删除它   
	if (NULL != m_pTipDlg)
	{
		// 删除非模态对话框对象   
		delete m_pTipDlg;
	}
}

