#ifndef OPENCVSHOWFRAME_H
#define OPENCVSHOWFRAME_H

#include <QQuickItem>
#include <QTimer>
#include <list>
#include <QImage>
#include <opencv/cv.h>
#include <opencv/highgui.h>
class OpenCVcapture;

class OpenCVshowFrame : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int m_frameRate READ frameRate WRITE setFrameRate NOTIFY frameRateChanged)
    Q_PROPERTY(bool m_run READ run WRITE setRun NOTIFY runChanged)
    Q_PROPERTY(QObject* m_capture READ capture WRITE setCapture NOTIFY captureChanged)
public:
    explicit OpenCVshowFrame(QQuickItem *parent = 0);
    ~OpenCVshowFrame();

    int frameRate() const;
    void setFrameRate(int rate);

    bool run() const;
    void setRun(bool r);

    QObject* capture() const;
    void setCapture(QObject *c);

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

#endif // OPENCVSHOWFRAME_H
