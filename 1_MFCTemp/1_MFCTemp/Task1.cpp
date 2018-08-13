// Task1.cpp : 实现文件
//

#include "stdafx.h"
#include "1_MFCTemp.h"
#include "Task1.h"
#include "afxdialogex.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;

// 全局变量
Mat srcImage1;
float src_Sumprobability[256] = { 0 };
float dst_Sumprobability[256] = { 0 };

// CTask1 对话框

IMPLEMENT_DYNAMIC(CTask1, CDialogEx)

CTask1::CTask1(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTask1::IDD, pParent)
{

}

CTask1::~CTask1()
{
}

void CTask1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_1);
	DDX_Control(pDX, IDC_CHECK2, m_2);
}


BEGIN_MESSAGE_MAP(CTask1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CTask1::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTask1::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTask1::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_CHECK1, &CTask1::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CTask1::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_BUTTON4, &CTask1::OnBnClickedButton4)
END_MESSAGE_MAP()


// CTask1 消息处理程序

Mat draw_grayHist(Mat &Image, Scalar color)
{
	int bins = 256;
	int hist_size[] = { bins };
	float range[] = { 0, 256 };
	const float* ranges[] = { range };
	MatND hist;
	int channels[] = { 0 };

	calcHist(&Image, 1, channels, Mat(), // do not use mask  
		hist, 1, hist_size, ranges,
		true, // the histogram is uniform  
		false);

	double max_val;
	minMaxLoc(hist, 0, &max_val, 0, 0);
	int scale = 2;
	int hist_height = 256;
	Mat hist_img = Mat::zeros(hist_height, bins*scale, CV_8UC3);
	for (int i = 0; i<bins; i++)
	{
		float bin_val = hist.at<float>(i);
		int intensity = cvRound(bin_val*hist_height / max_val);  //要绘制的高度  
		rectangle(hist_img, Point(i*scale, hist_height - 1),
			Point((i + 1)*scale - 1, hist_height - intensity),
			color);
	}

	return hist_img;
}


void CTask1::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	srcImage1 = imread("task111.jpg");
	cvtColor(srcImage1, srcImage1, CV_BGR2GRAY);

	imshow("【原图】", srcImage1);
}


void CTask1::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	Mat dstImage = Mat::zeros(srcImage1.size(), CV_8UC1);
	int bin = 256;
	float sumprobability = 0;

	for (int k = 0; k < bin; k++)
	{
		int s = 0;
		for (int j = 0; j < srcImage1.rows; j++)
		{
			uchar* data = srcImage1.ptr<uchar>(j);
			for (int i = 0; i < srcImage1.cols; i++)
			{
				if (k == data[i])
				{
					s++;
				}
			}
		}
		float probability = (float)s / (srcImage1.rows*srcImage1.cols);
		sumprobability += probability;
		for (int j = 0; j < srcImage1.rows; j++)
		{
			uchar* data = srcImage1.ptr<uchar>(j);
			uchar* dst1 = dstImage.ptr<uchar>(j);
			for (int i = 0; i < srcImage1.cols; i++)
			{
				if (k == data[i])
				{
					dst1[i] = sumprobability * 255 + 0.5;  //四舍五入
				}
			}
		}
	}

	Mat result(srcImage1.rows, srcImage1.cols + dstImage.cols + 1, srcImage1.type()); // 拼接对比图
	srcImage1.colRange(0, srcImage1.cols).copyTo(result.colRange(0, srcImage1.cols));
	dstImage.colRange(0, dstImage.cols).copyTo(result.colRange(srcImage1.cols + 1, result.cols));
	imshow("【均衡化对比效果图】", result);

	Mat src_HistImage = draw_grayHist(srcImage1, Scalar(0, 255, 0));
	Mat dst_HistImage = draw_grayHist(dstImage, Scalar(255, 0, 0));

	Mat hist_result(src_HistImage.rows, src_HistImage.cols + dst_HistImage.cols + 1, src_HistImage.type()); // 拼接直方图
	src_HistImage.colRange(0, src_HistImage.cols).copyTo(hist_result.colRange(0, src_HistImage.cols));
	dst_HistImage.colRange(0, dst_HistImage.cols).copyTo(hist_result.colRange(src_HistImage.cols + 1, hist_result.cols));
	imshow("【直方图对比效果图】", hist_result);
}


