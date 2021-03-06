#include "stdafx.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include "opencv2\opencv.hpp"


using namespace std;
using namespace cv;

typedef struct {
	double x;
	double y;
} point_t;


int modInverse(int a, int m)
{
	int m0 = m;
	int y = 0, x = 1;

	if (m == 1)
		return 0;

	while (a > 1)
	{
		// q is quotient
		int q = a / m;
		int t = m;

		// m is remainder now, process same as
		// Euclid's algo
		m = a % m, a = t;
		t = y;

		// Update y and x
		y = x - q * y;
		x = t;
	}

	// Make x positive
	if (x < 0)
		x += m0;

	return x;
}

long gcd(long a, long b)
{
	if (a == 0)
		return b;
	else if (b == 0)
		return a;

	if (a < b)
		return gcd(a, b % a);
	else
		return gcd(b, a % b);
}

int foo(double input)
{
	double integral = std::floor(input);
	double frac = input - integral;

	const long precision = 1000000000; // This is the accuracy.

	long gcd_ = gcd(round(frac * precision), precision);

	long denominator = precision / gcd_;
	long numerator = round(frac * precision) / gcd_;

	int result = (int(integral)) % 251;
	result = result + (numerator % 251)*(modInverse(denominator, 251));
	result = result % 251;
	return result;
}

/**
* Generate the polynomials coefficients of the lagrange interpolation polynomial
* for the given points
*/
vector<double>* lagrange_coeffs(const vector<point_t> points) {
	auto len = points.size();
	auto res = new vector<double>(len, 0);

	for (auto curpoint : points) {
		vector<double> tmpcoeffs(len, 0);
		// Start with a constant polynomial
		tmpcoeffs[0] = curpoint.y;
		double prod = 1;
		for (auto point : points) {
			if (curpoint.x == point.x) continue;
			prod *= curpoint.x - point.x;
			double precedent = 0;
			for (auto resptr = tmpcoeffs.begin(); resptr < tmpcoeffs.end(); resptr++) {
				// Compute the new coefficient of X^i based on
				// the old coefficients of X^(i-1) and X^i
				double newres = (*resptr) * (-point.x) + precedent;
				precedent = *resptr;
				*resptr = newres;
			}
		}
		transform(res->begin(), res->end(),
			tmpcoeffs.begin(),
			res->begin(),
			[=](double oldcoeff, double add) {return oldcoeff + add / prod; }
		);
	}
	return res;
}


int main()
{
	vector<point_t> points;

	point_t p;

	int r = 0;
	cout << "Enter the number of images:\t";
	cin >> r;
	int cur = 1;
	/*
	while((cin >> p.x) && (cin >> p.y)) {
	points.push_back(p);
	}
	*/
	string str;
	cout << "Enter the first image path:\t";
	cin >> str;
	Mat original = imread(str, CV_LOAD_IMAGE_COLOR);
	vector<Mat> originals(r);
	vector<int> arr(r);
	Mat New = Mat((int)(original.rows), r*(int)(original.cols), original.type());
	while (cur <= r)
	{
		string str;
		cout << "Enter Image" << cur << " Path:\t";
		cin >> str;
		cout << "Enter Image" << cur << " number:\t";
		cin >> arr[cur - 1];
		originals[cur - 1] = imread(str, CV_LOAD_IMAGE_COLOR);

		if (!originals[cur - 1].data)
		{
			cout << "Image failed to load!" << endl;
			return 1;
		}
		cur++;
	}

	vector<int> A1(New.rows*New.cols);
	vector<int> A2(New.rows*New.cols);
	vector<int> A3(New.rows*New.cols);
	vector<vector<int> > A;
	A.push_back(A1);
	A.push_back(A2);
	A.push_back(A3);
	//int A[3][New.rows*New.cols];
	int e = 0;
	int min = 251;
	int rr = 0;
	for (int i = 0; i < originals[0].rows; ++i)
	{
		for (int j = 0; j < originals[0].cols; ++j)
		{
			int c = e;
			rr++;
			points.clear();
			for (int k = 0; k < r; ++k)
			{
				p.x = arr[k];
				p.y = originals[k].at<Vec3b>(i, j)[0];
				points.push_back(p);
				int red = 0;
			}
			for (double coeff : *lagrange_coeffs(points))
			{
				if (coeff != (int)coeff)
					A[0][e] = foo(coeff);
				else
					A[0][e] = ((int)coeff + 2 * 251) % 251;
				e++;
			}
			e = c;
			points.clear();
			for (int k = 0; k < r; ++k)
			{
				p.x = arr[k];
				p.y = originals[k].at<Vec3b>(i, j)[1];
				points.push_back(p);
				int red = 0;
			}
			for (double coeff : *lagrange_coeffs(points))
			{
				if (coeff != (int)coeff)
					A[1][e] = foo(coeff);
				else
					A[1][e] = ((int)coeff + 2 * 251) % 251;
				e++;
			}
			e = c;
			points.clear();
			for (int k = 0; k < r; ++k)
			{
				p.x = arr[k];
				p.y = originals[k].at<Vec3b>(i, j)[2];
				points.push_back(p);
				int red = 0;
			}
			for (double coeff : *lagrange_coeffs(points))
			{
				if (coeff != (int)coeff)
					A[2][e] = foo(coeff);
				else
					A[2][e] = ((int)coeff + 2 * 251) % 251;
				e++;
			}
		}
	}

	e = 0;

	for (int i = 0; i < New.rows; ++i)
	{
		for (int j = 0; j < New.cols; ++j)
		{
			New.at<Vec3b>(i, j)[0] = A[0][e];
			New.at<Vec3b>(i, j)[1] = A[1][e];
			New.at<Vec3b>(i, j)[2] = A[2][e];
			e++;
		}
	}

	imwrite("extractedImage.tiff", New);


	return 0;
}
