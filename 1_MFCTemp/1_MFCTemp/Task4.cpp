// Task4.cpp : 实现文件
//

#include "stdafx.h"
#include "1_MFCTemp.h"
#include "Task4.h"
#include "afxdialogex.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;
// 全局
Mat srcImage4;
int minthreshold, maxthreshold;
double gaussian_temp[3][3] = { 0 };//用于存放3*3高斯滤波模板

// CTask4 对话框

IMPLEMENT_DYNAMIC(CTask4, CDialogEx)

CTask4::CTask4(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTask4::IDD, pParent)
{

}

CTask4::~CTask4()
{
}

void CTask4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTask4, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CTask4::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTask4::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTask4::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTask4::OnBnClickedButton4)
END_MESSAGE_MAP()


// CTask4 消息处理程序

Mat RGBtogray(Mat &srcImage4)
{
	Mat gray = Mat::zeros(srcImage4.size(), CV_8UC1);

	uchar* src_ptr = srcImage4.data;
	uchar* gray_ptr = gray.data;//指向图像数据的第一个字节

	int src_step = srcImage4.step;
	int gray_step = gray.step; //返回一行含有的字节数

	for (int j = 0; j < srcImage4.rows; j++)
	{
		for (int i = 0; i < srcImage4.cols; i++)
		{
			gray_ptr[gray_step*j + i] = 0.114*src_ptr[src_step*j + 3 * i] + 0.587*src_ptr[src_step*j + 3 * i + 1] + 0.299*src_ptr[src_step*j + 3 * i + 2];
		}
	}
	return gray;
}

void GaussianTemp(double gaussian_temp[3][3], const int size, const double sigma)
{
	const double PI = 3.14;

	double sum = 0;
	for (int i = 0; i<size; i++)
	{
		for (int j = 0; j<size; j++)
		{
			gaussian_temp[i][j] = (1 / (2 * PI*sigma*sigma))*exp(-((i - 1)*(i - 1) + (j - 1)*(j - 1)) / (2 * sigma*sigma));
			sum += gaussian_temp[i][j];
		}
	}

	return;
}

Mat GaussianFilter(Mat &grayImage)
{
	Mat gaussian = Mat::zeros(grayImage.size(), CV_8UC1);

	uchar* gray_ptr = grayImage.data;
	uchar* gaussian_ptr = gaussian.data;//指向图像数据的第一个字节
	int gray_step = grayImage.step;
	int gaussian_step = gaussian.step; //返回一行含有的字节数
	double sum = 0;

	for (int j = 0; j < grayImage.rows; j++)
	{
		for (int i = 0; i < grayImage.cols; i++)
		{
			sum = gray_ptr[(j - 1)*gray_step + i - 1] * gaussian_temp[0][0] + gray_ptr[(j - 1)*gray_step + i] * gaussian_temp[0][1] + gray_ptr[(j - 1)*gray_step + i + 1] * gaussian_temp[0][2] +
				gray_ptr[j *gray_step + i - 1] * gaussian_temp[1][0] + gray_ptr[j *gray_step + i] * gaussian_temp[1][1] + gray_ptr[j *gray_step + i + 1] * gaussian_temp[1][2] +
				gray_ptr[(j + 1)*gray_step + i - 1] * gaussian_temp[2][0] + gray_ptr[(j + 1)*gray_step + i] * gaussian_temp[2][1] + gray_ptr[(j + 1)*gray_step + i + 1] * gaussian_temp[2][2];
			if (sum>255)
				sum = 255;
			if (sum < 0)
				sum = 0;
			else
				gaussian_ptr[j*gaussian_step + i] = sum;
		}
	}
	return gaussian;
}

