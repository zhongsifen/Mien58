//
//  Mien58.cpp
//  Mien58
//
//  Created by SIFEN ZHONG on 26/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "Mien58.hpp"
#include <wdlib.hpp>
#include <dlib/opencv.h>
#include <opencv2/imgproc.hpp>

void showPoints(cv::Mat& img, std::vector<cv::Point>& points) {
	for (auto p=points.begin(); p<points.end(); ++p) {
		cv::circle(img, *p, 2, cv::Scalar(0xF0, 0xF0, 0x00));
	}
//	cv::line(img, points[0], points[1], cv::Scalar(0xF0, 0xF0, 0x00));
}

void showFace(cv::Mat& img, Landmark& face) {
	cv::rectangle(img, face.box, cv::Scalar(0x00, 0x00, 0xF0));
	showPoints(img, face.parts);
	cv::circle(img, face.eyeR, 2, cv::Scalar(0xF0, 0xF0, 0xF0));
	cv::circle(img, face.eyeL, 2, cv::Scalar(0xF0, 0xF0, 0xF0));
}


