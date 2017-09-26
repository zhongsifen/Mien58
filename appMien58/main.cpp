//
//  main.cpp
//  appMien58
//
//  Created by SIFEN ZHONG on 16/9/2017.
//  Copyright © 2017 ___ZHONGSIFEN___. All rights reserved.
//

#include <iostream>

int main_detect(int _argc, char** _argv);
int main_landmark(int _argc, char** _argv);
int main_recogn(int _argc, char** _argv);
int main(int argc, char** argv) {
	int ret = main_landmark(argc, argv);
	std::cout << "Hello, World!\n";
	return ret;
}
