//
//  main.cpp
//  appMien58
//
//  Created by SIFEN ZHONG on 16/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "Mien58.hpp"
#include "MienProc.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
using namespace cv;

const char* _filename[] = {
"2017-09-29-14-27-45-1.jpeg",
"2017-09-29-14-28-12-2.jpeg",
"2017-09-29-14-28-40-3.jpeg",
"2017-09-29-14-28-46-4.jpeg",
"2017-09-29-14-28-57-5.jpeg",
"2017-09-29-14-28-59-6.jpeg",
"2017-09-29-14-29-13-7.jpeg",
"2017-09-29-14-29-14-8.jpeg",
"2017-09-29-14-29-15-9.jpeg",
"2017-09-29-14-29-17-10.jpeg",
"2017-09-29-14-29-37-11.jpeg",
"2017-09-29-14-29-39-12.jpeg",
"2017-09-29-14-29-40-13.jpeg",
"2017-09-29-14-29-40-14.jpeg",
"2017-09-29-14-29-41-15.jpeg",
"2017-09-29-14-29-41-16.jpeg",
"2017-09-29-14-29-41-17.jpeg",
"2017-09-29-14-29-42-18.jpeg",
"2017-09-29-14-29-42-19.jpeg",
"2017-09-29-14-29-42-20.jpeg",
};
const std::string _folder("/Users/zhongsifen/Work/Mien58/data/0928_pic/");
const int _ndata = 20;

int main_webcam(int _argc, char** _argv);
int main_detect(int _argc, char** _argv);
int main_landmark(int _argc, char** _argv);
int main_recogn(int _argc, char** _argv);
int main(int argc, char** argv) {
	const int _argc = 9;
	Mien58 mien;
	cv::Mat f, h;
	std::vector<Face> faces;
	
	printf("sizeof = %d\n", sizeof(_filename)/sizeof(char*));
	for (int i = 0; i < _ndata; ++i)
	{
		f = cv::imread(_folder + _filename[i]);
		mien.detect(f, faces);
		int n = faces.size();
		for (int k=0; k<n; ++k) {
			align(f, faces[0].eyeL, faces[0].eyeR, h);
			showFace(f, faces[k]);
		}
		imshow("detect", f);
		imshow("aligh", h);
		waitKey();
	}
	
//	std::cout << "Hello, World!\n";
	
	return 0;
}
