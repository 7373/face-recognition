#ifndef OPENCVCOMMONACTION_H
#define OPENCVCOMMONACTION_H

#include "opencvaction.h"


class OpenCVcommonAction : public OpenCVaction
{
    Q_OBJECT
public:
    OpenCVcommonAction();
    ~OpenCVcommonAction();
    void action(cv::Mat *imgin, cv::Mat *&imgout, bool domosaic);
    void mosaic(cv::Mat& img, cv::Rect& rect);
};

#endif // OPENCVCOMMONACTION_H
