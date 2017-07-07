#include "AivisionFromChai/Aivision/Seetaface/include/seetaface.h"
#include <fstream>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>

using std::string;
using namespace std;

Feature SingleFeatLoader::spawnFeature(Seetaface& seeta, std::string img)
{
	cv::Mat src = cv::imread(img);
	std::vector<Feature> feats = seeta.spawnFeatures(src);
	if (feats.size() == 0) return{};
	return feats[0];
	//return{};
}

Feature SingleFeatLoader::spawnFeatureWithMat(Seetaface& seeta, cv::Mat src)
{
    std::vector<Feature> feats = seeta.spawnFeatures(src);
    if (feats.size() == 0) return{};
    return feats[0];
    //return{};
}

bool SingleFeatLoader::saveModelToFile(Feature& f, std::string file)
{
	std::ofstream fs(file);
	if (!fs) return false;
	fs << f.id << endl;
	for (int i = 0; i < FEATURE_SIZE; i++)
	{
		fs << f.feat[i] << " ";
	}
	fs << endl;
	return true;
}

bool GetFilenameUnderPath(string file_path, std::vector<string>& files) {
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(file_path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					GetFilenameUnderPath(p.assign(file_path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				char *ext = strrchr(fileinfo.name, '.');
				if (ext) {
					ext++;
					if (_stricmp(ext, "jpg") == 0 || _stricmp(ext, "png") == 0)
						files.push_back(p.assign(file_path).append("\\").append(fileinfo.name));
				}
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	return true;
}

string getFileName(string path)
{
	char fname[_MAX_FNAME];
	_splitpath(path.c_str(), NULL, NULL, fname, NULL); 
	return fname; 
}

bool SingleFeatLoader::loadDirToFile(Seetaface& seeta, std::string dir, std::string file)
{
	vector<string> files;
	GetFilenameUnderPath(dir, files);
	ofstream fs;
	fs.open(file);
	if (!fs) return false;
	for (int i = 0; i < files.size(); i++)
	{
		string fl = files[i];
		Feature ft = SingleFeatLoader::spawnFeature(seeta, fl);
		ft.id = i;
		fs << getFileName(fl) << endl;
		for (int i = 0; i < FEATURE_SIZE; i++)
			fs << ft.feat[i] << " ";
		fs << endl;
	}
	fs << endl;
	fs.close();
}
