//
//  MienRecogn.hpp
//  Mien58
//
//  Created by SIFEN ZHONG on 6/10/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef MienRecogn_hpp
#define MienRecogn_hpp

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/face.hpp>

namespace MienRecogn {
	cv::Ptr<cv::face::EigenFaceRecognizer> _recogn;
}

#endif /* MienRecogn_hpp */
