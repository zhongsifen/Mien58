//
//  MienRecogn.cpp
//  Mien58
//
//  Created by SIFEN ZHONG on 6/10/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include "MienRecogn.hpp"

#if 0
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/face.hpp"
#include "opencv2/core/utility.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace cv;
using namespace cv::face;
using namespace std;


int main(int argc, const char *argv[]) {
	// Get the path to your CSV.
	string fn_csv = string(argv[1]);
	// These vectors hold the images and corresponding labels.
	vector<Mat> images;
	vector<int> labels;
	std::map<int, string> labelsInfo;
	// Read in the data. This can fail if no valid
	// input filename is given.
	try {
		read_csv(fn_csv, images, labels, labelsInfo);
	} catch (cv::Exception& e) {
		cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
		// nothing more we can do
		exit(1);
	}
	
	// Quit if there are not enough images for this demo.
	if(images.size() <= 1) {
		string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
		CV_Error(Error::StsError, error_message);
	}
	// The following lines simply get the last images from
	// your dataset and remove it from the vector. This is
	// done, so that the training data (which we learn the
	// cv::FaceRecognizer on) and the test data we test
	// the model with, do not overlap.
	Mat testSample = images[images.size() - 1];
	int nlabels = (int)labels.size();
	int testLabel = labels[nlabels-1];
	images.pop_back();
	labels.pop_back();
	// The following lines create an Eigenfaces model for
	// face recognition and train it with the images and
	// labels read from the given CSV file.
	// This here is a full PCA, if you just want to keep
	// 10 principal components (read Eigenfaces), then call
	// the factory method like this:
	//
	//      EigenFaceRecognizer::create(10);
	//
	// If you want to create a FaceRecognizer with a
	// confidennce threshold, call it with:
	//
	//      EigenFaceRecognizer::create(10, 123.0);
	//
	_recogn = EigenFaceRecognizer::create();
	for( int i = 0; i < nlabels; i++ )
		model->setLabelInfo(i, labelsInfo[i]);
	model->train(images, labels);
	string saveModelPath = "face-rec-model.txt";
	cout << "Saving the trained model to " << saveModelPath << endl;
	model->save(saveModelPath);
	
	// The following line predicts the label of a given
	// test image:
	int predictedLabel = model->predict(testSample);
	//
	// To get the confidence of a prediction call the model with:
	//
	//      int predictedLabel = -1;
	//      double confidence = 0.0;
	//      model->predict(testSample, predictedLabel, confidence);
	//
	string result_message = format("Predicted class = %d / Actual class = %d.", predictedLabel, testLabel);
	cout << result_message << endl;
	if( (predictedLabel == testLabel) && !model->getLabelInfo(predictedLabel).empty() )
		cout << format("%d-th label's info: %s", predictedLabel, model->getLabelInfo(predictedLabel).c_str()) << endl;
	
	// advanced stuff
	if(argc>2) {
		// Sometimes you'll need to get/set internal model data,
		// which isn't exposed by the public cv::FaceRecognizer.
		// Since each cv::FaceRecognizer is derived from a
		// cv::Algorithm, you can query the data.
		//
		// First we'll use it to set the threshold of the FaceRecognizer
		// to 0.0 without retraining the model. This can be useful if
		// you are evaluating the model:
		//
		model->setThreshold(0.0);
		// Now the threshold of this model is set to 0.0. A prediction
		// now returns -1, as it's impossible to have a distance below
		// it
		predictedLabel = model->predict(testSample);
		cout << "Predicted class = " << predictedLabel << endl;
		// Here is how to get the eigenvalues of this Eigenfaces model:
		Mat eigenvalues = model->getEigenValues();
		// And we can do the same to display the Eigenvectors (read Eigenfaces):
		Mat W = model->getEigenVectors();
		// From this we will display the (at most) first 10 Eigenfaces:
		for (int i = 0; i < min(10, W.cols); i++) {
			string msg = format("Eigenvalue #%d = %.5f", i, eigenvalues.at<double>(i));
			cout << msg << endl;
			// get eigenvector #i
			Mat ev = W.col(i).clone();
			// Reshape to original size & normalize to [0...255] for imshow.
			Mat grayscale;
			normalize(ev.reshape(1), grayscale, 0, 255, NORM_MINMAX, CV_8UC1);
			// Show the image & apply a Jet colormap for better sensing.
			Mat cgrayscale;
			applyColorMap(grayscale, cgrayscale, COLORMAP_JET);
			imshow(format("%d", i), cgrayscale);
		}
		waitKey(0);
	}
	return 0;
}

#endif
