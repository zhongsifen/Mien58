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

bool Mien58::setup(Mien &mien) {
	
	return true;
}

bool Mien58::runCard(Mien &mien, std::vector<cv::Mat> &cards, std::vector<cv::Mat> &labels) {
	int n = (int)cards.size();
	labels.resize(n);
	for (int i=0; i<n; ++i) {
		std::vector<Landmark> landmarks;
		Landmark landmark;
		mien.detect(cards[i], landmarks);
		mien.beone(landmarks, landmark);
		mien.align(cards[i], landmark, labels[i]);
	}
	
	return true;
}

