#ifndef QUALITY_H
#define QUALITY_H

#include <QObject>
#include <QQuickItem>
#include <QThread>
#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QString>
#include <QByteArray>
#include <QSsl>
#include <QSslConfiguration>
#include <QSslSocket>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "glcm.h"
#include "iostream"
#include "math.h"

class Quality : public QThread
{
    Q_OBJECT
    void run() Q_DECL_OVERRIDE;

    Q_PROPERTY(QString brightnession READ getBrightnession WRITE setBrightnession)
    Q_PROPERTY(QString contrast READ getContrast WRITE setContrast)
    Q_PROPERTY(QString definition READ getDefinition WRITE setDefinition)
    Q_PROPERTY(QString facesize READ getFacesize WRITE setFacesize)
    Q_PROPERTY(QString faceposition READ getFaceposition WRITE setFaceposition)
    Q_PROPERTY(QString faceangle READ getFaceangle WRITE setFaceangle)

public:
    Quality();
    Q_INVOKABLE void qualityCallInQml(QString imageSource){
        this->imageSource=imageSource.mid(8);
        this->start();
    }

    double DefRto(Mat InputImg);
    double DefRto(IplImage *InputImg);
    double Tenegrad(Mat InputImg);
    double color(Mat InputImg);
    double brightness(Mat InputImg, double& avg);



    QString imageSource;

    QString brightnession;//亮度
    QString getBrightnession(){return brightnession;}
    void setBrightnession(QString value){brightnession=value;}

    QString contrast;//对比度
    QString getContrast(){return contrast;}
    void setContrast(QString value){contrast=value;}

    QString definition;//清晰度
    QString getDefinition(){return definition;}
    void setDefinition(QString value){definition=value;}

    QString facesize;//人脸大小
    QString getFacesize(){return facesize;}
    void setFacesize(QString value){facesize=value;}

    QString faceposition;//人脸位置
    QString getFaceposition(){return faceposition;}
    void setFaceposition(QString value){faceposition=value;}

    QString faceangle;//人脸角度
    QString getFaceangle(){return faceangle;}
    void setFaceangle(QString value){faceangle=value;}


signals:
    //全部完成
    void complete();

public slots:
    //全部完成
    void onComplete();
};

#endif // QUALITY_H
