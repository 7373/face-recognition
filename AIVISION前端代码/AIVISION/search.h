#ifndef SEARCH_H
#define SEARCH_H

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

//前置声明
class QNetworkAccessManager;
class QNetworkReply;

class Search : public QThread
{
    Q_OBJECT
    void run() Q_DECL_OVERRIDE;


public:
    Search();
    Q_INVOKABLE void searchCallInQml(QString imageSource){
        this->imageSource=imageSource.mid(8);
        this->start();
    }

    QString imageSource;
    float *feature;

    //QNetworkAccessManager，reply信号对应onHttpFinish()
    static QNetworkAccessManager *mNetManager;
    //进行HTTP传输
    void doHttpPost();
signals:
    //run()中特征值计算完成，通知QML的onComputeFinish()中进行文字显示更换
    void computeFinish();
    //run()中特征值计算完成，通知C++的onHttpStart()中进行网络请求发送
    void httpStart();
    //全部完成
    void complete(QString codestr,QString namestr,QString sexstr,QString typestr,QString imagepathstr);
    //http通信出错
    void error();


public slots:

    void onComputeFinish();
    void onHttpStart();

    //信号来自QNetworkAccessManager
    void onHttpFinish(QNetworkReply*);
    //全部完成
    void onComplete(QString codestr,QString namestr,QString sexstr,QString typestr,QString imagepathstr);
    void onError();
};

#endif // SEARCH_H
