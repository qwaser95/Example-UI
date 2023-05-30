#include "addeditres.h"
#include "ui_addeditres.h"
#include "extern.h"
#include <QDebug>

AddEditRES::AddEditRES(bool edit, QString title, QStringList rowDataRes, QWidget *parent, int row) :
  QDialog(parent),
  ui(new Ui::AddEditRES)
{
  m_edit = edit;
  curRow = row;
  ui->setupUi(this);
  this->setWindowTitle(title);

  DB_SelectTipiRES();
  ui->DBLUpCBox_NaimenovanieTipaRES->clear();
  while (globalQuery.next()) {
    ui->DBLUpCBox_NaimenovanieTipaRES->addItem(globalQuery.value(1).toString());
  }


  if (ui->DBCBox_TipAzimuta->currentIndex() != 2) {
    ui->label_28->setVisible(false);
    ui->DBEdit_AzimutDopolnitelniy->setVisible(false);
  }
  else {
    ui->label_28->setVisible(true);
    ui->DBEdit_AzimutDopolnitelniy->setVisible(true);
  }

  if (ui->DBCBox_TipUchetaDopRES->currentIndex() == 0) {
    ui->label_29->setVisible(false);
    ui->DBEdit_RadiusDopRES->setVisible(false);
  }
  else {
    ui->label_29->setVisible(true);
    ui->DBEdit_RadiusDopRES->setVisible(true);
  }

  //считывание строки данных РЭС
  if(rowDataRes.count() > 0 && rowDataRes.count() <= 18) {
    ui->DBEdit_NaimenovanieRES->setText(rowDataRes[0]);
    ui->DBLUpCBox_NaimenovanieTipaRES->setCurrentText(rowDataRes[1]);
    ui->DBEdit_MestoRazmescheniya->setText(rowDataRes[17]);
    ui->DBEdit_ShirotaStr->setText(rowDataRes[2]);
    ui->DBEdit_ShirotaDes->setText(rowDataRes[3]);
    ui->DBEdit_DolgotaStr->setText(rowDataRes[4]);
    ui->DBEdit_DolgotaDes->setText(rowDataRes[5]);
    ui->DBCBox_TipAzimuta->setCurrentText(rowDataRes[6]);
    ui->DBEdit_AzimutOsnovnoy->setValue(rowDataRes[7].toInt());
    ui->DBEdit_AzimutDopolnitelniy->setValue(rowDataRes[8].toInt());
    ui->DBEdit_Chastota->setText(rowDataRes[9]);
    ui->DBCBox_OslablenieSF->setCurrentText(rowDataRes[10]);
    ui->DBCBox_TipUchetaDopRES->setCurrentText(rowDataRes[11]);
    ui->DBEdit_RadiusDopRES->setValue(rowDataRes[12].toInt());
    ui->DBEdit_Porog1->setText(rowDataRes[13]);
    ui->DBEdit_Porog2->setText(rowDataRes[14]);
    ui->DBEdit_Porog3->setText(rowDataRes[15]);
    ui->DBCBox_Polyarizaciya->setCurrentText(rowDataRes[16]);
  }

  if (!m_edit) {
    ui->Button_RESPost->hide();
    ui->Button_RESComplete->setText("Добавить");
  }
}

AddEditRES::~AddEditRES()
{
  delete ui;
}

void AddEditRES::on_Button_RESCancel_clicked()
{
  this->close();
}

void AddEditRES::on_DBCBox_TipAzimuta_currentIndexChanged(int index)
{
    if (index != 2) {
      ui->label_28->setVisible(false);
      ui->DBEdit_AzimutDopolnitelniy->setVisible(false);
    }
    else {
      ui->label_28->setVisible(true);
      ui->DBEdit_AzimutDopolnitelniy->setVisible(true);
    }
}

void AddEditRES::on_DBCBox_TipUchetaDopRES_currentIndexChanged(int index)
{
  if (index == 0) {
    ui->label_29->setVisible(false);
    ui->DBEdit_RadiusDopRES->setVisible(false);
  }
  else {
    ui->label_29->setVisible(true);
    ui->DBEdit_RadiusDopRES->setVisible(true);
  }
}

