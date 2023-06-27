//Jose Joseph Thandapral
//CS5330
//Project 1 : Real-time filtering
// The following is the definition of the function prototypes
//that implements the real-time filtering project

#include<opencv2/opencv.hpp>
#include <iostream>
#include<math.h>
using namespace cv;

//The given function converts an input image from color to grayscale by calculating 
//the average value of each pixel's RGB channels and assigning it to all three 
//channels of the corresponding pixel in the destination image
int greyscale(cv::Mat& src, cv::Mat& dst)
{
	for (int i = 0; i < src.rows; ++i)
	{
		cv::Vec3b* rptrs = src.ptr <cv::Vec3b>(i);
		cv::Vec3b* rptrd = dst.ptr <cv::Vec3b>(i);
		for (int j = 0; j < src.cols; ++j)
		{
			uchar avg = (rptrs[j][0] + rptrs[j][1] + rptrs[j][2]) / 3;
			rptrd[j][0] = avg;
			rptrd[j][1] = avg;
			rptrd[j][2] = avg;
		}
	}
	return 0;
}

//The given function applies a 5x5 blur filter to an input image, first horizontally 
//and then vertically, and stores the result in the destination image.
/*

The kernel used for blurring in this code is a 5x5 matrix representation. It has the following values:

[1 2 4 2 1]
[2 4 8 4 2]
[4 8 16 8 4]
[2 4 8 4 2]
[1 2 4 2 1]

This kernel represents a symmetric filter, where the center element has the highest weight and the weights decrease symmetrically towards the edges. It is commonly used for blurring operations to achieve a smooth and softened effect on the image. The weights in the kernel determine the contribution of neighboring pixels in the blurring process.

*/
int blur5x5(cv::Mat& src, cv::Mat& dst)
{
	cv::Mat temp;
	src.copyTo(temp);

	for (int i = 2; i < (temp.rows - 3); ++i)
	{
		const cv::Vec3b* rptrs = src.ptr<cv::Vec3b>(i);
		cv::Vec3b* rptrd = temp.ptr<cv::Vec3b>(i);

		for (int j = 2; j < (temp.cols - 3); ++j)
		{
			rptrd[j][0] = (
				(rptrs[j - 2][0] + 2 * rptrs[j - 1][0] + 4 * rptrs[j][0] + 2 * rptrs[j + 1][0] + rptrs[j + 2][0]) * 0.1
				);
			rptrd[j][1] = (
				(rptrs[j - 2][1] + 2 * rptrs[j - 1][1] + 4 * rptrs[j][1] + 2 * rptrs[j + 1][1] + rptrs[j + 2][1]) * 0.1
				);
			rptrd[j][2] = (
				(rptrs[j - 2][2] + 2 * rptrs[j - 1][2] + 4 * rptrs[j][2] + 2 * rptrs[j + 1][2] + rptrs[j + 2][2]) * 0.1
				);
		}
	}

	return 0;
}

// Function impelementing the following 3x3 Sobel filter
//[ -1 0 1]
//[ -2 0 2]
//[ -1 0 1]
int sobelX3x3(cv::Mat& src, cv::Mat& dst)
{
	cv::Mat temp = cv::Mat::zeros(src.size(), CV_16SC3);
	cv::Mat temp2 = cv::Mat::zeros(src.size(), CV_16SC3);

	// Horizontal filter
	for (int i = 1; i < src.rows - 1; ++i)
	{
		cv::Vec3b* rptr = src.ptr<cv::Vec3b>(i);
		cv::Vec3s* dptr = temp.ptr<cv::Vec3s>(i);

		for (int j = 1; j < src.cols - 1; ++j)
		{
			for (int c = 0; c <= 2; c++)
			{
				dptr[j][c] = (-1 * rptr[j - 1][c] + rptr[j + 1][c]) / 2;
			}
		}
	}

	// Vertical filter
	for (int i = 1; i < src.rows - 1; ++i)
	{
		cv::Vec3s* rptr = temp.ptr<cv::Vec3s>(i);
		cv::Vec3s* dptr = temp2.ptr<cv::Vec3s>(i);

		for (int j = 1; j < src.cols - 1; ++j)
		{
			for (int c = 0; c <= 2; c++)
			{
				dptr[j][c] = (-1 * rptr[j - 1][c] + rptr[j + 1][c]) / 2;
			}
		}
	}

	temp2.copyTo(dst);
	return 0;
}


