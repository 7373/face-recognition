#include<iostream>
#include "AivisionFromChai/Aivision/Seetaface/include/seetaface.h"
#include <QDebug>

using namespace std;
using namespace cv; 
using namespace seeta; 

Seetaface* Seetaface::see=new Seetaface(DF,AF,IF);
Seetaface* Seetaface::get(string df, string af, string iif){
//    if(Seetaface::see==NULL)
//    {
//        return new Seetaface(df,af,iif);
//    }
//    else
        return Seetaface::see;
    //return see==NULL ? (new Seetaface(df,af,iif)):see;
}

Seetaface::Detector::Detector(string model)
	: seeta::FaceDetection(model.c_str())
{
	this->SetMinFaceSize(40);
	this->SetScoreThresh(2.f);
	this->SetImagePyramidScaleFactor(0.8f);
	this->SetWindowStep(4, 4);
}

Seetaface::Seetaface()
{
}

Seetaface::Seetaface(string d, string a, string i)
{
	detector = new Detector(d);
	pointDetector = new Alignment(a.c_str());
	recognizer = new Identification(i.c_str());
}

vector<seeta::FaceInfo> Seetaface::detect(cv::Mat img)
{
    cv::Mat imgGray; // gray image
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
    seeta::ImageData img_data;
    img_data.data = imgGray.data;
    img_data.width = imgGray.cols;
    img_data.height = imgGray.rows;
    img_data.num_channels = 1;
    std::vector<seeta::FaceInfo> faces =detector->Detect(img_data);
    return faces;
}

std::vector<Feature> Seetaface::spawnFeatures(const cv::Mat& src)
{
	//read pic color
	// ª“∂»Õº
	cv::Mat srcGray;

	cv::cvtColor(src, srcGray, CV_BGR2GRAY);

	seeta::ImageData src_img_data_color(src.cols, src.rows, src.channels());
	src_img_data_color.data = src.data;

	//read pic greyscale
	seeta::ImageData src_img_data(srcGray.cols, srcGray.rows, srcGray.channels());
	src_img_data.data = srcGray.data;

	std::vector<seeta::FaceInfo> faces = this->detector->Detect(src_img_data);
	int32_t face_num = static_cast<int32_t>(faces.size());
	if (face_num == 0)
	{
		return{};
	}
	vector<Feature> features{};
	for (int i = 0; i < face_num; i++)
	{
		Feature feat;
		feat.feat = new float[FEATURE_SIZE];
		seeta::FacialLandmark points[5];
		pointDetector->PointDetectLandmarks(src_img_data, faces[i], points);
		recognizer->ExtractFeatureWithCrop(src_img_data_color, points, feat.feat);
		features.push_back(feat);
	}

	return features;
}

float Seetaface::similarity(Feature& fa, Feature& fb)
{
    return recognizer->CalcSimilarity(fa.feat, fb.feat);
}

