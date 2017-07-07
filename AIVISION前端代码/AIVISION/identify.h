#ifndef IDENTIFY_H
#define IDENTIFY_H

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


class Identify : public QThread
{
    Q_OBJECT
    void run() Q_DECL_OVERRIDE;

    Q_PROPERTY(QString similarity READ getSimilarity WRITE setSimilarity)

public:
    Identify();
    Q_INVOKABLE void identifyCallInQml(QString imageSource, QString imageSource2);

    QString imageSource;
    QString imageSource2;

    QString getSimilarity() const {return similarity;}
    void setSimilarity(QString sim){similarity=sim;}
    QString similarity;

signals:
    //全部完成
    void complete();

public slots:
    //全部完成
    void onComplete();

};

#endif // IDENTIFY_H
