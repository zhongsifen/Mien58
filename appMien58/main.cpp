//
//  main.cpp
//  appMien58
//
//  Created by SIFEN ZHONG on 16/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "Mien58.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
using namespace cv;

int main_webcam(int _argc, char** _argv);
int main_detect(int _argc, char** _argv);
int main_landmark(int _argc, char** _argv);
int main_recogn(int _argc, char** _argv);
int main(int argc, char** argv) {
	const char* _argv[] = {
		"detect",
		"/Users/zhongsifen/Work/data/cert/cert/1.jpg",
		"/Users/zhongsifen/Work/data/cert/cert/2.jpg",
		"/Users/zhongsifen/Work/data/cert/cert/3.jpg",
		"/Users/zhongsifen/Work/data/cert/cert/4.jpg",
		"/Users/zhongsifen/Work/data/cert/cert/5.jpg",
		"/Users/zhongsifen/Work/data/cert/cert/6.jpg",
		"/Users/zhongsifen/Work/data/cert/cert/7.jpg",
		"/Users/zhongsifen/Work/data/cert/cert/8.jpg",
	};
	const int _argc = 9;
	Mien58 mien;
	cv::Mat f;
	std::vector<cv::Rect> faces;
	
	for (int i = 1; i < _argc; ++i)
	{
		f = cv::imread(_argv[i]);
		mien.detect(f, faces);
		for (int k=0; k<faces.size(); ++k) {
			rectangle(f, faces[k], Scalar(0x00, 0x00, 0xF0));
		}
		imshow("detect", f);
		waitKey();
	}
	
	std::cout << "Hello, World!\n";
	
	return 0;
}
