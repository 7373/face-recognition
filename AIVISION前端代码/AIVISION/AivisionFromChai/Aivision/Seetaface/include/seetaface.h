#ifndef __SEETAFACE_H
#define __SEETAFACE_H

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc.hpp>

#include "facedetection/face_detection.h"
#include "facealignment/face_alignment.h"
#include "faceidentification/face_identification.h"

#include <string>
#include <vector>
#include <iostream>

#include "util.h"
#include <string>
#define FEATURE_SIZE 2048

#define DF "C:/zFetch/AIVISION/AivisionFromChai/SeetaFaceEngine-master/FaceDetection/model/seeta_fd_frontal_v1.0.bin"
#define AF "C:/zFetch/AIVISION/AivisionFromChai/SeetaFaceEngine-master/\FaceAlignment/model/seeta_fa_v1.1.bin"
#define IF "C:/zFetch/AIVISION/AivisionFromChai/SeetaFaceEngine-master/\FaceIdentification/model/seeta_fr_v1.0.bin"

struct Feature
{
	Feature():id(-1) { feat = new float[FEATURE_SIZE]; };
	Feature(const Feature& f) {
		id = f.id;
		//if(feat != NULL) delete[] feat;
		feat = new float[FEATURE_SIZE];
		memcpy(feat, f.feat, FEATURE_SIZE * sizeof(float));
	}
	~Feature()
	{
		delete[] feat; 
	}

	int id;			// 从model文件中读入时有用，保存每个人的数据库id
	float* feat;
};

// seetaface的二次封装
class Seetaface
{
public: 
    static Seetaface* get(std::string df=DF, std::string af=AF, std::string iif=IF);
	Seetaface();
	Seetaface(
		std::string detectionFile, 
		std::string alignmentFile, 
		std::string identificationFile
	);
	std::vector<seeta::FaceInfo> detect(cv::Mat image); // detect faces 
	std::vector<Feature> spawnFeatures(const cv::Mat& image); 
	float similarity(Feature& fa, Feature& fb);
private:
    static Seetaface* see;
	typedef seeta::FaceAlignment Alignment;
	typedef seeta::FaceIdentification Identification;
	class Detector: public seeta::FaceDetection
	{
	public: Detector(std::string modefile);		      // 已经训练好的文件 seeta_fd_frontal_v1.0.bin
			Detector();
	} ;
	Detector* detector;								  // face detector
	Alignment* pointDetector;						  // face alignment 
	Identification* recognizer;					      // face recognition 
};

/*
注意：只能读取证件照（一张照片里一个人，自动忽略剩余人）
Feature 结构
id			: 用户ID
float[2048]	: 特征值
*/
class SingleFeatLoader
{
public:
	// 从img中读取特征值并返回（无ID）
	static Feature spawnFeature(Seetaface& seeta, std::string imgPath);

    static Feature spawnFeatureWithMat(Seetaface& seeta, cv::Mat src);
	// 把特征值保存到一个文件里(追加）
	static bool saveModelToFile(Feature& f, std::string file);
	// 把目录中的所有图片提取头像并保存
	static bool loadDirToFile(Seetaface& seeta, std::string dir, std::string file);
};

class FaceRecognizer
{
public:
	static float similarity(Seetaface& s, Feature& fa, Feature& fb);
};

class Blender
{
public:
	// 马赛克
	inline static void mosaic(cv::Mat& img, cv::Rect& rect){
		int imgw = img.cols;
		int imgh = img.rows;
		int masaicSize = 20;
		for (int i = rect.x; i < rect.x + rect.width; i += masaicSize)
			for (int j = rect.y; j < rect.y + rect.height; j += masaicSize)
			{
				cv::Rect r = cv::Rect(i, j, masaicSize, masaicSize);
				if (without(r.x, 0, imgw - masaicSize) || without(r.y, 0, imgh - masaicSize))continue;
                cv::Mat mosaic = img(r);
				mosaic.setTo(mean(mosaic));
			}
	}
};

#endif
