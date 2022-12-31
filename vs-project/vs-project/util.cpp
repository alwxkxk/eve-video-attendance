#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

Mat crop_image(Mat img) {
	// 截取图片的右侧30%。,上方20%。
	if (img.empty()) return Mat();

	int rows = img.rows;
	int cols = img.cols;
	//cout << "image rows:" << rows << ",cols:" << cols << endl;
	//Mat crop_img = img.colRange(Range(cols * 70 / 100, cols));
	Mat crop_img=img.colRange(Range(cols * 70 / 100, cols)).rowRange(0, rows * 20 / 100);

	return crop_img;
}


Mat threshold_img(Mat img,bool rgbFlag = false) {
	// 变黑白图，并返回成RGB格式的数据
	Mat result_img,gray_img,b_img,erode_img;
	cvtColor(img, gray_img, COLOR_RGB2GRAY);
	threshold(gray_img, b_img, 50, 255, THRESH_BINARY);
	//imshow("debug image", b_img);
	if (rgbFlag) {
		cvtColor(b_img, result_img, COLOR_GRAY2RGB);
		return result_img;
	}
	else {
		return b_img;
	}

}



vector<Vec4i> hough_line_x(Mat gray_img) {
	vector<Vec4i> lines;
	HoughLinesP(gray_img, lines, 1, CV_PI / 180, 10, 8, 10);

	//cout << "lines size:" << lines.size() << endl;

	return lines;

}





int parse_video(char* path) {
	cout << "path:" << path  << endl;

	VideoCapture cap;
	Mat frame;
	cap.open(path);
	if (!cap.isOpened()) { // check if we succeeded
		std::cerr << "Couldn't open capture." << std::endl;
		return -1;
	}


	namedWindow("input image", WINDOW_AUTOSIZE);
	namedWindow("debug image", WINDOW_AUTOSIZE);
	namedWindow("output image", WINDOW_AUTOSIZE);


	float minAngle = 89 * CV_PI / 180;
	float maxAngle = 91 * CV_PI / 180;
	for (;;) {
		cap >> frame;

		if (frame.empty()) break; // Ran out of film

		Mat crop_img = crop_image(frame);
		Mat b_img = threshold_img(crop_img);
		Mat crop_img_output;
		crop_img.copyTo(crop_img_output);
		//cvtColor(crop_img, gray_img, COLOR_RGB2GRAY);
		vector<Vec4i> lines = hough_line_x(b_img);

		int linesSize = 0;
		for (size_t i = 0; i < lines.size(); i++)
		{
			// HoughLinesP 需要自行过滤掉角度
			float angle = atan2(lines[i][1] - lines[i][3],lines[i][0] - lines[i][2]);
			//cout << "angle:" << angle << endl;
			if (angle > minAngle && angle < maxAngle) {
				linesSize++;
				cout << "lines:" << lines[i] << endl;
				line(crop_img_output, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(0, 0, 255), 1, 8);
			}
			
		}
		cout << "lines size:" << linesSize << endl;
 
 
		imshow("input image", frame);
		imshow("output image", crop_img_output);
		imshow("debug image", b_img);

		if ((char)waitKey(33) >= 0) break;

	}

	destroyWindow("input image");
	destroyWindow("debug image");
	destroyWindow("output image");

	return 0;
}

