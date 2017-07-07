#ifndef DATAOBJECTCAPTURE_H
#define DATAOBJECTCAPTURE_H

#include <QObject>
#include <QList>


class DataObjectCapture : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString path READ getPath WRITE setPath NOTIFY pathChanged)
//![0]

public:
    DataObjectCapture(QObject *parent=0);
    DataObjectCapture(const QString &path, QObject *parent=0);

    QString getPath() const;
    void setPath(const QString &path);

    QString m_path;
signals:
    void pathChanged();


//![1]
};

#endif // DATAOBJECTCAPTURE_H
