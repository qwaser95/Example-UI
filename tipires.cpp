#include "tipires.h"
#include "extern.h"
#include <QDebug>
#include <QResizeEvent>

TipiRes::TipiRes(QWidget *parent)
      : QDialog (parent), ui(new Ui::TipiResUi)
{
  ui->setupUi(this);
  DB_SelectTipiRES();
  drawDBTable_TipiRES();
}

void TipiRes::drawDBTable_TipiRES()
{
  RbTableHeaderView* hHead = new RbTableHeaderView(Qt::Horizontal,3,6);
  QAbstractItemModel* hModel = hHead->model();
  dataModel = new QStandardItemModel;

  hHead->setSpan(0,0,3,0);
  hHead->setSpan(0,1,2,0);
  hHead->setSpan(0,2,2,0);
  hHead->setSpan(0,3,2,0);
  hHead->setSpan(0,4,0,2);
  hModel->setData(hModel->index(0,0),QString("Наименование\nтипа РЭС"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,1),QString("Потери в\nАФТ"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,1),QString("дБ"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,2),QString("Коэффициент\nусиления\nантенны"),Qt::DisplayRole);
  hModel->setData(hModel->index(1,4),QString("гориз.\nплоскости"),Qt::DisplayRole);
  hModel->setData(hModel->index(1,5),QString("верт.\nплоскости"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,3),QString("Уровень\nбоковых\nлепестков ДН"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,2),QString("дБ"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,3),QString("дБ"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,4),QString("°"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,5),QString("°"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,4),QString("Ширина ДН в"),Qt::DisplayRole);


  hHead->setRowHeight(0,25);
  hHead->setRowHeight(1,35);
  hHead->setRowHeight(2,25);

  hHead->setSectionResizeMode(0,QHeaderView::Stretch);
  hHead->resizeSection(1,80);
  hHead->resizeSection(4,80);
  hHead->resizeSection(5,80);

  while (globalQuery.next()) {
    QList<QStandardItem*> items;
    for (int i = 1; i < 7; i++) items.append(new QStandardItem(globalQuery.value(i).toString()));
    dataModel->appendRow(items);
  }

  ui->DBTable_TipiRES->setModel(dataModel);
  ui->DBTable_TipiRES->setHorizontalHeader(hHead);
  ui->DBTable_TipiRES->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  ui->DBTable_TipiRES->verticalHeader()->setDefaultSectionSize(20);
}

void TipiRes::on_Button_TipiRESDeleteAll_clicked()
{
    dataModel->clear();
    QString naimenovanie_tipa_res;
    for (int i=0; i < dataModel->rowCount(); i++)
      {
        naimenovanie_tipa_res = dataModel->item(i, 0)->text();
        DB_TipRES(naimenovanie_tipa_res);
      }
    update_table();
}

void TipiRes::on_Button_TipiRESPost_clicked()
{
    this->close();
}

void TipiRes::on_Button_TipiRESDelete_clicked()
{
  if (!dataModel->rowCount()) return;
  QString naimenovanie_tipa_res;
  naimenovanie_tipa_res = dataModel->item(ui->DBTable_TipiRES->currentIndex().row(), 0)->text();
  DB_TipRES(naimenovanie_tipa_res);
  update_table();
}

void TipiRes::on_Button_TipiRESInsert_clicked()
{
  TipRes = new AddTipRes(this);

  connect (TipRes,      SIGNAL(signal_update_table()),
           this,        SLOT(update_table()));

  TipRes->exec();
}

void TipiRes::update_table()
{
  DB_SelectTipiRES();
  dataModel->clear();
  while (globalQuery.next()) {
    QList<QStandardItem*> items;
    for (int i = 1; i < 7; i++) items.append(new QStandardItem(globalQuery.value(i).toString()));
    dataModel->appendRow(items);
  }
}
