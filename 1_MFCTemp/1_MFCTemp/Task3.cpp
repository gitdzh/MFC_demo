// Task3.cpp : 实现文件
//

#include "stdafx.h"
#include "1_MFCTemp.h"
#include "Task3.h"
#include "afxdialogex.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;

// 全局
Mat srcImage3;

// CTask3 对话框

IMPLEMENT_DYNAMIC(CTask3, CDialogEx)

CTask3::CTask3(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTask3::IDD, pParent)
{

}

CTask3::~CTask3()
{
}

void CTask3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTask3, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CTask3::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTask3::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTask3::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTask3::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTask3::OnBnClickedButton5)
END_MESSAGE_MAP()


// CTask3 消息处理程序

Mat RGBtoGray(Mat &srcImage3)
{
	Mat gray = Mat::zeros(srcImage3.size(), CV_8UC1);

	uchar* src_ptr = srcImage3.data;
	uchar* gray_ptr = gray.data;//指向图像数据的第一个字节

	int src_step = srcImage3.step;
	int gray_step = gray.step; //返回一行含有的字节数

	for (int j = 0; j < srcImage3.rows; j++)
	{
		for (int i = 0; i < srcImage3.cols; i++)
		{
			gray_ptr[gray_step*j + i] = 0.114*src_ptr[src_step*j + 3 * i] + 0.587*src_ptr[src_step*j + 3 * i + 1] + 0.299*src_ptr[src_step*j + 3 * i + 2];
		}
	}
	return gray;
}

Mat MySobel(Mat& grayImage, int sobel_gx[3][3], int sobel_gy[3][3], Mat &xsobel, Mat &ysobel)
{
	uchar* xsobel_ptr = xsobel.data;
	uchar* ysobel_ptr = ysobel.data;
	uchar* gray_ptr = grayImage.data;
	int xsobel_step = xsobel.step;
	int ysobel_step = ysobel.step;
	int gray_step = grayImage.step;
	double sumx = 0;
	double sumy = 0;

	for (int j = 1; j < grayImage.rows - 1; j++)
	{
		for (int i = 1; i < grayImage.cols - 1; i++)
		{
			sumx = gray_ptr[(j - 1)*gray_step + i - 1] * sobel_gx[0][0] + gray_ptr[(j - 1)*gray_step + i] * sobel_gx[0][1] + gray_ptr[(j - 1)*gray_step + i + 1] * sobel_gx[0][2] +
				gray_ptr[j *gray_step + i - 1] * sobel_gx[1][0] + gray_ptr[j *gray_step + i] * sobel_gx[1][1] + gray_ptr[j *gray_step + i + 1] * sobel_gx[1][2] +
				gray_ptr[(j + 1)*gray_step + i - 1] * sobel_gx[2][0] + gray_ptr[(j + 1)*gray_step + i] * sobel_gx[2][1] + gray_ptr[(j + 1)*gray_step + i + 1] * sobel_gx[2][2];

			sumy = gray_ptr[(j - 1)*gray_step + i - 1] * sobel_gy[0][0] + gray_ptr[(j - 1)*gray_step + i] * sobel_gy[0][1] + gray_ptr[(j - 1)*gray_step + i + 1] * sobel_gy[0][2] +
				gray_ptr[j *gray_step + i - 1] * sobel_gy[1][0] + gray_ptr[j *gray_step + i] * sobel_gy[1][1] + gray_ptr[j *gray_step + i + 1] * sobel_gy[1][2] +
				gray_ptr[(j + 1)*gray_step + i - 1] * sobel_gy[2][0] + gray_ptr[(j + 1)*gray_step + i] * sobel_gy[2][1] + gray_ptr[(j + 1)*gray_step + i + 1] * sobel_gy[2][2];

			if (sumx>255)
				sumx = 255;
			if (sumx < 0)
				sumx = 0;

			if (sumy>255)
				sumy = 255;
			if (sumy < 0)
				sumy = 0;

			xsobel_ptr[j*xsobel_step + i] = abs(sumx);
			ysobel_ptr[j*ysobel_step + i] = abs(sumy);
		}
	}

	Mat result(xsobel.rows, xsobel.cols + ysobel.cols + 1, xsobel.type()); // 拼接对比图
	xsobel.colRange(0, xsobel.cols).copyTo(result.colRange(0, xsobel.cols));
	ysobel.colRange(0, ysobel.cols).copyTo(result.colRange(xsobel.cols + 1, result.cols));
	imshow("【X方向(左)  Y方向(右)对比效果图】", result);

	Mat sobel = Mat::zeros(grayImage.size(), CV_8UC1);
	uchar* sobel_ptr = sobel.data;
	int sobel_step = sobel.step;
	double sumxy = 0;
	for (int j = 0; j < grayImage.rows; j++)
	{
		for (int i = 0; i < grayImage.cols; i++)
		{
			sumxy = xsobel_ptr[j*xsobel_step + i] + ysobel_ptr[j*ysobel_step + i];
			if (sumxy>255)
				sumxy = 255;
			if (sumxy < 0)
				sumxy = 0;
			sobel_ptr[j*sobel_step + i] = sumxy;
		}
	}
	return sobel;
}

void CTask3::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	srcImage3 = imread("task131.bmp");
	imshow("【原图】", srcImage3);//载入图像转灰度图
}