Mat MyGvalue(Mat gaussianImage, int gx[3][3], int gy[3][3], Mat &x, Mat &y, double* &theta)
{
	uchar* x_ptr = x.data;
	uchar* yg_ptr = y.data;
	uchar* gaussian_ptr = gaussianImage.data;
	int x_step = x.step;
	int yg_step = y.step;
	int gaussian_step = gaussianImage.step;
	double sumx = 0;
	double sumy = 0;

	Mat g = Mat::zeros(gaussianImage.size(), CV_8UC1);
	uchar* g_ptr = g.data;
	int g_step = g.step;
	double sumxy = 0;

	int size = (gaussianImage.rows - 1)*(gaussianImage.cols - 1);
	theta = new double[size];
	for (int i = 0; i < size; i++)
	{
		theta[i] = 0;
	}
	int k = 0;

	for (int j = 1; j < gaussianImage.rows - 1; j++)
	{
		for (int i = 1; i < gaussianImage.cols - 1; i++)
		{
			sumx = gaussian_ptr[(j - 1)*gaussian_step + i - 1] * gx[0][0] + gaussian_ptr[(j - 1)*gaussian_step + i] * gx[0][1] + gaussian_ptr[(j - 1)*gaussian_step + i + 1] * gx[0][2] +
				gaussian_ptr[j *gaussian_step + i - 1] * gx[1][0] + gaussian_ptr[j *gaussian_step + i] * gx[1][1] + gaussian_ptr[j *gaussian_step + i + 1] * gx[1][2] +
				gaussian_ptr[(j + 1)*gaussian_step + i - 1] * gx[2][0] + gaussian_ptr[(j + 1)*gaussian_step + i] * gx[2][1] + gaussian_ptr[(j + 1)*gaussian_step + i + 1] * gx[2][2];

			sumy = gaussian_ptr[(j - 1)*gaussian_step + i - 1] * gy[0][0] + gaussian_ptr[(j - 1)*gaussian_step + i] * gy[0][1] + gaussian_ptr[(j - 1)*gaussian_step + i + 1] * gy[0][2] +
				gaussian_ptr[j *gaussian_step + i - 1] * gy[1][0] + gaussian_ptr[j *gaussian_step + i] * gy[1][1] + gaussian_ptr[j *gaussian_step + i + 1] * gy[1][2] +
				gaussian_ptr[(j + 1)*gaussian_step + i - 1] * gy[2][0] + gaussian_ptr[(j + 1)*gaussian_step + i] * gy[2][1] + gaussian_ptr[(j + 1)*gaussian_step + i + 1] * gy[2][2];

			theta[k++] = atan2(sumy, sumx) * 180 / 3.14;

			x_ptr[j*x_step + i] = abs(sumx);
			yg_ptr[j*yg_step + i] = abs(sumy);
		}
	}

	for (int j = 0; j < g.rows; j++)
	{
		for (int i = 0; i < g.cols; i++)
		{
			sumxy = sqrt(x_ptr[j*x_step + i] * x_ptr[j*x_step + i] + yg_ptr[j*yg_step + i] * yg_ptr[j*yg_step + i]);

			g_ptr[j*g_step + i] = (sumxy);
		}
	}

	return g;
}

Mat restrainMaxval(Mat gImage, double *theta)
{

	int k = 0;

	uchar* g_ptr = gImage.data;
	int g_step = gImage.step;
	for (int j = 1; j < gImage.rows - 1; j++)
	{
		for (int i = 1; i < gImage.cols - 1; i++)
		{
			bool flag1 = (g_ptr[j*g_step + i] < g_ptr[(j - 1)*g_step + i]);
			bool flag2 = (g_ptr[j*g_step + i] < g_ptr[(j + 1)*g_step + i]);

			bool flag3 = (g_ptr[j*g_step + i] < g_ptr[(j - 1)*g_step + i - 1]);
			bool flag4 = (g_ptr[j*g_step + i] < g_ptr[(j + 1)*g_step + i + 1]);

			bool flag5 = (g_ptr[j*g_step + i] < g_ptr[j*g_step + i - 1]);
			bool flag6 = (g_ptr[j*g_step + i] < g_ptr[j*g_step + i + 1]);

			bool flag7 = (g_ptr[j*g_step + i] < g_ptr[(j - 1)*g_step + i + 1]);
			bool flag8 = (g_ptr[j*g_step + i] < g_ptr[(j + 1)*g_step + i - 1]);

			if (((theta[k] >= 67.5) && (theta[k] < 112.5)) || ((theta[k] <= -67.5) && (theta[k] >-112.5)))
			{
				if ((flag1) || (flag2))
					g_ptr[j*g_step + i] = 0;
			}
			else if (((theta[k] >= 112.5) && (theta[k] < 157.5)) || ((theta[k] <= -22.5) && (theta[k] > -67.5)))
			{
				if ((flag3) || (flag4))
					g_ptr[j*g_step + i] = 0;
			}
			else if (((theta[k] >= -22.5) && (theta[k] <0)) || ((theta[k] <22.5) && (theta[k] >0)) || ((theta[k] <= -157.5) && (theta[k] > -180)) || ((theta[k] >= 157.5) && (theta[k] < 180)))
			{
				if ((flag5) || (flag6))
					g_ptr[j*g_step + i] = 0;
			}
			else if (((theta[k] >= 22.5) && (theta[k] < 67.5)) || ((theta[k] <= -112.5) && (theta[k] > -157.5)))
			{
				if ((flag7) || (flag8))
					g_ptr[j*g_step + i] = 0;
			}
			k++;
		}
	}

	return gImage;
}

