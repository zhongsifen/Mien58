//
//  Mien58.hpp
//  Mien58
//
//  Created by SIFEN ZHONG on 26/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef Mien58_hpp
#define Mien58_hpp

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/face.hpp>
#include <string>

const std::string _MODELDAT("/Users/zhongsifen/Work/Mien58/model/");
const std::string _DAT_SP(_MODELDAT + "shape_predictor_5_face_landmarks.dat");
const std::string _DAT_NET(_MODELDAT + "dlib_face_recognition_resnet_model_v1.dat");

typedef struct {
	double weight;
	cv::Rect box;
	std::vector<cv::Point> parts;
	
	cv::Point eyeR;
	cv::Point eyeL;
	cv::Point nose;
}
Face;

void showFace(cv::Mat& img, Face& face);

class Mien58 {
	dlib::frontal_face_detector _fd;
	dlib::shape_predictor _sp;
	cv::Ptr<cv::face::EigenFaceRecognizer> _recogn;

public:
	Mien58();
	
	bool detect(cv::Mat& img, std::vector<Face>& faces);
};

#endif /* Mien58_hpp */
