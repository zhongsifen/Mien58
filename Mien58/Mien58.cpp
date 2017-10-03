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
		cv::circle(img, *p, 2, cv::Scalar(0xF0, 0x00, 0x00));
	}
}

void showFace(cv::Mat& img, Face& face) {
	cv::rectangle(img, face.box, cv::Scalar(0x00, 0x00, 0xF0));
	showPoints(img, face.parts);
}

Mien58::Mien58() {
	_fd = dlib::get_frontal_face_detector();
//	dlib::deserialize(_DAT_SP) >> _sp;
}

bool
Mien58::detect(cv::Mat & cvmat, std::vector<Face> &faces) {
	std::vector<std::pair<double, dlib::full_object_detection>> dets;
	dlib::cv_image<dlib::bgr_pixel> dlimg(cvmat);
	_fd(dlimg, dets);
	
	int n = (int)dets.size();		if (n < 1) return false;
	faces.resize(n);
	for (int i=0; i<n; i++) {
		faces[i].weight = dets[i].first;
		dlib::full_object_detection* fo = &dets[i].second;
		wdlib::fdlib(fo->get_rect(), faces[i].box);
		int p = (int)fo->num_parts();
		std::vector<cv::Point>* lp = &faces[i].parts;
		lp->resize(p);
		for (int k=0; k<p; ++k) {
			wdlib::fdlib(fo->part(k), (*lp)[k]);
		}
	}
	
	return true;
}
