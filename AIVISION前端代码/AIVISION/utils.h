#ifndef UTILS_H
#define UTILS_H

#include <QImage>
#include <opencv/cv.h>
#include <opencv/highgui.h>

class Utils
{
public:
    Utils();

    static QImage cvMat2QImage(const cv::Mat& mat);
    static cv::Mat QImage2cvMat(QImage image);
};

#endif // UTILS_H
