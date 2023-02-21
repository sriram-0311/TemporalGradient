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
    string type("Gauss");
    imgs = cv_obj.Smoothing_Gauss(imgs, 1.5);
    Mat temporalGradient = cv_obj.temporal_gradient(imgs, type);
    // Mat temporalGradient = cv_obj.temporal_gradient(imgs, type);

    // compute the mean and standard deviation of first 100 images from imgs vector
    // slice the vector to get the first 100 images
    // vector<Mat> first_100_imgs(imgs.begin(), imgs.begin() + 100);
    // // compute the mean and standard deviation of the first 100 images
    // vector<float> mean_std = cv_obj.mean_std(first_100_imgs);
    // // display the mean and standard deviation of the first 100 images
    // cout << "mean: " << mean_std[0] << endl;
    // cout << "standard deviation: " << mean_std[1] << endl;
    // compute the mean and standard deviation of the temporal gradient
    // Mat mean_temporal, std_temporal
    // imshow("temporal gradient", temporalGradient);
    // threshold the result to create a mask of the moving objectsf
    // Mat mask = cv_obj.thresholding(temporalGradient, 30);
    // imshow("mask", mask);
    // combine mask with original image to highlight moving objects
    // Mat highlighted = cv_obj.highlight(imgs[0], mask);
    // display the resultant image with highlighted moving objects
    // cv_obj.display(highlighted, "highlighted");

    return(0);
}
