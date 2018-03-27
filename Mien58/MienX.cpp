//
//  MienProc.cpp
//  Mien58
//
//  Created by SIFEN ZHONG on 4/10/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "Mien.hpp"
#include "dlib_cv.hpp"
#include <opencv2/imgproc.hpp>

using namespace cv;

namespace MienX {
	void getSimTransform(const std::vector<Point2f>& pt_src, const std::vector<Point2f> pt_dst, Matx23d& aff)
	{
		Point2f s = pt_src[1] - pt_src[0];
		Point2f d = pt_dst[1] - pt_dst[0];
		double s_norm = norm(s);
		double d_norm = norm(d);
		double alpha = d_norm / s_norm;
		
		double cs = (Mat(s).dot(Mat(d)))/(s_norm*d_norm);
		double sn = sqrt(1 - cs*cs);
		
		cs *= alpha;
		sn *= alpha;
		
		Point2f s0 = pt_src[0];
		Point2f d0 = pt_dst[0];
		
		Point2f b = d0 - Point2f((float)(+cs*s0.x +sn*s0.y), (float)(-sn*s0.x +cs*s0.y));
		
		aff = Matx23d(+cs, +sn, b.x, -sn, +cs, b.y);
	}
	
	bool align(cv::Mat& f, std::vector<Point2f>& pt_src, const std::vector<Point2f> pt_dst, cv::Size _box, cv::Mat& h) {
		Matx23d aff;
		getSimTransform(pt_src, pt_dst, aff);
		warpAffine(f, h, aff, _box);
		
		return true;
	}
}

bool Mien::detect(cv::Mat & cvmat, std::vector<Landmark> &landmarks) {
	dlib::cv_image<uint8_t> dlimg(cvmat);
	std::vector<std::pair<double, dlib::rectangle>> dets;
	_fd(dlimg, dets);
	
	int n = (int)dets.size();		if (n < 1) return false;
	landmarks.resize(n);
	for (int i=0; i<n; i++) {
		dlib::full_object_detection fo = _sp(dlimg,dets[i].second);
		landmarks[i].weight = dets[i].first;
		dlib_cv::fdlib(fo.get_rect(), landmarks[i].box);
		std::vector<cv::Point2f>* ll = &landmarks[i].lrn;
		ll->resize(3);
		(*ll)[0] = cv::Point2f((fo.part(0).x() + fo.part(1).x())/2, (fo.part(0).y() + fo.part(1).y())/2);
		(*ll)[1] = cv::Point2f((fo.part(2).x() + fo.part(3).x())/2, (fo.part(2).y() + fo.part(3).y())/2);
		(*ll)[2] = cv::Point2f(fo.part(4).x(), fo.part(4).y());
	}
	
	return true;
}

bool Mien::beone(std::vector<Landmark> &landmarks, Landmark &landmark) {
	if (landmarks.size() < 1) return false;
	landmark = landmarks[0];
	
	return true;
}

bool Mien::align(cv::Mat& f, Landmark& landmark, cv::Mat& h) {
	MienX::align(f, landmark.lrn, MienConst::_lrn, MienConst::_box, h);
	
	return true;
}

bool Mien::train(std::vector<cv::Mat>& imgs, std::vector<int>& labels) {
	_recogn->train(imgs, labels);
	
	return true;
}

bool Mien::predict(cv::Mat& img, int& label, double& confidence) {
	label = _recogn->predict(img);
//	_recogn->predict(img, label, confidence);
	
	return true;
}

void Mien::showLandmark(cv::Mat& img, Landmark& landmark) {
	cv::rectangle(img, landmark.box, cv::Scalar(0x00, 0x00, 0xF0));
	for (auto p=landmark.lrn.begin(); p<landmark.lrn.end(); ++p) {
		cv::circle(img, *p, 2, cv::Scalar(0xF0, 0xF0, 0xF0));
	}
}



