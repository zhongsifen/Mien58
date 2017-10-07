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

#include "data.cpp"

int main_webcam(int _argc, char** _argv);
int main_detect(int _argc, char** _argv);
int main_landmark(int _argc, char** _argv);
int main_recogn(int _argc, char** _argv);

int main(int argc, char** argv) {
	const char** data = MienData::cert;
	const int sizeofdata = sizeof(MienData::cert)/sizeof(char*);
	std::string folder(data[0]);

	Mien58 mien;
	cv::Mat f, h;
	std::vector<Face> faces;
	
	for (int i = 1; i < sizeofdata; ++i)
	{
		f = cv::imread(folder + data[i]);
		mien.detect(f, faces);
		int n = faces.size();
		for (int k=0; k<n; ++k) {
			MienProc::align(f, faces[0].eyeL, faces[0].eyeR, h);
		}
		imshow("detect", f);
		imshow("aligh", h);
		imwrite(folder + "cert_" + std::to_string(i) + ".png", h);
		waitKey();
	}
	
//	std::cout << "Hello, World!\n";
	
	return 0;
}
