//
//  main.cpp
//  temporalgradient
//
//  Created by Anush sriram Ramesh on 2/6/23.
//
// read in sequence of images from dataset/Office/img01_0*.jpg and convert to grayscale. Compute the temporal gradient of the sequence and display the result. Threshold the result to create a mask of the moving objects. Combine mask with original image to highlight moving objects.

#include <iostream>
#include "../inc/cv_factory.hpp"
#include <string>

using namespace std;
using namespace cv;

int main()
{
    // create an instance of the cv_factory class
    cv_factory cv_obj;
    // read in sequence of images from dataset/Office/img01_0*.jpg and convert to grayscale
    vector<Mat> imgs = cv_obj.read_images("dataset/Office/");
    // compute the temporal gradient of the sequence and display the result
    string type("1D prewitt");
    // vector<Mat> smooth_imgs = cv_obj.Smoothing_Gauss(imgs, 4);
    // Mat temporalGradient = cv_obj.temporal_gradient(smooth_imgs, type);
    double std = cv_obj.ThreshStrategy(imgs);
    std = 4.5*std;
    cv_obj.temporal_gradient(imgs, type, int(std));
    return(0);
}
