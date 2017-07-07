#include "opencvcommonaction.h"

#include <QDebug>

#define min(x, y) (x < y ? x : y)
#define max(x, y) (x > y ? x : y)
#define without(x, min, max) (x < min || x > max)
#define within(x, min, max) (x >= min && x <= max)


OpenCVcommonAction::OpenCVcommonAction()
{

}

OpenCVcommonAction::~OpenCVcommonAction()
{

}

void OpenCVcommonAction::action(cv::Mat *imgin, cv::Mat *&imgout, bool domosaic)
{
//    imgout = cvCreateImage(cvGetSize(imgin), imgin->depth, imgin->nChannels);
//    cvCvtColor(imgin, imgout, CV_BGR2RGB);
    //imgout=imgin;

    //cv::transpose(*imgin,*imgout);

    cv::Rect rec(10,10,400,400);

    mosaic(*imgin,rec);



    imgout=imgin;

//    cv::rectangle(*imgin, rec, CV_RGB(0, 0, 255), CV_FILLED, 8, 0);
//    imgout=imgin;
}


void OpenCVcommonAction::mosaic(cv::Mat& img, cv::Rect& rect)
{
    int imgw = img.cols;
    int imgh = img.rows;
    int masaicSize = 20;
    for (int i = rect.x; i < rect.x + rect.width ; i += masaicSize)
        for (int j = rect.y; j < rect.y + rect.height; j += masaicSize)
        {
            cv::Rect r = cv::Rect(i, j, masaicSize, masaicSize);
            if (without(r.x, 0, imgw - masaicSize) || without(r.y, 0, imgh - masaicSize) )continue;
            cv::Mat mosaic = img(r);
            mosaic.setTo(mean(mosaic));
        }
}



