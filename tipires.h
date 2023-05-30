#pragma once

#include <QDialog>
#include <QStandardItemModel>
#include "ui_tipires.h"
#include "dbsqlqueries.h"
#include "RbTableHeaderView.h"
#include "addtipres.h"

class TipiRes : public QDialog
{

  Q_OBJECT

public:
  TipiRes(QWidget *parent = nullptr);
  virtual ~TipiRes(){delete  ui;}

  QStandardItemModel* dataModel = nullptr;
  AddTipRes *TipRes             = nullptr;

private:
  Ui::TipiResUi *ui             = nullptr;

  void drawDBTable_TipiRES();

protected:

signals:

private slots:

  void on_Button_TipiRESDeleteAll_clicked();
  void on_Button_TipiRESPost_clicked();
  void on_Button_TipiRESDelete_clicked();
  void on_Button_TipiRESInsert_clicked();

public slots:

  void update_table();
};
