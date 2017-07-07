#ifndef OPENCVCAPTURE_H
#define OPENCVCAPTURE_H

#include <QObject>
#include <opencv/cv.h>
#include <opencv/highgui.h>

class OpenCVcapture : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool m_run READ run WRITE setRun NOTIFY runChanged)
public:
    explicit OpenCVcapture(QObject *parent = 0);
    virtual ~OpenCVcapture();

    bool run() const;
    virtual void setRun(bool r);

    virtual cv::Mat* getFrame() = 0;

signals:
    void runChanged();
public slots:

protected:
    bool m_run;
};

#endif // OPENCVCAPTURE_H
