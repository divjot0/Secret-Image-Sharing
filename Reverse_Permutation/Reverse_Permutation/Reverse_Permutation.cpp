// Reverse_Permutation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2\highgui.hpp>
#include <fstream>
#include <algorithm>    // std::next_permutation, std::sort
#include <iostream> 
#include <vector>

using namespace cv;
using namespace std;

int main() {

	string str;
	cout << "Enter Image Path:\t";
	cin >> str;

	Mat original = imread(str, CV_LOAD_IMAGE_COLOR);

	if (!original.data)
	{
		cout << "Image failed to load!" << endl;
		return 1;
	}

	vector<int> myints(original.rows*original.cols);

	ifstream myfile;
	myfile.open("permu.txt");
	int c;
	for (int i = 0; i < original.rows*original.cols; ++i)
	{
		myfile >> c;
		myints[i] = c;
	}
	myfile.close();

	int cur = 0;
	Mat New = Mat((int)(original.rows), (int)(original.cols), original.type());
	for (int i = 0; i < (int)(original.rows); ++i)
	{
		for (int j = 0; j < (int)(original.cols); ++j)
		{
			New.at<Vec3b>(myints[cur] / original.cols, myints[cur] % original.cols)[0] = original.at<Vec3b>(i, j)[0];
			New.at<Vec3b>(myints[cur] / original.cols, myints[cur] % original.cols)[1] = original.at<Vec3b>(i, j)[1];
			New.at<Vec3b>(myints[cur] / original.cols, myints[cur] % original.cols)[2] = original.at<Vec3b>(i, j)[2];
			cur++;
		}
	}

	imwrite("Image.jpg", New);
	return 0;
}


