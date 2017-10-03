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

void showFace(cv::Mat& img, Face& face) {
	cv::rectangle(img, face.box, cv::Scalar(0x00, 0x00, 0xF0));
}

//bool
//Mien58::detect(cv::Mat &img, std::vector<cv::Rect> &faces) {
//	cv_image<bgr_pixel> cimg(img);
//	std::vector<std::pair<double, rectangle> > final_dets;
//	int n = (int)dets.size();		if (n < 1) return false;
//	fdlib(dets, faces);
//	
//	return true;
//}

Mien58::Mien58() {
	_fd = dlib::get_frontal_face_detector();
//	dlib::deserialize(_DAT_SP) >> _sp;
}

bool
Mien58::detect(cv::Mat & cvmat, std::vector<Face> &faces) {
	std::vector<std::pair<double, dlib::rectangle>> dets;
//	std::vector<dlib::rectangle> dets;
	dlib::cv_image<dlib::bgr_pixel> dlimg(cvmat);
//	dets = _fd(dlimg);
	_fd(dlimg, dets);
	
	int n = (int)dets.size();		if (n < 1) return false;
	faces.resize(n);
	for (int i=0; i<n; i++) {
		wdlib::fdlib(dets[i].second, faces[i].box);
//		miens[i].weight = dets[i].first;
//		dlib::full_object_detection* fo = &dets[i].second;
//		fdlib(fo->get_rect(), miens[i].box);
//		int p = (int)fo->num_parts();
//		std::vector<cv::Point>* lp = &miens[i].parts;
//		lp->resize(p);
//		for (int k=0; k<p; ++k) {
//			fdlib(fo->part(k), (*lp)[k]);
//		}
	}
	
	return true;
}
