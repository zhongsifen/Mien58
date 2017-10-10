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
#include <opencv2/highgui.hpp>
using namespace cv;

bool Mien58::setup() {
	
	return true;
}

bool Mien58::setupCard(std::vector<cv::Mat>& imgs) {
	std::vector<cv::Mat> cards;
	std::vector<int> labels;
	int n = (int)imgs.size();
	cards.resize(n);
	labels.resize(n);
	for (int i=0; i<n; ++i) {
		std::vector<Landmark> landmarks;
		Landmark landmark;
		_mien.detect(imgs[i], landmarks);
		_mien.beone(landmarks, landmark);
		_mien.align(imgs[i], landmark, cards[i]);
		labels[i] = i;
	}
	_mien.train(cards, labels);
	
	return true;
}

bool Mien58::run(cv::Mat& img, int& label, double& confidence) {
	cv::Mat h;
	std::vector<Landmark> landmarks;
	Landmark landmark;
	_mien.detect(img, landmarks);
	_mien.beone(landmarks, landmark);
	_mien.align(img, landmark, h);
	imshow("run h", h);
	_mien.predict(h, label, confidence);
	
	return true;
}

bool Mien58::run(std::vector<cv::Mat> &imgs, std::vector<int> &labels) {
	
	return true;
}

bool Mien58::runCard(Mien &mien, std::vector<cv::Mat>& imgs, std::vector<cv::Mat> &cards, std::vector<int> &labels) {
	int n = (int)imgs.size();
	cards.resize(n);
	labels.resize(n);
	for (int i=0; i<n; ++i) {
		std::vector<Landmark> landmarks;
		Landmark landmark;
		mien.detect(imgs[i], landmarks);
		mien.beone(landmarks, landmark);
		mien.align(imgs[i], landmark, cards[i]);
		labels[i] = i;
	}
	mien.train(cards, labels);
	
	return true;
}

