//
//  Mien.cpp
//  Mien58
//
//  Created by SIFEN ZHONG on 12/10/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "Mien.hpp"
#include <wdlib.hpp>

Mien::Mien() {
	_fd = dlib::get_frontal_face_detector();
	dlib::deserialize(MienConst::_DAT_SP) >> _sp;
	dlib::deserialize(MienConst::_DAT_NET) >> _net;
}

bool Mien::descr(cv::Mat& cvimg, dlib::matrix<rgb_pixel>& chip, dlib::matrix<float,0,1>& descr) {
	dlib::cv_image<rgb_pixel> img;
	wdlib::tdlib(cvimg, img);
	std::vector<matrix<rgb_pixel>> faces;
	for (auto face : _fd(img)) {
		auto shape = _sp(img, face);
		if (shape.num_parts() > 0) {
			matrix<rgb_pixel> face_chip;
			extract_image_chip(img, get_face_chip_details(shape,150,0.25), face_chip);
			faces.push_back(std::move(face_chip));
		}
	}
	std::vector<matrix<float,0,1>> face_descriptors = _net(faces);
	chip = faces[0];
	descr = face_descriptors[0];

	return true;
}