Mat thre(Mat restrainImage, int minthreshold, int maxthreshold)
{
	uchar* restrain_ptr = restrainImage.data;

	int restrain_step = restrainImage.step;

	for (int j = 0; j < restrainImage.rows; j++)
	{
		for (int i = 0; i < restrainImage.cols; i++)
		{
			if (restrain_ptr[j*restrain_step + i]>maxthreshold)
			{
				restrain_ptr[j*restrain_step + i] = 255;
			}
			if (restrain_ptr[j*restrain_step + i]<minthreshold)
			{
				restrain_ptr[j*restrain_step + i] = 0;
			}
		}
	}

	return restrainImage;
}

Mat LinkandFilter(Mat threImage, int minthreshold, int maxthreshold)
{
	uchar* thre_ptr = threImage.data;
	int thre_step = threImage.step;
	for (int j = 1; j < threImage.rows - 1; j++)
	{
		for (int i = 1; i < threImage.cols - 1; i++)
		{
			if ((thre_ptr[j*thre_step + i]>minthreshold) && (thre_ptr[j*thre_step + i] < maxthreshold))
			{
				for (int ii = 0; ii < 3; ii++)
				{
					for (int jj = 0; jj < 3; jj++)
					{
						if (thre_ptr[(j - 1 + ii)*thre_step + i - 1 + jj] == 255)  //>minthreshold
						{

							thre_ptr[j*thre_step + i] = 255;
						}
						else
							thre_ptr[j*thre_step + i] = 0;
					}
				}
			}
		}
	}
	return threImage;
}


void CTask4::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	destroyAllWindows();
	srcImage4 = imread("task141.bmp");
	imshow("【原图1】", srcImage4);
	minthreshold = 35;
	maxthreshold = 85;
}


void CTask4::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	destroyAllWindows();
	srcImage4 = imread("task142.jpg");
	imshow("【原图2】", srcImage4);
	minthreshold = 45;
	maxthreshold = 105;
}


void CTask4::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	Mat grayImage = RGBtogray(srcImage4);

	GaussianTemp(gaussian_temp, 3, 1);//生成高斯滤波模板

	Mat gaussianImage = GaussianFilter(grayImage);
	imshow("【高斯滤波效果图】", gaussianImage);//高斯滤波
	Mat cannyI;
	Canny(gaussianImage, cannyI, 60, 90, 3);
	imshow("cv-Canny", cannyI);
	int gx[3][3] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };
	int gy[3][3] = { 1, 1, 1, 0, 0, 0, -1, -1, -1 };

	Mat x = Mat::zeros(gaussianImage.size(), CV_8UC1);
	Mat y = Mat::zeros(gaussianImage.size(), CV_8UC1);

	int size = (gaussianImage.rows - 1)*(gaussianImage.cols - 1);
	double *theta = new double[size];

	Mat gImage = MyGvalue(gaussianImage, gx, gy, x, y, theta);
	imshow("【X方向梯度效果图】", x);
	imshow("【Y方向梯度效果图】", y);
	imshow("【梯度幅值效果图】", gImage);

	Mat restrainImage = restrainMaxval(gImage, theta);
	imshow("【非极大值抑制效果图】", restrainImage);

	Mat threImage = thre(restrainImage, minthreshold, maxthreshold);

	Mat cannyImage = LinkandFilter(threImage, minthreshold, maxthreshold);
	imshow("【Canny算子边缘提取效果图】", cannyImage);
}


void CTask4::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	destroyAllWindows();
	CTask4::OnCancel();
}
