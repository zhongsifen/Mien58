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

#if 0
image_window win(img);

if (faces.size() == 0)
{
	cout << "No faces found in image!" << endl;
	return 1;
	}
	
	// This call asks the DNN to convert each face image in faces into a 128D vector.
	// In this 128D vector space, images from the same person will be close to each other
	// but vectors from different people will be far apart.  So we can use these vectors to
	// identify if a pair of images are from the same person or from different people.
	std::vector<matrix<float,0,1>> face_descriptors = net(faces);
	
	
	// In particular, one simple thing we can do is face clustering.  This next bit of code
	// creates a graph of connected faces and then uses the Chinese whispers graph clustering
	// algorithm to identify how many people there are and which faces belong to whom.
	std::vector<sample_pair> edges;
	for (size_t i = 0; i < face_descriptors.size(); ++i)
	{
		for (size_t j = i+1; j < face_descriptors.size(); ++j)
		{
			// Faces are connected in the graph if they are close enough.  Here we check if
			// the distance between two face descriptors is less than 0.6, which is the
			// decision threshold the network was trained to use.  Although you can
			// certainly use any other threshold you find useful.
			if (length(face_descriptors[i]-face_descriptors[j]) < 0.25)
				edges.push_back(sample_pair(i,j));
		}
	}
	std::vector<unsigned long> labels;
	const auto num_clusters = chinese_whispers(edges, labels);
	// This will correctly indicate that there are 4 people in the image.
	cout << "number of people found in the image: "<< num_clusters << endl;
#endif
