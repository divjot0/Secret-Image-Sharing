#include <iostream>
#include <vector>
#include <algorithm>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <fstream>

using namespace std;
using namespace cv;

int main()
{
    int cur=0;

    string str;
    cout << "Enter the secret images' path:\t";
    cin >> str;
    Mat original = imread(str, CV_LOAD_IMAGE_GRAYSCALE);
	Mat New = Mat((int)(original.rows), (int)(original.cols), original.type());
    int myints[original.rows*original.cols];
    cout << "HI" << endl;
	ifstream myfile;
	myfile.open("permu.txt");
	int c;
	for (int i = 0; i < original.rows*original.cols; ++i)
	{
		myfile >> c;
		myints[i] = c;
	}
	myfile.close();

    int e=0;
	int min = 251;
    cout << "HI" << endl;
    for (int i = 0; i < original.rows; ++i)
	{
		for (int j = 0; j < original.cols; ++j)
		{
			if (original.at<unsigned char>(i, j)>250)
			{
				original.at<unsigned char>(i, j) = 250;
			}
		}
	}
	e=0;
	cout << "HI" << endl;
	for (int i = 0; i < original.rows; ++i)
	{
		for (int j = 0; j < original.cols; ++j)
		{
			New.at<unsigned char>(i, j) = original.at<unsigned char>(myints[e]/original.cols, myints[e]%original.cols);
			e++;
		}
	}

	string a = "PermutedImage.jpg";
	imwrite(a, New);
    return 0;
}
