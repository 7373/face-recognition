#ifndef CAPTURE_H
#define CAPTURE_H

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
#include <QList>
#include "dataobjectcapture.h"
#include "dataobjectlist.h"


class Capture : public QThread
{
    Q_OBJECT
    void run() Q_DECL_OVERRIDE;

public:
    Capture();
    Q_INVOKABLE void captureCallInQml();
    Q_INVOKABLE void stopCallInQml();

};

#endif // CAPTURE_H
