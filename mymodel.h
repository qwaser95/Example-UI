#pragma once

#include <QStandardItemModel>
#include <QFont>
#include <QBrush>
#include <QDebug>

class MyModel : public QStandardItemModel
{
    Q_OBJECT
public:

    MyModel(QObject *parent);
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
};