void CTask3::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	Mat grayImage = RGBtoGray(srcImage3);

	int sobel_gx[3][3] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	int sobel_gy[3][3] = { 1, 2, 1, 0, 0, 0, -1, -2, -1 };

	Mat xsobel = Mat::zeros(grayImage.size(), CV_8UC1);
	Mat ysobel = Mat::zeros(grayImage.size(), CV_8UC1);
	Mat sobelImage = MySobel(grayImage, sobel_gx, sobel_gy, xsobel, ysobel);

	imshow("【x与y方向合成效果图】", sobelImage);
}


void CTask3::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	//int Laplace_Temp[3][3] = { 0, 1, 0, 1, -4, 1, 0, 1, 0 };
	int Laplace_Temp[3][3] = { 1, 1, 1, 1, -8, 1, 1, 1, 1 };
	//int Laplace_Temp[3][3] = { 0, -1, 0, -1, 4, -1, 0, -1, 0 };
	//int Laplace_Temp[3][3] = { -1, -1, -1, -1, 8, -1, -1, -1, -1 };


	Mat grayImage = RGBtoGray(srcImage3);
	Mat LaplaceImage = Mat::zeros(grayImage.size(), CV_8UC1);

	uchar* Laplace_ptr = LaplaceImage.data;
	uchar* gray_ptr = grayImage.data;

	int Laplace_step = LaplaceImage.step;
	int gray_step = grayImage.step;

	double sum = 0;

	for (int j = 1; j < grayImage.rows - 1; j++)
	{
		for (int i = 1; i < grayImage.cols - 1; i++)
		{
			sum = gray_ptr[(j - 1)*gray_step + i - 1] * Laplace_Temp[0][0] + gray_ptr[(j - 1)*gray_step + i] * Laplace_Temp[0][1] + gray_ptr[(j - 1)*gray_step + i + 1] * Laplace_Temp[0][2] +
				gray_ptr[j *gray_step + i - 1] * Laplace_Temp[1][0] + gray_ptr[j *gray_step + i] * Laplace_Temp[1][1] + gray_ptr[j *gray_step + i + 1] * Laplace_Temp[1][2] +
				gray_ptr[(j + 1)*gray_step + i - 1] * Laplace_Temp[2][0] + gray_ptr[(j + 1)*gray_step + i] * Laplace_Temp[2][1] + gray_ptr[(j + 1)*gray_step + i + 1] * Laplace_Temp[2][2];

			if (sum>255)
				sum = 255;
			if (sum < 0)
				sum = 0;

			Laplace_ptr[j*Laplace_step + i] = (sum);
		}
	}
	imshow("【Laplace算子效果图】", LaplaceImage);
}


void CTask3::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	destroyAllWindows();
	CTask3::OnCancel();
}


void CTask3::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码
	int Laplace_Temp[3][3] = { 1, 1, 1, 1, -8, 1, 1, 1, 1 };
	//int Laplace_Temp[3][3] = { 0, -1, 0, -1, 4, -1, 0, -1, 0 };
	//int Laplace_Temp[3][3] = { -1, -1, -1, -1, 8, -1, -1, -1, -1 };


	Mat grayImage = RGBtoGray(srcImage3);
	Mat LaplaceImage = Mat::zeros(grayImage.size(), CV_8UC1);

	uchar* Laplace_ptr = LaplaceImage.data;
	uchar* gray_ptr = grayImage.data;

	int Laplace_step = LaplaceImage.step;
	int gray_step = grayImage.step;

	double sum = 0;

	for (int j = 1; j < grayImage.rows - 1; j++)
	{
		for (int i = 1; i < grayImage.cols - 1; i++)
		{
			sum = gray_ptr[(j - 1)*gray_step + i - 1] * Laplace_Temp[0][0] + gray_ptr[(j - 1)*gray_step + i] * Laplace_Temp[0][1] + gray_ptr[(j - 1)*gray_step + i + 1] * Laplace_Temp[0][2] +
				gray_ptr[j *gray_step + i - 1] * Laplace_Temp[1][0] + gray_ptr[j *gray_step + i] * Laplace_Temp[1][1] + gray_ptr[j *gray_step + i + 1] * Laplace_Temp[1][2] +
				gray_ptr[(j + 1)*gray_step + i - 1] * Laplace_Temp[2][0] + gray_ptr[(j + 1)*gray_step + i] * Laplace_Temp[2][1] + gray_ptr[(j + 1)*gray_step + i + 1] * Laplace_Temp[2][2];

			if (sum>255)
				sum = 255;
			if (sum < 0)
				sum = 0;

			Laplace_ptr[j*Laplace_step + i] = (sum);
		}
	}
	Mat IncreaseImage = Mat::zeros(grayImage.size(), grayImage.type());

	uchar* increase_ptr = IncreaseImage.data;
	int increase_step = IncreaseImage.step;

	for (int j = 0; j<grayImage.rows; j++)
	{
		for (int i = 0; i < grayImage.cols; i++)
		{
			increase_ptr[j*increase_step + i] = saturate_cast<uchar>(gray_ptr[j*Laplace_step + i] - Laplace_ptr[j*Laplace_step + i]);
		}
	}
	imshow("【Laplace算子图像增强效果图】", IncreaseImage);

}
