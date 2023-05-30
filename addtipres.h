#pragma once

#include <QDialog>

namespace Ui {
class AddTipRes;
}

class AddTipRes : public QDialog
{
  Q_OBJECT

public:
  explicit AddTipRes(QWidget *parent = 0);
  ~AddTipRes();

private slots:
  void on_DefaultBTN_clicked();
  void on_ClearBTN_clicked();
  void on_AddBTN_clicked();

private:
  Ui::AddTipRes *ui = nullptr;

signals:
  void signal_update_table();
};
