#ifndef OPENCVACTIONCAPTURE_H
#define OPENCVACTIONCAPTURE_H
#include "opencvaction.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QDateTime>
#include <QDebug>
#include <string>
#include <Windows.h>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

using namespace cv;

class OpenCVactionCapture : public OpenCVaction
{
    Q_OBJECT




public:
    OpenCVactionCapture();
    ~OpenCVactionCapture();
    void action(cv::Mat *imgin, cv::Mat *&imgout, bool domosaic);

    void GetStringSize(HDC hDC, const char* str, int* w, int* h);
    void paDrawString(Mat& dst, const char* str, Point org, Scalar color, int fontSize, bool italic, bool underline);

    string rolename;
    bool hasrole;

    //QNetworkAccessManager，reply信号对应onHttpFinish()
    static QNetworkAccessManager *mNetManager;




public slots:
    //信号来自QNetworkAccessManager
    void onHttpFinish(QNetworkReply*);
};

#endif // OPENCVACTIONCAPTURE_H
