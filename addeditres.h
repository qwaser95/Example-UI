#pragma once

#include <QDialog>
#include "dbsqlqueries.h"

namespace Ui {
class AddEditRES;
}

class AddEditRES : public QDialog
{
  Q_OBJECT

public:
  explicit AddEditRES(bool, QString, QStringList = {}, QWidget *parent = nullptr, int = 0);
  ~AddEditRES();

  bool m_edit;
  int curRow;

private slots:
  void on_Button_RESCancel_clicked();
  void on_DBCBox_TipAzimuta_currentIndexChanged(int index);
  void on_DBCBox_TipUchetaDopRES_currentIndexChanged(int index);
  void on_Button_RESPost_clicked();
  void on_Button_RESComplete_clicked();
  void processAddEditRES(bool);
  void on_DBEdit_ShirotaDes_textEdited(const QString &arg1);
  void on_DBEdit_DolgotaDes_textEdited(const QString &arg1);

private:
  Ui::AddEditRES *ui = nullptr;

};
