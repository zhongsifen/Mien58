//
//  main.cpp
//  appMien58
//
//  Created by SIFEN ZHONG on 16/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "Mien58.hpp"
#include "Mien.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
using namespace cv;

#include "data.cpp"

int main_recogn(int _argc, char** _argv);
int main(int argc, char** argv) {
//	return main_recogn(argc, argv);
	const char** data_card = MienData::card;
	const int n = sizeof(MienData::card)/sizeof(char*);
	std::string folder_card(MienData::folder_card);

	Mien58 m58;
	std::vector<Mat> imgs;
	imgs.resize(n);
	for (int i = 0; i < n; ++i)
	{
		imgs[i] = cv::imread(folder_card + data_card[i]);
	}
	m58.setupCard(imgs);

	const char** data_input = MienData::input;
	const int l = sizeof(MienData::input)/sizeof(char*);
	std::string folder_input(MienData::folder_input);
	
	for (int i=0; i<l; ++i) {
		Mat f = cv::imread(folder_input + data_input[i]);
		int p=-1;
		double w=0;
		m58.run(f, p);
		
//		imshow("f", f);
//		imshow("h", h);
//		waitKey(10);
	}

	return 0;
}
