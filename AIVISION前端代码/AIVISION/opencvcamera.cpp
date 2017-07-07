#include "opencvcamera.h"
//#include <QSGSimpleTextureNode>
//#include <QQuickWindow>
//#include <QTimer>
#include <QDebug>


OpenCVcamera::OpenCVcamera(QObject *parent): OpenCVcapture(parent),
    m_cameraId(0),
    m_openedCameraId(-1),
    m_matImage(NULL),
    m_cvCapture(NULL)
{
    m_matImage=new cv::Mat();
    capture = cv::VideoCapture(0);

}



OpenCVcamera::~OpenCVcamera()
{
    if (m_cvCapture != NULL) {
        cvReleaseCapture(&m_cvCapture);
        m_cvCapture = NULL;
    }

    m_matImage = NULL;

}


int OpenCVcamera::cameraId() const
{
    return m_cameraId;
}


void OpenCVcamera::setCameraId(int id)
{
    m_cameraId = id;
}


void OpenCVcamera::setRun(bool r)
{
    m_run = r;
}

cv::Mat* OpenCVcamera::getFrame()
{


    capture>>*m_matImage;
    return m_matImage;
}







