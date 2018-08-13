
// 3_MFCTempDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "3_MFCTemp.h"
#include "3_MFCTempDlg.h"
#include "afxdialogex.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//// 全局 
int flag = 0;
Mat g_srcImage, g_threImage, g_grayImage;// 函数1中所用到的-原图,阈值化图,灰度图
Mat g_morphImage;// 函数2中所用到的形态学操作图
Mat g_rectangleImage;// 函数3中所用到的矩形图
Mat g_moveImage;// 函数4中所用到的平移图
Mat g_rotateImage;// 函数5中所用到的旋转图
Mat g_switchImage;// 函数6中所用到的开关图
int g_nThresholdType = 0;// 0为二进制阈值，1为反二进制阈值，2为截断阈值，3为阈值化为0，4为反阈值化为0，5为均匀自适应阈值，6为高斯自适应阈值
int g_nThresholdValue = 75;// 前景阈值
double rectx0, recty0, xoffset, yoffset;// 包围矩形的中心x0,y0,相对于中心的偏移量
double k, pi_angle, angle;//斜率,弧度,角度

HICON m_hIconLedRed, m_hIconLedGreen;
CStatic m_DIP1;
CStatic m_DIP2;
CStatic m_DIP3;
CStatic m_DIP4;
CStatic m_DIP5;
CStatic m_DIP6;
CStatic m_DIP7;
CStatic m_DIP8;
CStatic m_DIP9;
CStatic m_DIP10;
CStatic m_DIP11;
CStatic m_DIP12;

// CMy3_MFCTempDlg 对话框



CMy3_MFCTempDlg::CMy3_MFCTempDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy3_MFCTempDlg::IDD, pParent)
	, m_edit1(0)
	, m_edit2(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pTipDlg = NULL;
}

void CMy3_MFCTempDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_Menu1);
	DDX_Control(pDX, IDC_BUTTON2, m_Menu2);
	DDX_Control(pDX, IDC_TITLE, m_Menu3);
	DDX_Control(pDX, IDC_CHECK1, m_picture1);
	DDX_Control(pDX, IDC_CHECK2, m_picture2);
	DDX_Control(pDX, IDC_CHECK3, m_picture3);
	DDX_Control(pDX, IDC_CHECK4, m_picture4);
	DDX_Control(pDX, IDC_DIP1, m_DIP1);
	DDX_Control(pDX, IDC_DIP2, m_DIP2);
	DDX_Control(pDX, IDC_DIP3, m_DIP3);
	DDX_Control(pDX, IDC_DIP4, m_DIP4);
	DDX_Control(pDX, IDC_DIP5, m_DIP5);
	DDX_Control(pDX, IDC_DIP6, m_DIP6);
	DDX_Control(pDX, IDC_DIP7, m_DIP7);
	DDX_Control(pDX, IDC_DIP8, m_DIP8);
	DDX_Control(pDX, IDC_DIP9, m_DIP9);
	DDX_Control(pDX, IDC_DIP10, m_DIP10);
	DDX_Control(pDX, IDC_DIP11, m_DIP11);
	DDX_Control(pDX, IDC_DIP12, m_DIP12);
	DDX_Control(pDX, IDC_CHECK5, m_picture5);
	DDX_Control(pDX, IDC_CHECK6, m_picture6);

	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT1, m_edit11);
	DDX_Control(pDX, IDC_EDIT2, m_edit22);
}

