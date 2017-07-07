#ifndef OpenCVshowFrameCAPTURE_H
#define OpenCVshowFrameCAPTURE_H


#include <QQuickItem>
#include <QTimer>
#include <list>
#include <QImage>
#include <opencv/cv.h>
#include <opencv/highgui.h>
class OpenCVcapture;

class OpenCVshowFrameCapture : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int m_frameRate READ frameRate WRITE setFrameRate NOTIFY frameRateChanged)
    Q_PROPERTY(bool m_run READ run WRITE setRun NOTIFY runChanged)
    Q_PROPERTY(QObject* m_capture READ capture WRITE setCapture NOTIFY captureChanged)


    Q_PROPERTY(bool mosaic READ getMosaic WRITE setMosaic)
public:
    explicit OpenCVshowFrameCapture(QQuickItem *parent = 0);
    ~OpenCVshowFrameCapture();

    int frameRate() const;
    void setFrameRate(int rate);

    bool run() const;
    void setRun(bool r);

    QObject* capture() const;
    void setCapture(QObject *c);


    bool getMosaic() const {return mosaic;}
    void setMosaic(bool mo){mosaic=mo;}
    bool mosaic=true;


    Q_INVOKABLE void addAction(QObject *act);

    Q_INVOKABLE void startPredict();

    Q_INVOKABLE void setLabel(int i);

    Q_INVOKABLE void startTrain();

signals:
    void frameRateChanged();
    void runChanged();
    void captureChanged();
    void who(int i);

public slots:

    void fun();

protected slots:
    void updateFrame();
    void a() {

    }

protected:
    QSGNode* updatePaintNode(QSGNode * old, UpdatePaintNodeData *);
private:
    int m_frameRate;
    bool m_run;
    QObject *m_capture;
    QTimer m_timer;
    std::list<QObject*> m_actions;
    cv::Mat* doActions(cv::Mat *img);
    QImage::Format format(int depth, int nChannels);

};

#endif // OpenCVshowFrameCAPTURE_H
