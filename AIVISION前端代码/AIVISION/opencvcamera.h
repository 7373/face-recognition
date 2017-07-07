#ifndef OPENCVCAMERA_H
#define OPENCVCAMERA_H

#include <QObject>

#include "opencvcapture.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>


class OpenCVcamera : public OpenCVcapture
{
    Q_OBJECT
    Q_PROPERTY(int m_cameraId READ cameraId WRITE setCameraId NOTIFY cameraIdChanged)
public:
    OpenCVcamera(QObject *parent = NULL);
    ~OpenCVcamera();

    int cameraId() const;
    void setCameraId(int id);

    virtual void setRun(bool r);

    cv::Mat* getFrame();


signals:
    void cameraIdChanged();
    void runChanged();
    void frame(const QImage &img);
public slots:

protected:


protected slots:

private:
    int m_cameraId;
    int m_openedCameraId;
    cv::Mat *m_matImage;
    CvCapture *m_cvCapture;
    cv::VideoCapture capture;
};

#endif // OPENCVCAMERA_H
