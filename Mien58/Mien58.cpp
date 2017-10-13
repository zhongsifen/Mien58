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
#if 0
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
#endif
bool Mien58::setupCard(cv::Mat &img) {
	dlib::matrix<rgb_pixel> chip;
	dlib::matrix<float, 0, 1> descr;
	_mien.descr(img, chip, descr);
	_chips.push_back(chip);
	_descrs.push_back(descr);
	
	return true;
}

bool Mien58::setupCard(std::vector<cv::Mat> &imgs) {
	int n = (int)imgs.size();
	_chips.resize(n);
	_descrs.resize(n);
	for (int i=0; i<n; ++i) {
		_mien.descr(imgs[i], _chips[i], _descrs[i]);
	}
	
	return true;
}

bool Mien58::run(cv::Mat &img, int& id) {
	dlib::matrix<rgb_pixel> chip;
	dlib::matrix<float, 0, 1> descr;
	_mien.descr(img, chip, descr);
	double score = 100;
	int index = id = -1;
	int n = (int)_descrs.size();
	for (int i=0; i<n; ++i) {
		double s = dlib::length(descr - _descrs[i]);
		if (s < score) {
			score = s;
			index = i;
		}
	}
	if (score > 0.6) return false;
	id = index;
	dlib::cv_image<bgr_pixel> cvimg(img);
	dlib::image_window im(cvimg);
	dlib::image_window ch(_chips[id]);
	dlib::sleep(1000);
	
	return true;
}





