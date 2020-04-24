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
	int count = 0;

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

	float h[100][8];
	float h1[100][8];
	float h2[100][8];

	for (int a = 0; a < nX; a++) {
		for (int b = 0; b < nY; b++) {
			float* hist = new float[8];
			memset(hist, 0, sizeof(float) * 8);
			float* hist1 = new float[8];
			memset(hist1, 0, sizeof(float) * 8);
			float* hist2 = new float[8];
			memset(hist2, 0, sizeof(float) * 8);
			for (int i = 0; i < cellSize; i++) {
				for (int j = 0; j < cellSize; j++) {
					int c = angle.at<float>(i + 16 * a, j + 16 * b) / 45;
					hist[c] += mag.at<float>(i + 16 * a, j + 16 * b);
					int d = angle1.at<float>(i + 16 * a, j + 16 * b) / 45;
					hist1[d] += mag1.at<float>(i + 16 * a, j + 16 * b);
					int e = angle2.at<float>(i + 16 * a, j + 16 * b) / 45;
					hist2[e] += mag2.at<float>(i + 16 * a, j + 16 * b);
				}
			}
			for (int q = 0; q < 8; q++) {
				h[count][q] = hist[q];
				h1[count][q] = hist1[q];
				h2[count][q] = hist2[q];
			}
			count += 1;
			delete[] hist;
			delete[] hist1;
			delete[] hist2;
		}
	}
	for (int l = 0; l < nX * nY; l++) {
		for (int k = 0; k < 8; k++) {
			n1 += (h[l][k] - h1[l][k])*(h[l][k] - h1[l][k]);
		}
	}
	for (int l = 0; l < nX * nY; l++) {
		for (int k = 0; k < 8; k++) {
			n2 += (h[l][k] - h2[l][k])*(h[l][k] - h2[l][k]);
		}
	}
	float m1 = sqrt(n1);
	float m2 = sqrt(n2);
	if (m1 > m2) {
		std::cout << "与参考图像相似度高的是img2" << std::endl;
	}
	else {
		std::cout << "与参考图像相似度高的是img1" << std::endl;
	}
	waitKey(0);
	return 0;
}


