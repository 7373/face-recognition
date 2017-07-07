#ifndef VIVOEXPRESSION_H
#define VIVOEXPRESSION_H

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
#include <QTextToSpeech>


class QTextToSpeech;

class VivoExpression : public QThread
{
    Q_OBJECT
    void run() Q_DECL_OVERRIDE;


    Q_PROPERTY(QString hint READ getHint WRITE setHint NOTIFY HintChanged)


public:
    VivoExpression();
    Q_INVOKABLE void expressionCallInQml();

    static QTextToSpeech * m_speech;


    QString hint;
    QString getHint(){return hint;}
    void setHint(QString newhint){hint=newhint;}

signals:
    //全部完成
    void complete();
    void HintChanged(QString hint);

public slots:
    //全部完成
    void onComplete();
    void onHintChanged(QString hint);
};

#endif // VIVOEXPRESSION_H
