#ifndef DATAOBJECTLIST_H
#define DATAOBJECTLIST_H

#include <QObject>
#include <QList>
#include <QAbstractItemModel>
#include "dataobjectcapture.h"

class DataObjectList : public QAbstractListModel
{
    Q_OBJECT
public:
    enum datatype{
        IMAGEPATH=1
    };
    Q_ENUM(datatype)

    static DataObjectList* getInstance();

    static DataObjectList* instance;

    QList<DataObjectCapture*> datalist;
    int rowCount(const QModelIndex & = QModelIndex()) const;
    void add(QString filepath);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

private:
    DataObjectList();
};

#endif // DATAOBJECTLIST_H
