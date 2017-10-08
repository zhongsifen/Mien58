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

namespace Mien58 {
	bool setup(Mien& mien);
	bool runCard(Mien& mien, std::vector<cv::Mat>& cards, std::vector<cv::Mat>& labels);
	bool saveCard(std::vector<cv::Mat>& cards, std::string path);
	bool loadCard(std::vector<cv::Mat>& cards, std::string path);
}

#endif /* Mien58_hpp */