// For the following 3x3 Sobel filter
//[ 1 2 1]
//[ 0 0 0] 
//[ -1 -2 -1]
int sobelY3x3(cv::Mat& src, cv::Mat& dst)
{
	cv::Mat temp = cv::Mat::zeros(src.size(), CV_16SC3);

	for (int i = 1; i < src.rows - 1; ++i)
	{
		cv::Vec3b* rptrm1 = src.ptr <cv::Vec3b>(i - 1);
		cv::Vec3b* rptr = src.ptr <cv::Vec3b>(i);
		cv::Vec3b* rptrp1 = src.ptr <cv::Vec3b>(i + 1);

		cv::Vec3s* dptr = temp.ptr <cv::Vec3s>(i);
		for (int j = 1; j < src.cols - 1; ++j)
		{
			for (int c = 0; c <= 2; c++)
			{
				dptr[j][c] = (1 * rptrm1[j - 1][c] + 2 * rptrm1[j][c] + rptrm1[j + 1][c]
					- 1 * rptrp1[j - 1][c] - 2 * rptrp1[j][c] - rptrp1[j + 1][c]) / 4;
			}
		}
	}

	temp.copyTo(dst);
	return 0;


}

int blurQuantize(cv::Mat& src, cv::Mat& dst, int levels)
{
	blur5x5(src, dst);
	int bucket = 255 / levels;
	for (int i = 0; i < src.rows; ++i)
	{
		cv::Vec3b* rptrd = dst.ptr <cv::Vec3b>(i);
		for (int j = 1; j < src.cols; ++j)
		{
			rptrd[j][0] = (rptrd[j][0] / bucket) * bucket;
			rptrd[j][1] = (rptrd[j][1] / bucket) * bucket;
			rptrd[j][2] = (rptrd[j][2] / bucket) * bucket;
		}
	}
	return 0;
}



int magnitude(cv::Mat& sx, cv::Mat& sy, cv::Mat& dst)
{
	dst = cv::Mat::zeros(sx.size(), sx.type());
	for (int i = 0; i < sx.rows; ++i)
	{
		cv::Vec3b* rptrsx = sx.ptr <cv::Vec3b>(i);
		cv::Vec3b* rptrsy = sy.ptr <cv::Vec3b>(i);
		cv::Vec3b* rptrd = dst.ptr <cv::Vec3b>(i);
		for (int j = 0; j < sx.cols; ++j)
		{
			rptrd[j][0] = sqrt((rptrsx[j][0] * rptrsx[j][0]) + (rptrsy[j][0] * rptrsy[j][0]));
			rptrd[j][1] = sqrt((rptrsx[j][1] * rptrsx[j][1]) + (rptrsy[j][1] * rptrsy[j][1]));
			rptrd[j][2] = sqrt((rptrsx[j][2] * rptrsx[j][2]) + (rptrsy[j][2] * rptrsy[j][2]));
		}
	}
	return 0;
}

int cartoon(cv::Mat& src, cv::Mat& dst, int levels, int magThreshold)
{
	cv::Mat sobelXdisplaysrc;
	cv::Mat sobelYdisplaysrc;
	cv::Mat gradsrc;
	cv::Mat magImage;
	sobelX3x3(src, gradsrc);
	cv::convertScaleAbs(gradsrc, sobelXdisplaysrc);
	sobelY3x3(src, gradsrc);
	cv::convertScaleAbs(gradsrc, sobelYdisplaysrc);
	magImage.create(src.size(), src.type());
	magnitude(sobelXdisplaysrc, sobelYdisplaysrc, magImage);
	dst = cv::Mat::zeros(src.size(), src.type());
	cv::Mat blurQuantImage;
	blurQuantize(src, blurQuantImage, levels);
	for (int i = 0; i < blurQuantImage.rows; ++i)
	{
		cv::Vec3b* rptrs = blurQuantImage.ptr <cv::Vec3b>(i);
		cv::Vec3b* rptrg = magImage.ptr <cv::Vec3b>(i);
		cv::Vec3b* rptrd = dst.ptr <cv::Vec3b>(i);
		for (int j = 0; j < blurQuantImage.cols; ++j)
		{
			for (int c = 0; c < 2; c++)
			{
				if (rptrg[j][c] > magThreshold)
				{
					rptrd[j][c] = 0;
				}
				else
				{
					rptrd[j][c] = rptrs[j][c];
				}
			}
		}
	}
	return 0;
}

//task 10: Making a negative of the image
int negative(cv::Mat& src, cv::Mat& dst)
{
	dst = cv::Mat::zeros(src.size(), src.type());
	for (int i = 0; i < src.rows; ++i)
	{
		cv::Vec3b* rptrs = src.ptr <cv::Vec3b>(i);
		cv::Vec3b* rptrd = dst.ptr <cv::Vec3b>(i);
		for (int j = 1; j < src.cols; ++j)
		{
			rptrd[j][0] = 255 - rptrs[j][0];
			rptrd[j][1] = 255 - rptrs[j][1];
			rptrd[j][2] = 255 - rptrs[j][2];
		}
	}
	return 0;
}