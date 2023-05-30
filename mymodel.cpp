#include "mymodel.h"

MyModel::MyModel(QObject *parent)
    :QStandardItemModel(parent)
{
}

Qt::ItemFlags MyModel::flags(const QModelIndex &index) const
{
      Qt::ItemFlags flags = QStandardItemModel::flags(index);
  if (index.column() == 0)
    flags |= Qt::ItemIsUserCheckable | Qt::ItemIsEditable;
  return flags;
}

bool MyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
   if(role==Qt::CheckStateRole)
    return QStandardItemModel::setData(index,value.toBool(),Qt::EditRole);
  return QStandardItemModel::setData(index,value);
}


QVariant MyModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QStandardItemModel::data(index, role);
  switch (role)
  {
    case Qt::DisplayRole:
    case Qt::EditRole:
      if(index.column() == 0)
        return value.toInt() != 0 ? QString::fromUtf8("") : QString::fromUtf8("");
      return QStandardItemModel::data(index,role);
    case Qt::CheckStateRole:
      if (index.column() == 0)
        return (QStandardItemModel::data(index).toInt() != 0) ? Qt::Checked : Qt::Unchecked;
  }
  return value;
}



