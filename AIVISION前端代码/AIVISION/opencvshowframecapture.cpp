#include "OpenCVshowFrameCapture.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/contrib/contrib.hpp>
#include "opencvcapture.h"
#include <QSGTexture>
#include <QSGSimpleTextureNode>
#include <QQuickWindow>
#include "opencvaction.h"
#include "opencvactioncapture.h"
#include "utils.h"

OpenCVshowFrameCapture::OpenCVshowFrameCapture(QQuickItem *parent) : QQuickItem(parent),
    m_frameRate(60),
    m_run(false),
    m_capture(NULL)
{
    m_timer.setInterval(1000 / m_frameRate);
    connect(&m_timer, &QTimer::timeout, this, &OpenCVshowFrameCapture::updateFrame);
    setFlag(QQuickItem::ItemHasContents);
    m_actions.push_back(new OpenCVactionCapture());
}

OpenCVshowFrameCapture::~OpenCVshowFrameCapture()
{
    for (auto ite = m_actions.begin(); ite != m_actions.end(); ++ite) {
        (*ite)->deleteLater();
    }
    m_actions.clear();
}

int OpenCVshowFrameCapture::frameRate() const
{
    return m_frameRate;
}

void OpenCVshowFrameCapture::startPredict()
{

}

void OpenCVshowFrameCapture::setLabel(int i)
{

}

void OpenCVshowFrameCapture::startTrain()
{

}

void OpenCVshowFrameCapture::setFrameRate(int rate)
{
    if (rate <= 0) {
        rate = 33;
    }
    m_frameRate = rate;
    if (m_timer.isActive()) {
        m_timer.stop();
        m_timer.start(1000 / m_frameRate);
    } else {
        m_timer.setInterval(1000 / m_frameRate);
    }
}

bool OpenCVshowFrameCapture::run() const
{
    return m_run;
}

void OpenCVshowFrameCapture::setRun(bool r)
{
    m_run = r;
    if (m_run) {
        if (!m_timer.isActive())
            m_timer.start();
    } else {
        if (m_timer.isActive())
            m_timer.stop();
    }
}

QObject* OpenCVshowFrameCapture::capture() const
{
    return m_capture;
}

void OpenCVshowFrameCapture::fun()
{
    qDebug() << "fun";
}

void OpenCVshowFrameCapture::setCapture(QObject *c)
{
    m_capture = c;
}

void OpenCVshowFrameCapture::updateFrame()
{
    OpenCVcapture *cap = static_cast<OpenCVcapture*>(m_capture);
    if (cap->run()) {
        update();
    }
}


void OpenCVshowFrameCapture::addAction(QObject *act)
{
    m_actions.push_back(act);
}

cv::Mat* OpenCVshowFrameCapture::doActions(cv::Mat *img)
{
    cv::Mat *t = img;
    if (m_actions.empty()) {
    } else {
        QList<cv::Mat*> list;
        for (auto ite = m_actions.begin(); ite != m_actions.end(); ++ite) {
            OpenCVaction *act = static_cast<OpenCVaction*>(*ite);
            cv::Mat *out;
            act->action(t, out, this->mosaic);
            t = out;
            list.push_back(out);
        }
        for (auto ite = list.begin(); ite != list.end(); ++ite) {
            if ((*ite) != t) {
                //(*ite)->release();

                //cvReleaseMat(&(*ite));

            }
        }
    }
    return t;
}


QImage::Format OpenCVshowFrameCapture::format(int depth, int nChannels)
{
    QImage::Format re = QImage::Format_Invalid;
    do {
        if (depth == 8 && nChannels == 1) {
            re = QImage::Format_RGB888;
            break;
        }
        if (nChannels == 3) {
            re = QImage::Format_RGB888;
            break;
        }

    }while(0);

    return re;
}


QSGNode* OpenCVshowFrameCapture::updatePaintNode(QSGNode *old, UpdatePaintNodeData *)
{
    QSGSimpleTextureNode *texture = static_cast<QSGSimpleTextureNode*>(old);
    if (texture == NULL) {
        texture = new QSGSimpleTextureNode();
    }
    QImage img;
    IplImage *iplImage = NULL;
    cv::Mat * matImage = NULL;
    IplImage *out = NULL;
    cv::Mat * outMat = NULL;
    if (m_capture) {
        matImage = static_cast<OpenCVcapture*>(m_capture)->getFrame();
    }
    if (matImage != NULL) {
        outMat = doActions(matImage);

        img=Utils::cvMat2QImage(*outMat);
//        uchar *imgData = (uchar *)out->imageData;
//        //qDebug() << out->depth << out->nChannels;
//        img = QImage(imgData, out->width, out->height, QImage::Format_RGB888);
    } else {
        img = QImage(boundingRect().size().toSize(), QImage::Format_RGB888);
    }
    QSGTexture *t = window()->createTextureFromImage(img.scaled(boundingRect().size().toSize()));
    if (t) {
        QSGTexture *tt = texture->texture();
        if (tt) {
            tt->deleteLater();
        }
        texture->setRect(boundingRect());
        texture->setTexture(t);
    }
    if (outMat) {
        //cvReleaseMat(&outMat);
        //outMat->release();

    }
    return texture;
}
