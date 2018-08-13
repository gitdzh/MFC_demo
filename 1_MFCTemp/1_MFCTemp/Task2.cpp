// Task2.cpp : 实现文件
//

#include "stdafx.h"
#include "1_MFCTemp.h"
#include "Task2.h"
#include "afxdialogex.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;
// 全局
Mat srcImage2;
float Mean_Template[3][3] = { 0 };

// CTask2 对话框

IMPLEMENT_DYNAMIC(CTask2, CDialogEx)

CTask2::CTask2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTask2::IDD, pParent)
{

}

CTask2::~CTask2()
{
}

void CTask2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTask2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CTask2::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTask2::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTask2::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTask2::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTask2::OnBnClickedButton5)
END_MESSAGE_MAP()


// CTask2 消息处理程序

Mat Mean(float Mean_Temp[][3])
{
	Mat Mean_result;

	Mean_result.create(srcImage2.size(), srcImage2.type());

	for (int j = 1; j<srcImage2.rows - 1; j++)
	{
		const uchar* up = srcImage2.ptr<const uchar>(j - 1);//上  
		const uchar* center = srcImage2.ptr<const uchar>(j);//中 
		const uchar* down = srcImage2.ptr<const uchar>(j + 1);//下 
		uchar * result = Mean_result.ptr<uchar>(j);//输出图像的第i行  
		int channel = srcImage2.channels();
		for (int i = srcImage2.channels(); i < (srcImage2.cols - 1)* channel; i++)
		{
			result[i] = saturate_cast<uchar>(up[i - channel] * Mean_Temp[0][0] + up[i] * Mean_Temp[0][1] + up[i + channel] * Mean_Temp[0][2] +
				center[i - channel] * Mean_Temp[1][0] + center[i] * Mean_Temp[1][1] + center[i + channel] * Mean_Temp[1][2] +
				down[i - channel] * Mean_Temp[2][0] + down[i] * Mean_Temp[2][1] + down[i + channel] * Mean_Temp[2][2]);
		}
	}
	//将最外围一圈的像素值设为0  
	Mean_result.row(0).setTo(Scalar(0));
	Mean_result.row(Mean_result.rows - 1).setTo(Scalar(0));
	Mean_result.col(0).setTo(Scalar(0));
	Mean_result.col(Mean_result.cols - 1).setTo(Scalar(0));
	return Mean_result;
}

void CTask2::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	srcImage2 = imread("task121.jpg");
	imshow("【原图】", srcImage2);
}


void CTask2::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	Mat Mean_result = Mean(Mean_Template);
	imshow("【均值滤波效果图】", Mean_result);
}


void CTask2::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	Mat MedianImage = Mat::zeros(srcImage2.size(), srcImage2.type());
	int b[9] = { 0 };
	int t = 0;
	for (int j = 1; j < srcImage2.rows - 1; j++)
	{
		uchar* up = srcImage2.ptr<uchar>(j - 1);
		uchar* center = srcImage2.ptr<uchar>(j);
		uchar* down = srcImage2.ptr<uchar>(j + 1);
		uchar* data = MedianImage.ptr<uchar>(j);
		int channel = srcImage2.channels();

		for (int i = 1; i < (srcImage2.cols - 1)* channel; i++)
		{
			b[0] = up[i - channel];
			b[1] = up[i];
			b[2] = up[i + channel];
			b[3] = center[i - channel];
			b[4] = center[i];
			b[5] = center[i + channel];
			b[6] = down[i - channel];
			b[7] = down[i];
			b[8] = down[i + channel];
			for (int x = 0; x < 8; x++)
			{
				for (int y = x + 1; y < 9; y++)
				{
					if (b[x]>b[y])
					{
						t = b[x];
						b[x] = b[y];
						b[y] = t;
					}
				}
			}
			data[i] = b[4];
		}
	}
	imshow("【中值滤波效果图】", MedianImage);
}


void CTask2::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码	
	int sum = 3 * 3;
	for (int i = 0; i <3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Mean_Template[i][j] = 1.0 / sum;
		}
	}
	MessageBox(_T("已为您生成均值滤波模板！"), NULL, MB_ICONINFORMATION);
}


void CTask2::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码
	destroyAllWindows();
	CTask2::OnCancel();
}
