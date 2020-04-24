// 9_1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat hog = cv::imread("D:\\hogTemplate.jpg");
	cv::Mat img1 = cv::imread("D:\\img1.jpg");
	cv::Mat img2 = cv::imread("D:\\img2.jpg");

	float n1 = 0;
	float n2 = 0;
	float m1 = 0;
	float m2 = 0;

	Mat gx, gy;
	Mat mag, angle;
	Sobel(hog, gx, CV_32F, 1, 0, 1);
	Sobel(hog, gy, CV_32F, 0, 1, 1);
	cartToPolar(gx, gy, mag, angle, true);

	Mat gx1, gy1;
	Mat mag1, angle1;
	Sobel(img1, gx1, CV_32F, 1, 0, 1);
	Sobel(img1, gy1, CV_32F, 0, 1, 1);
	cartToPolar(gx1, gy1, mag1, angle1, true);

	Mat gx2, gy2;
	Mat mag2, angle2;
	Sobel(img2, gx2, CV_32F, 1, 0, 1);
	Sobel(img2, gy2, CV_32F, 0, 1, 1);
	cartToPolar(gx2, gy2, mag2, angle2, true);

	int cellSize = 16;
	int nX = hog.cols / cellSize;
	int nY = hog.rows / cellSize;

	for (int a = 0; a < nX; a++) {
		for (int b = 0; b < nY; b++) {
			float* hist = new float[8];
			memset(hist, 0, sizeof(float) * 8);
			float* hist1 = new float[8];
			memset(hist1, 0, sizeof(float) * 8);
			float* hist2 = new float[8];
			memset(hist2, 0, sizeof(float) * 8);
			for (int i = 0; i < cellSize; ++i) {
				for (int j = 0; j < cellSize; ++j) {
					int c = angle.at<float>(i + 16 * a, j + 16 * b) / 45;
					hist[c] += mag.at<float>(i + 16 * a, j + 16 * a);
					int d = angle1.at<float>(i + 16 * a, j + 16 * b) / 45;
					hist1[d] += mag1.at<float>(i + 16 * a, j + 16 * a);
					int e = angle2.at<float>(i + 16 * a, j + 16 * b) / 45;
					hist2[e] += mag2.at<float>(i + 16 * a, j + 16 * a);
				}
			}
			n1 = 0;
			for (int k = 0; k < 8; k++) {
				n1 += (hist[k] - hist1[k])*(hist[k] - hist1[k]);
			}
			n2 = 0;
			for (int k = 0; k < 8; k++) {
				n2 += (hist[k] - hist2[k])*(hist[k] - hist2[k]);
			}
			m1 += sqrt(n1);
			m2 += sqrt(n2);
			delete[] hist;
			delete[] hist1;
			delete[] hist2;
		}
	}
	if (m1 > m2) {
		std::cout << "与参考图像相似度高的是img2" << std::endl;
	}
	else {
		std::cout << "与参考图像相似度高的是img1" << std::endl;
	}
	waitKey(0);
	return 0;
}


