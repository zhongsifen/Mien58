//
//  Mien58.hpp
//  Mien58
//
//  Created by SIFEN ZHONG on 26/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef Mien58_hpp
#define Mien58_hpp

#include <opencv2/core.hpp>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <string>

const std::string _DAT("/Users/zhongsifen/Work/dlib/data/");
const std::string _DAT_SP(_DAT + "shape_predictor_68_face_landmarks.dat");
const std::string _DAT_NET(_DAT + "dlib_face_recognition_resnet_model_v1.dat");

class Mien58 {
	dlib::frontal_face_detector _detector;
public:
	Mien58() {
		_detector = dlib::get_frontal_face_detector();
	}
	
	bool detect(cv::Mat& img, std::vector<cv::Rect>& face);
};

#endif /* Mien58_hpp */
