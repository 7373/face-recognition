#include "dataobjectlist.h"
#include <QAbstractItemModel>


DataObjectList::DataObjectList()
{

}
int DataObjectList::rowCount(const QModelIndex &) const
{
    return DataObjectList::datalist.count();
}
void DataObjectList::add(QString filepath){
    int row=0;
    beginInsertRows(QModelIndex(), row, row);
    DataObjectList::datalist.insert(row, new DataObjectCapture("file:///"+filepath));
    endInsertRows();
}

DataObjectList* DataObjectList::instance=new DataObjectList();
DataObjectList* DataObjectList::getInstance(){
    return instance;
}

QHash<int, QByteArray> DataObjectList::roleNames() const
{
//    static const QHash<int, QByteArray> roles {
//        { IMAGEPATH, "imagepath" }
//    };
//    return roles;
    QHash<int, QByteArray>  d;
    d[datatype::IMAGEPATH] = "imagepath";
    return  d;
}

QVariant DataObjectList::data(const QModelIndex &index, int role) const
{
    if (index.row() < rowCount()){
        switch (role) {
            case IMAGEPATH: return DataObjectList::datalist.at(index.row())->m_path;
            default: return QVariant();
        }
    }
}
