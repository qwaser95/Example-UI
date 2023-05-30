#pragma once

#include <QDialog>
#include <qfilesystemmodel.h>
#include <QTreeView>
#include <QtDebug>

namespace Ui {
class LoadFromDirectory;
}

class LoadFromDirectory : public QDialog
{
  Q_OBJECT

public:
  explicit LoadFromDirectory(QWidget *parent = nullptr);
  ~LoadFromDirectory();
  QFileSystemModel *model = nullptr;


private slots:
  void on_pushButton_clicked();
  void on_treeView_clicked(const QModelIndex &index);

private:
  Ui::LoadFromDirectory *ui = nullptr;

signals:
  void signal_refreshTableRaschet(bool);
  int signal_loadRezultatiARM1FromDirectory(const QString&);
};
