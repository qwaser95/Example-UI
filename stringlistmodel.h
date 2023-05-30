#ifndef STRINGLISTMODEL_H
#define STRINGLISTMODEL_H

#include <QAbstractTableModel>

class StringListModel : public QAbstractItemModel
{

    Q_OBJECT

public:
  StringListModel();
  ~StringListModel(){}

private:
  int rowCount(const QModelIndex &parent) const;
  int columnCount(const QModelIndex &parent) const;
  QVariant data(const QModelIndex &index, int role) const;

};

#endif // STRINGLISTMODEL_H
