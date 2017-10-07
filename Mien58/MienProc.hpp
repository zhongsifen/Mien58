//
//  MienProc.hpp
//  Mien58
//
//  Created by SIFEN ZHONG on 4/10/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef MienProc_hpp
#define MienProc_hpp

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

namespace MienProc {
	
//	const cv::Point _eyeL(92, 42);
//	const cv::Point _eyeR(36, 42);
//	const cv::Size _box(128, 128);
	const cv::Point _eyeL(46, 21);
	const cv::Point _eyeR(18, 21);
	const cv::Size _box(64, 64);

	bool
	align(cv::Mat& f, cv::Point& eyeL, cv::Point& eyeR, cv::Mat& h);
	
}

#endif /* MienProc_hpp */
