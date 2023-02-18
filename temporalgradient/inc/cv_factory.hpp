//
//  cv_factory.hpp
//  temporalgradient
//
//  Created by Anush sriram Ramesh on 2/6/23.
//
// include the header files needed to perform cv operations and read and writing file directories

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <filesystem>

using namespace std;
using namespace cv;

// define class to perform cv operations
class cv_factory {
    public:
        vector<float> filter{(-0.5, 0, 0.5)};
        // function to read all image files in the directory and return a vector
        vector<Mat> read_images(string directory) {
            // create a vector to store the images
            vector<Mat> imgs;
            //generate the files names from 1 to 1070 and read the images in grayscale
            for (int i = 1; i<=1070;i++) {
                int NumOfZeroes = 4 - to_string(i).length();
                string ZeroString = "";
                for (int j = 0; j < NumOfZeroes; j++) {
                    ZeroString += "0";
                }
                string filename = directory + "img01_" + ZeroString + to_string(i) + ".jpg";
                Mat photos = imread(filename, IMREAD_GRAYSCALE);
                imgs.push_back(photos);
            }
            return imgs;
        }

        // function to compute the temporal gradient of the sequence using the specified filter, passed as a parameter and return the temporal gradient image as result
        Mat temporal_gradient(vector<Mat> imgs, vector<float> filter, string filter_type) {
            // create a matrix to store the temporal gradient
            Mat temporal_gradient = Mat::zeros(imgs[0].size(), CV_8UC1);

            if(filter_type == "1D diff")
            {   // compute the temporal gradient of the sequence and display the result
                for (int i = 0; i < imgs.size() - 1; i++) {
                Mat diff = abs(0.5*(-imgs[i] + imgs[i + 1]));
                temporal_gradient = max(temporal_gradient, diff);
                }
            }

            else if(filter_type == "simple filter")
            {   // compute the temporal gradient of the sequence and display the result
                for (int i = 1; i < imgs.size() - 1; i++) {
                Mat diff = abs(0.5*(imgs[i+1] - imgs[i-1]));
                temporal_gradient = max(temporal_gradient, diff);
                }
            }

            if(filter_type == "Gauss")
            {   // compute the temporal gradient of the sequence and display the result
                for (int i = 0; i < imgs.size() - 2; i++) {
                Mat diff = abs(filter[0]*imgs[i] + filter[1]*imgs[i+1] + filter[2]*imgs[i+2]);
                temporal_gradient = max(temporal_gradient, diff);
                }
            }

            return temporal_gradient;
        }

        // function to threshold the temporal gradient image to create a mask of the moving objects
        Mat thresholding(Mat temporal_gradient, int threshold_value) {
            // threshold the result to create a mask of the moving objects
            Mat mask;
            threshold(temporal_gradient, mask, threshold_value, 255, THRESH_BINARY);
            return mask;
        }

        // function to combine mask with original image to highlight moving objects
        Mat highlight(Mat image, Mat mask) {
            // combine mask with original image to highlight moving objects
            Mat highlighted = Mat::zeros(image.size(), CV_8UC3);
            // vectorize the operation to highlight the moving objects
            for (int i = 0; i < image.rows; i++) {
                for (int j = 0; j < image.cols; j++) {
                    if (mask.at<uchar>(i, j) == 255) {
                        highlighted.at<Vec3b>(i, j) = image.at<Vec3b>(i, j);
                    }
                }
            }
            return highlighted;
        }

        // function to display the temporal gradient image
        void display(Mat image, string window_name) {
            // display the temporal gradient image
            namedWindow(window_name, WINDOW_NORMAL);
            imshow(window_name, image);
            waitKey(0);
        }

        /* creating a 1D derivative of Gaussian filter_1D */
        void CreateGaussian(const int size, int tsigma)
        {   Mat Gauss;
            double Nr, Dr, sum;
            sum = 0;
            for(int i=0;i<size;i++)
            {   Nr = -(pow(i,2));
                Dr = 2*pow(tsigma, 2);
                Gauss.at<double>(i) = (Nr/Dr);
                sum += Gauss.at<double>(i);
            }
            Gauss = Gauss/sum;
        }
};