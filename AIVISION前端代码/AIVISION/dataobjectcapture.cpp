#include "dataobjectcapture.h"
#include <QDebug>


DataObjectCapture::DataObjectCapture(QObject *parent)
    : QObject(parent)
{
}

DataObjectCapture::DataObjectCapture(const QString &path, QObject *parent)
    : QObject(parent), m_path(path)
{
}

QString DataObjectCapture::getPath() const
{
    return m_path;
}

void DataObjectCapture::setPath(const QString &path)
{
    if (path != m_path) {
        m_path =path;
        emit pathChanged();
    }
}



