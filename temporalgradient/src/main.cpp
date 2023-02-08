//
//  main.cpp
//  temporalgradient
//
//  Created by Anush sriram Ramesh on 2/6/23.
//
// read in sequence of images from dataset/Office/img01_0*.jpg and convert to grayscale. Compute the temporal gradient of the sequence and display the result. Threshold the result to create a mask of the moving objects. Combine mask with original image to highlight moving objects.

#include <iostream>
#include "../inc/cv_factory.hpp"

using namespace std;
using namespace cv;

int main()
{
    // create an instance of the cv_factory class
    cv_factory cv_obj;
    // read in sequence of images from dataset/Office/img01_0*.jpg and convert to grayscale
    vector<Mat> imgs = cv_obj.read_images("dataset/Office/");
    // compute the temporal gradient of the sequence and display the result
    Mat filter = (Mat_<float>(1, 3) << -1, 0, 1);
    Mat temporalGradient = cv_obj.temporal_gradient(imgs, filter);
    imshow("temporal gradient", temporalGradient);
    // threshold the result to create a mask of the moving objects
    Mat mask = cv_obj.thresholding(temporalGradient, 30);
    imshow("mask", mask);
    // combine mask with original image to highlight moving objects
    Mat highlighted = cv_obj.highlight(imgs[0], mask);
    // display the resultant image with highlighted moving objects
    cv_obj.display(highlighted, "highlighted");
}