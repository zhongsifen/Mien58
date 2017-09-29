// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*

    This example program shows how to find frontal human faces in an image and
    estimate their pose.  The pose takes the form of 68 landmarks.  These are
    points on the face such as the corners of the mouth, along the eyebrows, on
    the eyes, and so forth.  
    


    This face detector is made using the classic Histogram of Oriented
    Gradients (HOG) feature combined with a linear classifier, an image pyramid,
    and sliding window detection scheme.  The pose estimator was created by
    using dlib's implementation of the paper:
        One Millisecond Face Alignment with an Ensemble of Regression Trees by
        Vahid Kazemi and Josephine Sullivan, CVPR 2014
    and was trained on the iBUG 300-W face landmark dataset.  

    Also, note that you can train your own models using dlib's machine learning
    tools.  See train_shape_predictor_ex.cpp to see an example.

    


    Finally, note that the face detector is fastest when compiled with at least
    SSE2 instructions enabled.  So if you are using a PC with an Intel or AMD
    chip then you should enable at least SSE2 instructions.  If you are using
    cmake to compile this program you can enable them by using one of the
    following commands when you create the build project:
        cmake path_to_dlib_root/examples -DUSE_SSE2_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_SSE4_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_AVX_INSTRUCTIONS=ON
    This will set the appropriate compiler options for GCC, clang, Visual
    Studio, or the Intel compiler.  If you are using another compiler then you
    need to consult your compiler's manual to determine how to enable these
    instructions.  Note that AVX is the fastest but requires a CPU from at least
    2011.  SSE4 is the next fastest and is supported by most current machines.  
*/

#include "Mien58.hpp"
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>

using namespace dlib;
using namespace std;

// ----------------------------------------------------------------------------------------
namespace landmark {
	const char* argv[] = {
		"landmark",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-31-1.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-33-2.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-34-3.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-34-4.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-35-5.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-35-6.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-35-7.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-35-8.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-35-9.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-36-10.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-36-11.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-36-12.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-36-13.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-37-14.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-37-15.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-37-16.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-37-17.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-37-18.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-38-19.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-38-20.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-38-21.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-38-22.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-39-23.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-39-24.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-39-25.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-39-26.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-39-27.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-40-28.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-40-29.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-40-30.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-40-31.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-40-32.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-40-33.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-41-34.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-41-35.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-41-36.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-41-37.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-42-38.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-42-39.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-42-40.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-42-41.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-42-42.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-43-43.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-43-44.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-43-45.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-43-46.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-43-47.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-44-48.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-44-49.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-44-50.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-44-51.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-45-52.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-45-53.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-45-54.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-45-55.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-45-56.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-46-57.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-46-58.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-46-59.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-46-60.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-47-61.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-47-62.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-47-63.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-47-64.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-47-65.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-48-66.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-48-67.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-48-68.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-48-69.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-49-70.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-49-71.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-49-72.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-49-73.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-49-74.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-50-75.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-50-76.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-50-77.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-50-78.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-51-79.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-51-80.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-51-81.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-51-82.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-52-83.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-52-84.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-52-85.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-52-86.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-52-87.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-53-88.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-53-89.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-53-90.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-53-91.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-53-92.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-54-93.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-54-94.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-54-95.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-54-96.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-55-97.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-48-55-98.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-49-31-99.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-49-40-100.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-49-42-101.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-49-53-102.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-49-55-103.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-49-56-104.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-49-56-105.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-49-57-106.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-49-58-107.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-49-58-108.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-49-59-109.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-00-110.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-01-111.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-01-112.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-01-113.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-02-114.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-02-115.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-02-116.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-02-117.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-03-118.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-03-119.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-03-120.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-03-121.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-04-122.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-04-123.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-04-124.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-04-125.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-04-126.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-05-127.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-05-128.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-05-129.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-05-130.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-05-131.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-06-132.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-06-133.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-06-134.jpeg",
		"/Users/zhongsifen/Work/data/cert/wcr/2017-09-04-10-50-06-135.jpeg",
	};
	const int argc = 136;
};
using namespace landmark;
int main_landmark(int _argc, char** _argv)
{  
    try
    {
        // This example takes in a shape model file and then a list of images to
        // process.  We will take these filenames in as command line arguments.
        // Dlib comes with example images in the examples/faces folder so give
        // those as arguments to this program.
        if (argc == 1)
        {
            cout << "Call this program like this:" << endl;
            cout << "./face_landmark_detection_ex shape_predictor_68_face_landmarks.dat faces/*.jpg" << endl;
            cout << "\nYou can get the shape_predictor_68_face_landmarks.dat file from:\n";
            cout << "http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2" << endl;
            return 0;
        }

        // We need a face detector.  We will use this to get bounding boxes for
        // each face in an image.
        frontal_face_detector detector = get_frontal_face_detector();
        // And we also need a shape_predictor.  This is the tool that will predict face
        // landmark positions given an image and face bounding box.  Here we are just
        // loading the model from the shape_predictor_68_face_landmarks.dat file you gave
        // as a command line argument.
        shape_predictor sp;
        deserialize(_DAT_SP) >> sp;


        image_window win, win_faces;
        // Loop over all the images provided on the command line.
        for (int i = 1; i < argc; ++i)
        {
            cout << "processing image " << argv[i] << endl;
            array2d<rgb_pixel> img;
            load_image(img, argv[i]);
            // Make the image larger so we can detect small faces.
//            pyramid_up(img);

            // Now tell the face detector to give us a list of bounding boxes
            // around all the faces in the image.
            std::vector<rectangle> dets = detector(img);
            cout << "Number of faces detected: " << dets.size() << endl;

            // Now we will go ask the shape_predictor to tell us the pose of
            // each face we detected.
            std::vector<full_object_detection> shapes;
            for (unsigned long j = 0; j < dets.size(); ++j)
            {
                full_object_detection shape = sp(img, dets[j]);
                cout << "number of parts: "<< shape.num_parts() << endl;
                cout << "pixel position of first part:  " << shape.part(0) << endl;
                cout << "pixel position of second part: " << shape.part(1) << endl;
                // You get the idea, you can get all the face part locations if
                // you want them.  Here we just store them in shapes so we can
                // put them on the screen.
                shapes.push_back(shape);
            }

            // Now let's view our face poses on the screen.
            win.clear_overlay();
            win.set_image(img);
            win.add_overlay(render_face_detections(shapes));

            // We can also extract copies of each face that are cropped, rotated upright,
            // and scaled to a standard size as shown here:
            dlib::array<array2d<rgb_pixel> > face_chips;
            extract_image_chips(img, get_face_chip_details(shapes), face_chips);
            win_faces.set_image(tile_images(face_chips));

//            cout << "Hit enter to process the next image..." << endl;
//            cin.get();
			dlib::sleep(1000);
        }
    }
    catch (exception& e)
    {
        cout << "\nexception thrown!" << endl;
        cout << e.what() << endl;
    }
	
	return 0;
}

// ----------------------------------------------------------------------------------------

