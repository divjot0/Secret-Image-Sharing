// Colored_Image_Sharing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2\opencv.hpp"
#include <vector>

using namespace std;
using namespace cv;

int main()
{
	int n, r;
	string name;
	cout << "Enter the image: ";
	cin >> name;
	Mat image = imread(name, CV_LOAD_IMAGE_COLOR);
	/*
	Mat image = Mat::zeros(Size(2, 4), CV_8UC1);
	image.at<unsigned char>(0, 0) = 250;
	image.at<unsigned char>(1, 0) = 200;
	image.at<unsigned char>(2, 0) = 50;
	image.at<unsigned char>(3, 0) = 100;
	image.at<unsigned char>(0, 1) = 250;
	image.at<unsigned char>(1, 1) = 200;
	image.at<unsigned char>(2, 1) = 50;
	image.at<unsigned char>(3, 1) = 100;
	*/
	cout << "Enter the number of shadow images to be made: ";
	cin >> n;
	cout << "Enter the number of images required to uncover the original image: ";
	cin >> r;
	vector<Mat> shadow;
	vector<string> name_image;
	for (int i = 0; i < n; i++) {
		string temp = to_string(i);
		name_image.push_back(temp);
	}
	for (int i = 0; i < n; i++) {
		Mat shadow_temp = Mat::zeros(Size(image.cols / r, image.rows), CV_8UC3);
		shadow.push_back(shadow_temp);
	}
	vector<int> arr;
	vector<int> arr2;
	vector<int> arr3;
	for (int i = 0; i < r; i++) {
		arr.push_back(0);
		arr2.push_back(0);
		arr3.push_back(0);
	}
	int k = 0;
	int row = 0, col = 0;
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			if (k < r - 1) {
				if (image.at<Vec3b>(i, j)[0] <= 250) {
					arr[k] = image.at<Vec3b>(i, j)[0];
				}
				else {
					arr[k] = 250;
				}
				if (image.at<Vec3b>(i, j)[1] <= 250) {
					arr2[k] = image.at<Vec3b>(i, j)[1];
				}
				else {
					arr2[k] = 250;
				}
				if (image.at<Vec3b>(i, j)[2] <= 250) {
					arr3[k] = image.at<Vec3b>(i, j)[2];
				}
				else {
					arr3[k] = 250;
				}
				k++;
			}
			else if (k == r - 1) {
				if (image.at<Vec3b>(i, j)[0] <= 250) {
					arr[k] = image.at<Vec3b>(i, j)[0];
				}
				else {
					arr[k] = 250;
				}
				if (image.at<Vec3b>(i, j)[1] <= 250) {
					arr2[k] = image.at<Vec3b>(i, j)[1];
				}
				else {
					arr2[k] = 250;
				}
				if (image.at<Vec3b>(i, j)[2] <= 250) {
					arr3[k] = image.at<Vec3b>(i, j)[2];
				}
				else {
					arr3[k] = 250;
				}
				k = 0;
				for (int t = 0; t < n; t++) {
					int temp = 0;
					int temp2 = 0;
					int temp3 = 0;
					for (int m = 0; m < r; m++) {
						temp = temp + (arr[m] * pow(t + 1, m));
						temp = temp % 251;
						temp2 = temp2 + (arr2[m] * pow(t + 1, m));
						temp2 = temp2 % 251;
						temp3 = temp3 + (arr3[m] * pow(t + 1, m));
						temp3 = temp3 % 251;
					}
					if (row < shadow[t].rows && col < shadow[t].cols) {

						shadow[t].at<Vec3b>(row, col)[0] = temp;
						shadow[t].at<Vec3b>(row, col)[1] = temp2;
						shadow[t].at<Vec3b>(row, col)[2] = temp3;
					}

				}
				if (col == (shadow[0].cols - 1)) {
					row++;
					col = 0;
				}
				else {
					col++;
				}
			}
		}
	}

	imshow("Input_image", image);
	for (int i = 0; i < n; i++) {
		imshow(name_image[i], shadow[i]);
		string name;
		name = name_image[i] + ".tiff";
		imwrite(name, shadow[i]);
	}
	waitKey();
	return 0;
}

