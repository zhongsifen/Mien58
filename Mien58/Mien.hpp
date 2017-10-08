//
//  Mien.hpp
//  Mien
//
//  Created by SIFEN ZHONG on 4/10/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef Mien_hpp
#define Mien_hpp

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <opencv2/core.hpp>
#include <opencv2/face.hpp>

namespace MienConst {
	const std::string _MODELDAT("/Users/zhongsifen/Work/Mien58/model/");
	const std::string _DAT_SP(_MODELDAT + "shape_predictor_5_face_landmarks.dat");
	const std::string _DAT_NET(_MODELDAT + "dlib_face_recognition_resnet_model_v1.dat");
	//	const cv::Point2f _eyeL(92, 42);
	//	const cv::Point2f _eyeR(36, 42);
	//	const cv::Size _box(128, 128);
	const cv::Point2f _eyeL(46, 21);
	const cv::Point2f _eyeR(18, 21);
	const cv::Size _box(64, 64);
	const std::vector<cv::Point2f> _lrn = { _eyeL, _eyeR, };
}

class Landmark {
public:
	double weight;
	cv::Rect box;
	std::vector<cv::Point2f> lrn;
};

class Mien {
	dlib::frontal_face_detector _fd;
	dlib::shape_predictor _sp;
	cv::Ptr<cv::face::EigenFaceRecognizer> _recogn;
	
public:
	Mien();
	
	bool detect(cv::Mat& img, std::vector<Landmark>& landmarks);
	bool beone(std::vector<Landmark>& landmarks, Landmark& landmark);
	bool align(cv::Mat& f, Landmark& landmark, cv::Mat& h);
	void showLandmark(cv::Mat& img, Landmark& landmark);
};

#endif /* Mien_hpp */
