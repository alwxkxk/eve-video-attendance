#include "tesseract/baseapi.h"
#include "leptonica/allheaders.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void ocr_img_path(char* path) {
    // 根据图片文件路径识别输出文字
    char* outText;

    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();

    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(NULL, "chi_sim")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // Open input image with leptonica library
    Pix* image = pixRead(path);
    api->SetImage(image);



    // Get OCR result
    outText = api->GetUTF8Text();

    printf("OCR output:\n%s", outText);



    // 输出到文件
    //fstream file;
    //file.open("sample_file.txt", ios_base::out);

    //if (!file.is_open())
    //{
    //    cout << "Unable to open the file.\n";
    //    return ;
    //}

    //file << outText;
    //file.close();

    // Destroy used object and release memory
    api->End();
    delete api;
    delete[] outText;
    pixDestroy(&image);
}

void ocr_opencv_mat(Mat image) {
    // opencv 的方式读取图片
    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();

    if (api->Init(NULL, "chi_sim")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }
    char* outText;


    api->SetImage(image.data,image.cols,image.rows,3,image.step);

    // Get OCR result
    outText = api->GetUTF8Text();

    printf("OCR output:\n%s", outText);

    api->End();
    delete api;
    delete[] outText;
}