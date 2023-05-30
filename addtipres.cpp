#include "addtipres.h"
#include "ui_addtipres.h"
#include "dbsqlqueries.h"
#include "extern.h"

AddTipRes::AddTipRes(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::AddTipRes)
{
  ui->setupUi(this);
}

AddTipRes::~AddTipRes()
{
  delete ui;
}

void AddTipRes::on_DefaultBTN_clicked()
{
  ui->Edit_Naimenovanie->setText("");
  ui->Edit_AFT->setText("0");
  ui->Edit_koef->setText("23");
  ui->Edit_BLDN->setText("-15");
  ui->Edit_goriz->setText("8.6");
  ui->Edit_vert->setText("8.6");
}

void AddTipRes::on_ClearBTN_clicked()
{
  ui->Edit_Naimenovanie->setText("");
  ui->Edit_AFT->setText("");
  ui->Edit_koef->setText("");
  ui->Edit_BLDN->setText("");
  ui->Edit_goriz->setText("");
  ui->Edit_vert->setText("");
}

void AddTipRes::on_AddBTN_clicked()
{
  QStringList TipResAdd;
  DB_TakeIdTipRES();
  int id_tipa_res;
  globalQuery.next();
  id_tipa_res = globalQuery.value(0).toInt() + 1;
  TipResAdd.append(QString::number(id_tipa_res));
  TipResAdd.append(ui->Edit_Naimenovanie->text());
  TipResAdd.append(ui->Edit_AFT->text());
  TipResAdd.append(ui->Edit_koef->text());
  TipResAdd.append(ui->Edit_BLDN->text());
  TipResAdd.append(ui->Edit_goriz->text());
  TipResAdd.append(ui->Edit_vert->text());
  DB_InsertTipRES(TipResAdd);

  emit signal_update_table();

  this->close();
}