void AddEditRES::on_Button_RESPost_clicked()
{
  processAddEditRES(false);
}

void AddEditRES::on_Button_RESComplete_clicked()
{
  processAddEditRES(true);
}

void AddEditRES::processAddEditRES(bool close)
{
  QStringList dataRES;
  dataRES.append(ui->DBEdit_NaimenovanieRES->text());
  dataRES.append(ui->DBLUpCBox_NaimenovanieTipaRES->currentText());
  dataRES.append(ui->DBEdit_MestoRazmescheniya->text());
  dataRES.append(ui->DBEdit_ShirotaStr->text());
  if (ui->DBEdit_ShirotaDes->text() == "") {QMessageBox::warning(this, "Незаполненное поле", "Введите десятичную широту");return;}
  dataRES.append(ui->DBEdit_ShirotaDes->text());
  dataRES.append(ui->DBEdit_DolgotaStr->text());
  if (ui->DBEdit_DolgotaDes->text() == "") {QMessageBox::warning(this, "Незаполненное поле", "Введите десятичную долготу");return;}
  dataRES.append(ui->DBEdit_DolgotaDes->text());

  if (ui->DBCBox_TipAzimuta->currentText() == "Азимут") dataRES.append(QString::number(0));
  else if (ui->DBCBox_TipAzimuta->currentText() == "Вращение") dataRES.append(QString::number(1));
  else dataRES.append(QString::number(2));

  dataRES.append(ui->DBEdit_AzimutOsnovnoy->text());
  if (ui->DBEdit_AzimutDopolnitelniy->text() == "") dataRES.append("0");
  else dataRES.append(ui->DBEdit_AzimutDopolnitelniy->text());
  if (ui->DBEdit_Chastota->text() == "") {QMessageBox::warning(this, "Незаполненное поле", "Введите частоту");return;}
  dataRES.append(ui->DBEdit_Chastota->text());
  dataRES.append(ui->DBCBox_OslablenieSF->currentText());

  if (ui->DBCBox_TipUchetaDopRES->currentText() == "без учёта") dataRES.append(QString::number(0));
  else if (ui->DBCBox_TipUchetaDopRES->currentText() == "с учётом «R»") dataRES.append(QString::number(1));
  else dataRES.append(QString::number(2));

  if (ui->DBEdit_RadiusDopRES->text() == "") dataRES.append("2");
  else dataRES.append(ui->DBEdit_RadiusDopRES->text());
  if (ui->DBEdit_Porog1->text() == "") dataRES.append("-40");
  else dataRES.append(ui->DBEdit_Porog1->text());
  if (ui->DBEdit_Porog2->text() == "") dataRES.append("-40");
  else dataRES.append(ui->DBEdit_Porog2->text());
  if (ui->DBEdit_Porog3->text() == "") dataRES.append("-124");
  else dataRES.append(ui->DBEdit_Porog3->text());
  dataRES.append(ui->DBCBox_Polyarizaciya->currentText());

  if (m_edit) {
    DB_EditRES(QString::number(curRow), dataRES);
  }
  else {
    DB_AddRES(dataRES);
  }
  if (close) this->close();
}

void AddEditRES::on_DBEdit_ShirotaDes_textEdited(const QString &arg1)
{
  ui->DBEdit_ShirotaStr->setText(afGeoCoordDesToStr(arg1.toDouble()));
  if (ui->DBEdit_ShirotaDes->text() == "") ui->DBEdit_ShirotaStr->clear();
}

void AddEditRES::on_DBEdit_DolgotaDes_textEdited(const QString &arg1)
{
  ui->DBEdit_DolgotaStr->setText(afGeoCoordDesToStr(arg1.toDouble()));
  if (ui->DBEdit_DolgotaDes->text() == "") ui->DBEdit_DolgotaStr->clear();
}
