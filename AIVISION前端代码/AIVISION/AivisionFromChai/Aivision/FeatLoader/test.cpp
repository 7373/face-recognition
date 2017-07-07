/*
两种方式存储特征值：
1. 输入文件目录和特征值文件目录，把特征值保存到特征值文件里
2. 输入文件夹，获取所有的特征值并保存在特征值文件里

保存好的特征值文件可以直接使用，作为人脸识别的依据
*/
#include <iostream>
#include <fstream>
#include "seetaface.h"
using namespace cv;
using namespace std;

int main(int, char*[])
{
	// 初始化环境，载入训练好的模型
	Seetaface sf = Seetaface(
		"model/seeta_fd_frontal_v1.0.bin",
		"model/seeta_fa_v1.0.bin",
		"model/seeta_fr_v1.0.bin"
	);

	while (true)
	{
		cout << "选择保存方式：\n";
		cout << "1. 按 1 读取单个图片的特征值并保存到文件\n";
		cout << "2. 按 2 读取整个目录的特征值并保存到文件\n";
		char c; 
		cin >> c;
		switch (c)
		{
		case '1':
		{
			cout << "输入图片路径\n";
			string file;
			cin >> file;
			Feature f = SingleFeatLoader::spawnFeature(sf, file);
			cout << "输入保存的文件路径\n";
			string modelFile;
			cin >> modelFile; 
			cout << "存储中...\n";
			SingleFeatLoader::saveModelToFile(f, modelFile);
			break;
		}
		case '2':
			cout << "输入目录\n";
			string dir;
			cin >> dir; 
			cout << "输入保存的文件路径\n";
			string modelFile;
			cin >> modelFile;
			cout << "存储中...\n";
			SingleFeatLoader::loadDirToFile(sf, dir, modelFile);
			break;
		}
	}

	return 0;
}