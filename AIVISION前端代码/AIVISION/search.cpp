#include "search.h"
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
#include "AivisionFromChai/Aivision/Seetaface/include/seetaface.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include "urlconfig.h"

QNetworkAccessManager *Search::mNetManager = NULL;

Search::Search()
{
    //连接信号与槽
    connect(this, SIGNAL(httpStart()), this, SLOT(onHttpStart()));
}

void Search::run(){
    //计算出特征值
    Seetaface* sf=Seetaface::get();
    Feature feature = SingleFeatLoader::spawnFeature(*sf, this->imageSource.toStdString());
    this->feature=feature.feat;

    emit computeFinish();
    emit httpStart();
    qDebug()<<"search http started";
}

//在QML中实现
void Search::onComputeFinish(){

}
//开始发送请求传输数据
void Search::onHttpStart(){
    qDebug()<<"started really";
    doHttpPost();
    connect(this->mNetManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onHttpFinish(QNetworkReply*)));
}

//信号来自QNetworkAccessManager
void Search::onHttpFinish(QNetworkReply* reply){

    //对reply进行解析
    if(reply->error()==QNetworkReply::NoError){

        QString codestr;
        QString namestr;
        QString sexstr;
        QString typestr;
        QString imagepathstr;

        QJsonParseError json_error;
        QJsonDocument parse_doucment = QJsonDocument::fromJson(reply->readAll(), &json_error);
        if(json_error.error == QJsonParseError::NoError)
        {
            if(parse_doucment.isObject())
            {
                QJsonObject obj = parse_doucment.object();
                if(obj.contains("code"))
                {
                    QJsonValue name_value = obj.take("code");
                    if(name_value.isString())
                    {
                        codestr= name_value.toString();
                    }
                }
                if(obj.contains("name"))
                {
                    QJsonValue name_value = obj.take("name");
                    if(name_value.isString())
                    {
                        namestr= name_value.toString();
                    }
                }
                if(obj.contains("sex"))
                {
                    QJsonValue name_value = obj.take("sex");
                    if(name_value.isString())
                    {
                        sexstr= name_value.toString();
                    }
                }
                if(obj.contains("type"))
                {
                    QJsonValue name_value = obj.take("type");
                    if(name_value.isString())
                    {
                        typestr= name_value.toString();
                    }
                }
             }
            imagepathstr=URLCONFIG::IMAGE_URL+codestr+".jpg";
            emit complete(codestr,namestr,sexstr,typestr,imagepathstr);
        }
        else
            emit error();
    }
    else
        emit error();
}
//全部完成
void Search::onComplete(QString codestr,QString namestr,QString sexstr,QString typestr,QString imagepathstr){

}
void Search::onError(){

}

//真实进行HTTP请求的函数
void Search::doHttpPost(){

    if( !mNetManager ) {
        mNetManager = new QNetworkAccessManager(this);
    }

    QString url=URLCONFIG::SEARCH_URL;

    //将计算出的特征值传递给服务器查询

    //边界的时候这里加两杠
    QString boundary = "----weasdashDsdesd";
    //起始边界
    QString startBoundary = "--" + boundary;
    //最终结束边界
    QString endBoundary = "\r\n--" + boundary + "--\r\n";
    //设置传输类型
    QString qContentType = "multipart/form-data; boundary=" + boundary;

    //要发送的内容，这不是人脸要发送的内容，是我自己测试用的
    QByteArray content;
    QString tempStr = startBoundary;

    tempStr = "\r\n";
    tempStr +=startBoundary;
    tempStr += "\r\nContent-Disposition: form-data; name=\"feature\"\r\n\r\n";
    for(int i=0;i<2047;i++)
        tempStr +=QString::number(this->feature[i])+" ";
    tempStr+=QString::number(this->feature[2047]);
    content.append(tempStr.toUtf8());

    content.append(endBoundary);

    //构造http请求
    QNetworkRequest req;
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1SslV3);
    req.setSslConfiguration(config);
    req.setUrl(QUrl(url));
    req.setHeader(QNetworkRequest::ContentTypeHeader, qContentType.toLatin1());
    QNetworkReply * reply = mNetManager->post(req, content);
}