BEGIN_MESSAGE_MAP(CMy3_MFCTempDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK1, &CMy3_MFCTempDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CMy3_MFCTempDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CMy3_MFCTempDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CMy3_MFCTempDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy3_MFCTempDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMy3_MFCTempDlg::OnClickedButton4)
	ON_BN_CLICKED(IDC_CHECK5, &CMy3_MFCTempDlg::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK6, &CMy3_MFCTempDlg::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy3_MFCTempDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMy3_MFCTempDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMy3_MFCTempDlg 消息处理程序

BOOL CMy3_MFCTempDlg::OnInitDialog()
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
	m_hIcon3 = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICONTITLE), IMAGE_ICON, 227, 46, LR_DEFAULTCOLOR);
	m_Menu1.SetIcon(m_hIcon1);
	m_Menu2.SetIcon(m_hIcon2);
	m_Menu3.SetIcon(m_hIcon3);

	// DIP灯初始化
	m_hIconLedRed = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICONRED), IMAGE_ICON, 20, 20, LR_DEFAULTCOLOR);
	m_hIconLedGreen = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICONGREEN), IMAGE_ICON, 20, 20, LR_DEFAULTCOLOR);
	m_DIP1.SetIcon(m_hIconLedRed);
	m_DIP2.SetIcon(m_hIconLedRed);
	m_DIP3.SetIcon(m_hIconLedRed);
	m_DIP4.SetIcon(m_hIconLedRed);
	m_DIP5.SetIcon(m_hIconLedRed);
	m_DIP6.SetIcon(m_hIconLedRed);
	m_DIP7.SetIcon(m_hIconLedRed);
	m_DIP8.SetIcon(m_hIconLedRed);
	m_DIP9.SetIcon(m_hIconLedRed);
	m_DIP10.SetIcon(m_hIconLedRed);
	m_DIP11.SetIcon(m_hIconLedRed);
	m_DIP12.SetIcon(m_hIconLedRed);

	m_btnload.SubclassDlgItem(IDC_BUTTON3, this);
	m_btnload.SetIcon(IDI_ICONLOAD);
	m_btnload.SetAlign(CButtonST::ST_ALIGN_VERT);

	m_btnidentify.SubclassDlgItem(IDC_BUTTON4, this);
	m_btnidentify.SetIcon(IDI_ICONGO);
	m_btnidentify.SetAlign(CButtonST::ST_ALIGN_VERT);

	m_edit11.SetWindowText(_T("75"));
	m_edit22.SetWindowText(_T("202"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy3_MFCTempDlg::OnPaint()
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
HCURSOR CMy3_MFCTempDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMy3_MFCTempDlg::OnBnClickedCheck1()
{
	// TODO:  在此添加控件通知处理程序代码
	m_picture2.SetCheck(0);
	m_picture3.SetCheck(0);
	m_picture4.SetCheck(0);
	m_picture5.SetCheck(0);
	m_picture6.SetCheck(0);
	flag = 1;
	m_DIP1.SetIcon(m_hIconLedRed);
	m_DIP2.SetIcon(m_hIconLedRed);
	m_DIP3.SetIcon(m_hIconLedRed);
	m_DIP4.SetIcon(m_hIconLedRed);
	m_DIP5.SetIcon(m_hIconLedRed);
	m_DIP6.SetIcon(m_hIconLedRed);
	m_DIP7.SetIcon(m_hIconLedRed);
	m_DIP8.SetIcon(m_hIconLedRed);
	m_DIP9.SetIcon(m_hIconLedRed);
	m_DIP10.SetIcon(m_hIconLedRed);
	m_DIP11.SetIcon(m_hIconLedRed);
	m_DIP12.SetIcon(m_hIconLedRed);
	destroyAllWindows();
}


void CMy3_MFCTempDlg::OnBnClickedCheck2()
{
	// TODO:  在此添加控件通知处理程序代码
	m_picture1.SetCheck(0);
	m_picture3.SetCheck(0);
	m_picture4.SetCheck(0);
	m_picture5.SetCheck(0);
	m_picture6.SetCheck(0);
	flag = 2;
	m_DIP1.SetIcon(m_hIconLedRed);
	m_DIP2.SetIcon(m_hIconLedRed);
	m_DIP3.SetIcon(m_hIconLedRed);
	m_DIP4.SetIcon(m_hIconLedRed);
	m_DIP5.SetIcon(m_hIconLedRed);
	m_DIP6.SetIcon(m_hIconLedRed);
	m_DIP7.SetIcon(m_hIconLedRed);
	m_DIP8.SetIcon(m_hIconLedRed);
	m_DIP9.SetIcon(m_hIconLedRed);
	m_DIP10.SetIcon(m_hIconLedRed);
	m_DIP11.SetIcon(m_hIconLedRed);
	m_DIP12.SetIcon(m_hIconLedRed);
	destroyAllWindows();
}


void CMy3_MFCTempDlg::OnBnClickedCheck3()
{
	// TODO:  在此添加控件通知处理程序代码
	m_picture1.SetCheck(0);
	m_picture2.SetCheck(0);
	m_picture4.SetCheck(0);
	m_picture5.SetCheck(0);
	m_picture6.SetCheck(0);
	flag = 3;
	m_DIP1.SetIcon(m_hIconLedRed);
	m_DIP2.SetIcon(m_hIconLedRed);
	m_DIP3.SetIcon(m_hIconLedRed);
	m_DIP4.SetIcon(m_hIconLedRed);
	m_DIP5.SetIcon(m_hIconLedRed);
	m_DIP6.SetIcon(m_hIconLedRed);
	m_DIP7.SetIcon(m_hIconLedRed);
	m_DIP8.SetIcon(m_hIconLedRed);
	m_DIP9.SetIcon(m_hIconLedRed);
	m_DIP10.SetIcon(m_hIconLedRed);
	m_DIP11.SetIcon(m_hIconLedRed);
	m_DIP12.SetIcon(m_hIconLedRed);
	destroyAllWindows();
}


void CMy3_MFCTempDlg::OnBnClickedCheck4()
{
	// TODO:  在此添加控件通知处理程序代码
	m_picture1.SetCheck(0);
	m_picture2.SetCheck(0);
	m_picture3.SetCheck(0);
	m_picture5.SetCheck(0);
	m_picture6.SetCheck(0);
	flag = 4;
	m_DIP1.SetIcon(m_hIconLedRed);
	m_DIP2.SetIcon(m_hIconLedRed);
	m_DIP3.SetIcon(m_hIconLedRed);
	m_DIP4.SetIcon(m_hIconLedRed);
	m_DIP5.SetIcon(m_hIconLedRed);
	m_DIP6.SetIcon(m_hIconLedRed);
	m_DIP7.SetIcon(m_hIconLedRed);
	m_DIP8.SetIcon(m_hIconLedRed);
	m_DIP9.SetIcon(m_hIconLedRed);
	m_DIP10.SetIcon(m_hIconLedRed);
	m_DIP11.SetIcon(m_hIconLedRed);
	m_DIP12.SetIcon(m_hIconLedRed);
	destroyAllWindows();
}

void CMy3_MFCTempDlg::OnBnClickedCheck5()
{
	// TODO:  在此添加控件通知处理程序代码
	m_picture1.SetCheck(0);
	m_picture2.SetCheck(0);
	m_picture3.SetCheck(0);
	m_picture4.SetCheck(0);
	m_picture6.SetCheck(0);
	flag = 5;
	m_DIP1.SetIcon(m_hIconLedRed);
	m_DIP2.SetIcon(m_hIconLedRed);
	m_DIP3.SetIcon(m_hIconLedRed);
	m_DIP4.SetIcon(m_hIconLedRed);
	m_DIP5.SetIcon(m_hIconLedRed);
	m_DIP6.SetIcon(m_hIconLedRed);
	m_DIP7.SetIcon(m_hIconLedRed);
	m_DIP8.SetIcon(m_hIconLedRed);
	m_DIP9.SetIcon(m_hIconLedRed);
	m_DIP10.SetIcon(m_hIconLedRed);
	m_DIP11.SetIcon(m_hIconLedRed);
	m_DIP12.SetIcon(m_hIconLedRed);
	destroyAllWindows();
}

void CMy3_MFCTempDlg::OnBnClickedCheck6()
{
	// TODO:  在此添加控件通知处理程序代码
	m_picture1.SetCheck(0);
	m_picture2.SetCheck(0);
	m_picture3.SetCheck(0);
	m_picture4.SetCheck(0);
	m_picture5.SetCheck(0);
	flag = 6;
	m_DIP1.SetIcon(m_hIconLedRed);
	m_DIP2.SetIcon(m_hIconLedRed);
	m_DIP3.SetIcon(m_hIconLedRed);
	m_DIP4.SetIcon(m_hIconLedRed);
	m_DIP5.SetIcon(m_hIconLedRed);
	m_DIP6.SetIcon(m_hIconLedRed);
	m_DIP7.SetIcon(m_hIconLedRed);
	m_DIP8.SetIcon(m_hIconLedRed);
	m_DIP9.SetIcon(m_hIconLedRed);
	m_DIP10.SetIcon(m_hIconLedRed);
	m_DIP11.SetIcon(m_hIconLedRed);
	m_DIP12.SetIcon(m_hIconLedRed);
	destroyAllWindows();
}

void CMy3_MFCTempDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	switch (flag)
	{
	case 1:g_srcImage = imread("dip_switch_01.bmp"); break;
	case 2:g_srcImage = imread("dip_switch_02.bmp"); break;
	case 3:g_srcImage = imread("dip_switch_03.bmp"); break;
	case 4:g_srcImage = imread("dip_switch_11.bmp"); break;
	case 5:g_srcImage = imread("dip_switch_22.bmp"); break;
	case 6:g_srcImage = imread("dip_switch_33.bmp"); break;
	default:MessageBox(_T("载入图片失败！请重试..."), NULL, MB_ICONWARNING);
	}	
	/// 显示源图像
	imshow("【开关图片】", g_srcImage);
}


//函数2-形态学操作
Mat morphology(Mat &g_threImage)
{
	/// 定义形态学操作的核
	Mat element1 = getStructuringElement(MORPH_RECT, Size(39, 39));//MORPH_RECT, MORPH_CROSS, MORPH_ELLIPSE
	Mat element2 = getStructuringElement(MORPH_RECT, Size(39, 39));//MORPH_RECT, MORPH_CROSS, MORPH_ELLIPSE
	/// 先腐蚀后膨胀得到前景
	erode(g_threImage, g_threImage, element1);
	dilate(g_threImage, g_threImage, element2);
	//imshow("【形态学操图像】", g_threImage);
	return g_threImage;
}

//函数3-寻找包围矩形顶点并计算偏移量和旋转量
void findpoint(Mat &g_morphImage)
{
	int thresh = 100;
	int max_thresh = 255;
	/// 转为灰度图并模糊化  
	//cvtColor(g_morphImage, g_A, CV_BGR2GRAY);
	blur(g_morphImage, g_morphImage, Size(3, 3));

	Mat threshold_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// 阈值化检测边界  
	threshold(g_morphImage, threshold_output, thresh, 255, THRESH_BINARY);
	/// 寻找轮廓  
	findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// 对每个找到的轮廓创建可倾斜的边界框和椭圆  
	vector<RotatedRect> minRect(contours.size());
	vector<RotatedRect> minEllipse(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		minRect[i] = minAreaRect(Mat(contours[i]));
		if (contours[i].size() > 5)
		{
			minEllipse[i] = fitEllipse(Mat(contours[i]));
		}
	}

	/// 绘出轮廓及其可倾斜的边界框和边界椭圆  
	g_rectangleImage = Mat::zeros(threshold_output.size(), CV_8UC3);
	Point2f rect_points[4];
	for (int i = 0; i < contours.size(); i++)
	{
		///绘制旋转的包围矩形
		minRect[i].points(rect_points);
		//cout << "4个顶点的坐标分别为:" << endl;
		for (int j = 0; j < 4; j++)
		{
			line(g_rectangleImage, rect_points[j], rect_points[(j + 1) % 4], Scalar(0, 0, 255), 1, 8);
			//cout << rect_points[j] << endl;
		}
	}
	/// 结果在窗体中显示  
	//namedWindow("【包围框图像】", CV_WINDOW_AUTOSIZE);
	//imshow("【包围框图像】", g_rectangleImage);

	/// 计算平移量
	//cout << endl;
	//cout << "g_srcImage.cols=" << g_srcImage.cols << endl;
	//cout << "g_srcImage.rows=" << g_srcImage.rows << endl;

	rectx0 = (rect_points[0].x + rect_points[2].x) / 2;    //包围矩形中心的X坐标=(p0x+p2x)/2
	recty0 = (rect_points[0].y + rect_points[2].y) / 2;    //包围矩形中心的Y坐标=(p0y+p2y)/2
	xoffset = (g_srcImage.cols / 2 - rectx0);          //包围矩形中心x0相对于图像中心xc的偏移量=fabs(xc-x0)
	yoffset = (g_srcImage.rows / 2 - recty0);          //包围矩形中心x0相对于图像中心xc的偏移量=fabs(yc-y0)
	//cout << endl;
	//cout << "包围矩形中心的x0坐标= " << rectx0 << endl;
	//cout << "包围矩形中心的y0坐标= " << recty0 << endl;
	//cout << endl;
	//cout << "矩形中心偏移量xoffset=" << xoffset << endl;
	//cout << "矩形中心偏移量yoffset=" << yoffset << endl;

	/// 计算旋转角度
	k = fabs((rect_points[0].y - rect_points[3].y) / (rect_points[0].x - rect_points[3].x));// 通过相邻两点来计算斜率
	pi_angle = atan(k);// 通过反正切得到弧度数
	angle = pi_angle * 180 / 3.14159;//转化为角度数
	//cout << endl;
	//cout << "旋转的弧度pi_angle=" << pi_angle << endl;
	//cout << "旋转的角度 angle = " << angle << endl;
}

//函数4-将图像移至中心
void move(Mat &g_srcImage)
{
	const int rows = g_srcImage.rows;
	const int cols = g_srcImage.cols;
	g_moveImage.create(rows, cols, g_srcImage.type());
	Vec3b *p;
	for (int i = 0; i < rows; i++)
	{
		p = g_moveImage.ptr<Vec3b>(i);
		for (int j = 0; j < cols; j++)
		{
			//平移后坐标映射到原图像  
			int x = j - xoffset;
			int y = i - yoffset;
			//保证映射后的坐标在原图像范围内  
			if (x >= 0 && y >= 0 && x < cols && y < rows)
				p[j] = g_srcImage.ptr<Vec3b>(y)[x];
		}
	}
	Point center0 = Point(g_srcImage.cols / 2, g_srcImage.rows / 2);
	circle(g_moveImage, center0, 3, Scalar(0, 255, 0), -1, 8, 0);//这里倒数第三个参数-1为实心圆,0为空心圆,最后两个参数默认8,0
	//imshow("【平移至图像中心的图像】", g_moveImage);
}

//函数5-将平移后的图像绕图像中心旋转
void rotate(Mat &g_moveImage)
{
	double a = sin(angle * CV_PI / 180);
	double b = cos(angle * CV_PI / 180);

	int width = g_srcImage.cols;
	int height = g_srcImage.rows;

	int rotate_width = int(height * fabs(a) + width * fabs(b));
	int rotate_height = int(width * fabs(a) + height * fabs(b));

	Point center = Point(g_srcImage.cols / 2, g_srcImage.rows / 2);

	Mat map_matrix = getRotationMatrix2D(center, -angle, 1.0);
	map_matrix.at<double>(0, 2) += (rotate_width - width) / 2;     // 修改坐标偏移  
	map_matrix.at<double>(1, 2) += (rotate_height - height) / 2;   // 修改坐标偏移  

	warpAffine(g_moveImage, g_rotateImage, map_matrix, { rotate_width, rotate_height }, CV_INTER_CUBIC);
	imshow("【绕图像中心旋转的图像】", g_rotateImage);
}

//函数6-将旋转后的图像阈值化得到开关
void DIPImage(Mat &g_rotateImage)
{
	int DIPwidth = 322;
	int DIPheight = 38;
	Point uleft(g_rotateImage.cols / 2 + 105, g_rotateImage.rows / 2 - 45);
	Point dright(g_rotateImage.cols / 2 + 135, g_rotateImage.rows / 2 - 30);
	Mat judge = g_rotateImage(Rect(uleft, dright));
	//imshow("222", judge);
	bool A;
	int sum = 0;
	for (int j = 0; j < judge.rows; j++)
	{
		uchar* data = judge.ptr<uchar>(j);
		for (int i = 0; i < judge.cols; i++)
		{
			sum = data[i] + sum;
		}
	}
	//cout << sum;

	threshold(g_rotateImage, g_switchImage, 202, 255, 0);
	/// 定义形态学操作的核
	Mat element1 = getStructuringElement(MORPH_RECT, Size(7, 7));//MORPH_RECT, MORPH_CROSS, MORPH_ELLIPSE
	Mat element2 = getStructuringElement(MORPH_RECT, Size(7, 7));//MORPH_RECT, MORPH_CROSS, MORPH_ELLIPSE
	/// 先腐蚀后膨胀得到前景
	erode(g_switchImage, g_switchImage, element1);
	dilate(g_switchImage, g_switchImage, element2);
	//imshow("1111", g_switchImage);

	/// 截取矩形包围的图像，并保存到dst中  
	Point leftup((g_rotateImage.cols - DIPwidth) / 2, (g_rotateImage.rows - DIPheight) / 2);
	Point rightdown((g_rotateImage.cols + DIPwidth) / 2, (g_rotateImage.rows + DIPheight) / 2);
	g_switchImage = g_switchImage(Rect(leftup, rightdown));
	if (sum >46000)
	{
		flip(g_switchImage, g_switchImage, -1);
	}
	imshow("【开关图像】", g_switchImage);
}

//函数7-判断开关状态
void judgestatus(Mat &g_switchImage)
{
	int thresh = 100;
	int max_thresh = 255;
	/// 转为灰度图并模糊化  
	cvtColor(g_switchImage, g_switchImage, CV_BGR2GRAY);
	//blur(g_switchImage, g_switchImage, Size(3, 3));
	GaussianBlur(g_switchImage, g_switchImage, Size(3, 3),1.5,1.5);

	Mat threshold_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// 阈值化检测边界  
	threshold(g_switchImage, threshold_output, thresh, 255, THRESH_BINARY);
	/// 寻找轮廓  
	findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// 对每个找到的轮廓创建可倾斜的边界框和椭圆  
	vector<RotatedRect> minRect(contours.size());
	vector<RotatedRect> minEllipse(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		minRect[i] = minAreaRect(Mat(contours[i]));
		if (contours[i].size() > 5)
		{
			minEllipse[i] = fitEllipse(Mat(contours[i]));
		}
	}

	/// 绘出轮廓及其可倾斜的边界框和边界椭圆  
	Mat g_rectangleImage = Mat::zeros(threshold_output.size(), CV_8UC3);
	Point2f rect_points[4];

	int allx[48];
	int k = 0;
	for (int i = 0; i < contours.size(); i++)
	{
		///绘制旋转的包围矩形
		minRect[i].points(rect_points);
		for (int j = 0; j < 4; j++)
		{
			allx[k] = rect_points[j].x;
			k++;
		}
	}
	int t;
	for (int i = 0; i < 47; i++)
	{
		for (int j = i + 1; j < 48; j++)
		{
			if (allx[i]>allx[j])
			{
				t = allx[i];
				allx[i] = allx[j];
				allx[j] = t;
			}
		}
	}
	int DIP = 1;
	for (int number = 0; number < 48; number += 4)
	{
		int xx = (allx[number] + allx[number + 2]) / 2;
		int ydown = g_switchImage.rows / 2 + 10;
		uchar* ptr = g_switchImage.ptr<uchar>(ydown);
		if (ptr[xx]>0)
		{
			switch (DIP)
			{
			case 1:m_DIP1.SetIcon(m_hIconLedGreen); break;
			case 2:m_DIP2.SetIcon(m_hIconLedGreen); break;
			case 3:m_DIP3.SetIcon(m_hIconLedGreen); break;
			case 4:m_DIP4.SetIcon(m_hIconLedGreen); break;
			case 5:m_DIP5.SetIcon(m_hIconLedGreen); break;
			case 6:m_DIP6.SetIcon(m_hIconLedGreen); break;
			case 7:m_DIP7.SetIcon(m_hIconLedGreen); break;
			case 8:m_DIP8.SetIcon(m_hIconLedGreen); break;
			case 9:m_DIP9.SetIcon(m_hIconLedGreen); break;
			case 10:m_DIP10.SetIcon(m_hIconLedGreen); break;
			case 11:m_DIP11.SetIcon(m_hIconLedGreen); break;
			case 12:m_DIP12.SetIcon(m_hIconLedGreen); break;
			}
		}
		DIP++;
	}
	//imshow("line", g_switchImage);
}

void CMy3_MFCTempDlg::OnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	/// 灰度图像
	cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);

	threshold(g_grayImage, g_threImage, g_nThresholdValue, 255, g_nThresholdType);
	//imshow("【阈值化图像】", g_threImage);
	
	g_morphImage = morphology(g_threImage);
	findpoint(g_morphImage);
	move(g_srcImage);
	rotate(g_moveImage);

	DIPImage(g_rotateImage);
	judgestatus(g_switchImage);
}

void CMy3_MFCTempDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	CMy3_MFCTempDlg::OnCancel();
}


void CMy3_MFCTempDlg::OnBnClickedButton1()
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

CMy3_MFCTempDlg::~CMy3_MFCTempDlg()
{
	// 如果非模态对话框已经创建则删除它   
	if (NULL != m_pTipDlg)
	{
		// 删除非模态对话框对象   
		delete m_pTipDlg;
	}
}