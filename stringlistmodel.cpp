#include "stringlistmodel.h"

StringListModel::StringListModel()
{

}

int StringListModel::rowCount(const QModelIndex &parent) const
{
  return 3;
}

int StringListModel::columnCount(const QModelIndex &parent) const
{
  return 2;
}

QVariant StringListModel::data(const QModelIndex &index, int role) const
{
//  if (role == Qt::DisplayRole) {
//    QString unswer = QString("row = ") + QString::number(index.row()) + "  col = " + QString::number(index.column());
//    // строкой выше мы формируем ответ. QString::number преобразует число в текст
//    return QVariant(unswer);
//  }
//  return QVariant();
}
