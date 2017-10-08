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

int main(int argc, char** argv) {
	const char** data = MienData::cert;
	const int sizeofdata = sizeof(MienData::cert)/sizeof(char*);
	std::string folder(data[0]);

	std::vector<Mat> cards, labels;
	cards.resize(sizeofdata-1);
	labels.resize(sizeofdata-1);
	for (int i = 1; i < sizeofdata; ++i)
	{
		cards[i-1] = cv::imread(folder + data[i]);
	}

	Mien mien;
	Mien58::setup(mien);
	Mien58::runCard(mien, cards, labels);
	for (int i = 0; i < labels.size(); ++i)
	{
		imshow("detect", cards[i]);
		imshow("aligh", labels[i]);
		imwrite(folder + "label_" + std::to_string(i+1) + ".png", labels[i]);
		waitKey();
	}
	
//	std::cout << "Hello, World!\n";
	
	return 0;
}
