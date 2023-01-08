//Example 2-1. A simple OpenCV program that loads an image from disk and displays it
//on the screen

#include <iostream>
#include <stdlib.h>
#include "util.h"

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// windows 系统下 设置成支持utf8中文显示
void windows_cmd_support_utf8(void) {
    system("chcp 65001 & cls");
}




int main(int argc, char** argv) {
	if (argc != 2) {
		cout << "Error: command paramter should has input path."  << endl;
		// 让程序不马上退出
		getchar();
		return -1;
	}
    windows_cmd_support_utf8();

	parse_video(argv[1]);


    getchar();
    return 0;


	return 0;
}
