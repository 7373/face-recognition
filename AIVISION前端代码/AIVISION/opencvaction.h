#ifndef OPENCVACTION_H
#define OPENCVACTION_H

#include <QObject>
#include <opencv/cv.h>
#include <opencv/highgui.h>

class OpenCVaction : public QObject
{
    Q_OBJECT
public:
    explicit OpenCVaction(QObject *parent = 0);
    virtual ~OpenCVaction();
    virtual void action(cv::Mat *imgin, cv::Mat *&imgout, bool domosaic) = 0;
signals:

public slots:
};

#endif // OPENCVACTION_H
