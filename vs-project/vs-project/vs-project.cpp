//Example 2-1. A simple OpenCV program that loads an image from disk and displays it
//on the screen

#include <iostream>
#include "util.h"
using namespace std;


int main(int argc, char** argv) {
	if (argc != 2) {
		cout << "Error: command paramter should has input path."  << endl;
		// 让程序不马上退出
		getchar();
		return -1;
	}

	parse_video(argv[1]);


	return 0;
}
