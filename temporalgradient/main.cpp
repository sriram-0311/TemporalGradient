//
//  main.cpp
//  temporalgradient
//
//  Created by Anush sriram Ramesh on 2/6/23.
//
// read in sequence of images from dataset/Office/img01_0*.jpg and convert to grayscale. Compute the temporal gradient of the sequence and display the result. Threshold the result to create a mask of the moving objects. Combine mask with original image to highlight moving objects.

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <filesystem>

using namespace std;
using namespace cv;

int main()
{
    Vector<Mat> imgs;
    // read all image files in the directory "dataset/Office/*.jpg in increasing order and store in a vector"
    for (int i = 1; i<=1070;i++) {
        int NumOfZeroes = 4 - to_string(i).length();
        string ZeroString = "";
        for (int j = 0; j < NumOfZeroes; j++) {
            ZeroString += "0";
        }
        string filename = "dataset/Office/img01_" + ZeroString + to_string(i) + ".jpg";
        Mat photos = imread(filename, IMREAD_GRAYSCALE);
        imgs.push_back(photos);
    }

    // compute the temporal gradient of the sequence and display the result
    Mat temporal_gradient = Mat::zeros(imgs[0].size(), CV_8UC1);
    for (int i = 0; i < imgs.size() - 1; i++) {
        Mat diff = abs(imgs[i] - imgs[i + 1]);
        temporal_gradient = max(temporal_gradient, diff);
    }
    imshow("temporal gradient", temporal_gradient);
    // show 10 sample images read from the directory
    // for (int i = 0; i < 10; i++) {
    //     imshow("sample images", imgs[i]);
    //     waitKey(0);
    // }
    return 0;
}
