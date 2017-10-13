//
//  Mien58.hpp
//  Mien58
//
//  Created by SIFEN ZHONG on 26/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef Mien58_hpp
#define Mien58_hpp
	
#include "Mien.hpp"
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/face.hpp>

class Mien58 {
	Mien _mien;
	std::vector<dlib::matrix<dlib::rgb_pixel>> _chips;
	std::vector<dlib::matrix<float, 0, 1>> _descrs;
public:
	bool setup();
//	bool setupCard(std::vector<cv::Mat>& imgs);
//	bool run(cv::Mat& img, int& label, double& confidence);
//	bool run(std::vector<cv::Mat>& imgs, std::vector<int>& labels);
//	
//	bool runCard(Mien& mien, std::vector<cv::Mat>& imgs, std::vector<cv::Mat>& cards, std::vector<int>& labels);
//	bool saveCard(std::vector<cv::Mat>& cards, std::string path);
//	bool loadCard(std::vector<cv::Mat>& cards, std::string path);
	
	bool setupCard(cv::Mat& img);
	bool setupCard(std::vector<cv::Mat>& imgs);
	bool run(cv::Mat& img, int& id);
};

#endif /* Mien58_hpp */
