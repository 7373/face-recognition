#include "register.h"
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
#include "urlconfig.h"


QNetworkAccessManager *Register::mNetManager = NULL;

Register::Register()
{
    //连接信号与槽
    connect(this, SIGNAL(httpStart()), this, SLOT(onHttpStart()));
}
void Register::registerCallInQml(QString imageSource, QString name, QString sex, QString id, QString label){
    this->imageSource=imageSource.mid(8);//因为是以file:///开头的，所以删掉就是绝对路径了
    this->name=name;
    this->sex=sex;
    this->id=id;
    this->label=label;
    this->start();
}

void Register::run(){
     //计算人脸特征值
//    double x=0;
//    for(int i=0;i<888898888;i++)
//    {
//       x=x+1;
//    }
//    qDebug()<<"expect started"+QString::number(x);

    //计算出特征值
    Seetaface* sf=Seetaface::get();
    Feature feature = SingleFeatLoader::spawnFeature(*sf, this->imageSource.toStdString());
    this->feature=feature.feat;

    this->feature;
    emit computeFinish();
    emit httpStart();

}

//在QML中实现
void Register::onComputeFinish(){

}
//开始发送请求传输数据
void Register::onHttpStart(){
    qDebug()<<"started really";
    doHttpPost();
    connect(this->mNetManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onHttpFinish(QNetworkReply*)));
}

//信号来自QNetworkAccessManager
void Register::onHttpFinish(QNetworkReply* reply){
    //对reply进行某些操作，这里没有

    //QVariant status_code=reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if(reply->error()==QNetworkReply::NoError)
        emit complete();
    else
        emit error();
}
//全部完成
void Register::onComplete(){

}
void Register::onError(){

}

//真实进行HTTP请求的函数
void Register::doHttpPost(){

    if( !mNetManager ) {
        mNetManager = new QNetworkAccessManager(this);
    }

    QString url=URLCONFIG::REGISTER_URL;

    //将计算出的特征值、人像照片、以及其他输入传递给服务器中

    //图像
    QFile file(imageSource);
    if(file.exists()) {
        if( !file.open(QIODevice::ReadOnly)) {
            qDebug()<<"error open file"<<endl;
            return;
        }
    }
    //读取所有文件
    QByteArray fileContent = file.readAll();
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
    tempStr += "\r\nContent-Disposition: form-data; name=\"file\"; filename=\""+getExt(file)+"\"\r\n";
    tempStr += "Content-Type: " + getType(file) + "\r\n\r\n";
    content.append(tempStr.toUtf8());
    content.append(fileContent);
    file.close();

    tempStr = "\r\n";
    tempStr +=startBoundary;
    tempStr += "\r\nContent-Disposition: form-data; name=\"temp.code\"\r\n\r\n";
    tempStr +=this->id;
    content.append(tempStr.toUtf8());

    tempStr = "\r\n";
    tempStr +=startBoundary;
    tempStr += "\r\nContent-Disposition: form-data; name=\"temp.name\"\r\n\r\n";
    //tempStr +=QString::fromLocal8Bit("失败了");
    tempStr +=this->name;
    content.append(tempStr.toUtf8());

    tempStr = "\r\n";
    tempStr +=startBoundary;
    tempStr += "\r\nContent-Disposition: form-data; name=\"temp.sex\"\r\n\r\n";
    tempStr +=this->sex;
    content.append(tempStr.toUtf8());

    tempStr = "\r\n";
    tempStr +=startBoundary;
    tempStr += "\r\nContent-Disposition: form-data; name=\"temp.type\"\r\n\r\n";
    tempStr +=this->label;
    content.append(tempStr.toUtf8());

    tempStr = "\r\n";
    tempStr +=startBoundary;
    tempStr += "\r\nContent-Disposition: form-data; name=\"temp.feature\"\r\n\r\n";
    for(int i=0;i<2047;i++)
        tempStr +=QString::number(this->feature[i])+" ";
    tempStr+=QString::number(this->feature[2047]);
    content.append(tempStr.toUtf8());

//    tempStr = "\r\n";
//    tempStr +=startBoundary;
//    tempStr += "\r\nContent-Disposition: form-data; name=\"productdetail\"\r\n\r\n";
//    tempStr +=QString::fromLocal8Bit("衣服的详情啊啊啊啊3333222");
//    content.append(tempStr.toUtf8());

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


/*
 * 根据形参得到文件的类型和名称
 */
QString Register::getExt(QFile &file)
{
    QFileInfo fileInfo(file);
    return fileInfo.fileName();
}

/*
 * 得到文件类型
 */
QString Register::getType(QFile &file) {
    QFileInfo fileInfo(file);
    QString ext = fileInfo.completeSuffix();
qDebug() << "ext:" << ext;
    QString fileExt = "";
    if( !ext.compare("jpg")) {
        fileExt = "image/jpeg";
    } else if(!ext.compare("mp3")) {
        fileExt = "audio/mpeg";
    } else if(!ext.compare("amr")) {
        fileExt = "audio/amr";
    } else if(!ext.compare("mp4")) {
        fileExt = "video/mp4";
    }
    return fileExt;
}
