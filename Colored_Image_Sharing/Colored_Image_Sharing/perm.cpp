#include <iostream>     // std::cout
#include <algorithm>    // std::next_permutation, std::sort
#include <opencv2/highgui.hpp>
#include <fstream>

using namespace cv;
using namespace std;

int main () {
  
  string str;
  cout << "Enter Image Path:\t";
  cin >> str;

  Mat original = imread(str, CV_LOAD_IMAGE_GRAYSCALE);

  if (!original.data)
  {
    cout << "Image failed to load!" << endl;
    return 1;
  }

  int myints[original.rows*original.cols];

  for (int i = 0; i < original.rows*original.cols; ++i)
  {
    myints[i]=i;
  }

  cout << "Enter the key:\t";
  long long int r;
  random_shuffle(myints, myints+(original.rows*original.cols));
  ofstream myfile;
  myfile.open ("permu.txt");
  for (int i = 0; i < original.rows*original.cols; ++i)
  {
    myfile << myints[i] << endl;
  }
  myfile.close();
  return 0;
}