void CTask1::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	int bin = 256;
	float src_sumprobability = 0;

	for (int k = 0; k < bin; k++)
	{
		int s = 0;
		for (int j = 0; j < srcImage1.rows; j++)
		{
			uchar* data = srcImage1.ptr<uchar>(j);
			for (int i = 0; i < srcImage1.cols; i++)
			{
				if (k == data[i])
				{
					s++;//得到原图像的r[k]对应的n[k]
				}
			}
		}
		float src_probability = (float)s / (srcImage1.rows*srcImage1.cols);//求原图像的p[r](r[k])
		src_sumprobability += src_probability;//求原图像的累积p(r[k])
		src_Sumprobability[k] = src_sumprobability;
	}

	float dst_sumprobability = 0;
	if (m_1.GetCheck() == 1)
	{
		for (int k = 0; k < bin; k++)
		{
			float c = 0.25;
			float dst_probability = c*log(1 + k);

			dst_sumprobability += dst_probability;//求目标图像的累积p(r[k])
			dst_Sumprobability[k] = dst_sumprobability;
		}
		for (int k = 0; k < bin; k++)
		{
			dst_Sumprobability[k] /= dst_sumprobability;
		}
	}
	else
	{
		Mat dstImage = imread("task112.jpg");
		cvtColor(dstImage, dstImage, CV_BGR2GRAY);

		imshow("【目标图像】", dstImage);
		Mat dst_Hist = draw_grayHist(dstImage, Scalar(0, 255, 0));
		imshow("【目标图像直方图】", dst_Hist);
		for (int k = 0; k < bin; k++)
		{
			int s = 0;
			for (int j = 0; j < dstImage.rows; j++)
			{
				uchar* data = dstImage.ptr<uchar>(j);
				for (int i = 0; i < dstImage.cols; i++)
				{
					if (k == data[i])
					{
						s++;//得到目标图像的r[k]对应的n[k]
					}
				}
			}
			float dst_probability = (float)s / (dstImage.rows*dstImage.cols);//求目标图像的p[r](r[k])
			dst_sumprobability += dst_probability;//求目标图像的累积p(r[k])
			dst_Sumprobability[k] = dst_sumprobability;
		}
	}

	int new_graylevel[256];//用于存放新的灰度

	for (int src = 0; src < 256; src++)
	{
		for (int dst = 0; dst < 256; dst++)
		{
			if ((src_Sumprobability[src] >= dst_Sumprobability[dst]) && (src_Sumprobability[src] <= dst_Sumprobability[dst + 1]))
			{
				if (abs(src_Sumprobability[src] - dst_Sumprobability[dst]) <= abs(src_Sumprobability[src] - dst_Sumprobability[dst + 1]))
				{
					new_graylevel[src] = dst;
				}
				else
				{
					new_graylevel[src] = dst + 1;
				}
			}
		}
	}

	Mat newImage = Mat::zeros(srcImage1.size(), srcImage1.type());
	for (int k = 0; k < bin; k++)
	{

		for (int j = 0; j < srcImage1.rows; j++)
		{
			uchar* data = srcImage1.ptr<uchar>(j);
			uchar* newdata = newImage.ptr<uchar>(j);
			for (int i = 0; i < srcImage1.cols; i++)
			{
				if (k == data[i])
				{
					newdata[i] = new_graylevel[k];
				}
			}
		}
	}

	imshow("【直方图规定化效果图】", newImage);
	Mat new_Hist = draw_grayHist(newImage, Scalar(255, 0, 0));
	imshow("【规定化图像直方图】", new_Hist);
}


void CTask1::OnBnClickedCheck1()
{
	// TODO:  在此添加控件通知处理程序代码
	m_2.SetCheck(0);
}


void CTask1::OnBnClickedCheck2()
{
	// TODO:  在此添加控件通知处理程序代码
	m_1.SetCheck(0);
}


void CTask1::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	destroyAllWindows();
}
