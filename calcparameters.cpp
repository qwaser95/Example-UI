#include "calcparameters.h"
#include "ui_calcparameters.h"
#include "extern.h"

CalcParameters::CalcParameters(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::CalcParameters)
{
  ui->setupUi(this);
  ui->ChBox_AS->setChecked(true);

   //Считывание значений
  ui->Edit_DiapazoniChastot->setText(DiapazonChastot);


  if(IzmenenieMestopologeniyaBS == true) {
      ui->CBox_IzmenenieMestopologeniyaBS->setEnabled(true);
      ui->CBox_IzmenenieMestopologeniyaBS->setCurrentIndex(1);
      ui->Label_RadiusIzmeneniyaMestopologeniyaBS->setText("Радиус изменения местоположения " + QString::number(RadiusIzmeneniyaMestopologeniyaBS) + " м");
  }
  else {
      ui->CBox_IzmenenieMestopologeniyaBS->setEnabled(false);
      ui->CBox_IzmenenieMestopologeniyaBS->setCurrentIndex(0);
      ui->Label_RadiusIzmeneniyaMestopologeniyaBS->setText("Радиус изменения местоположения");
  }

  if(IzmenenieVisotiPodvesaBS == true) {
      ui->CBox_IzmenenieVisotiPodvesaBS->setEnabled(true);
      ui->CBox_IzmenenieVisotiPodvesaBS->setCurrentIndex(1);
      ui->Label_UvelichenieVisotiPodvesa->setText("Поднять высоту подвеса антенны БС на " + QString::number(UvelichenieVisotiPodvesa) + " м");
  }
  else {
      ui->CBox_IzmenenieVisotiPodvesaBS->setEnabled(false);
      ui->CBox_IzmenenieVisotiPodvesaBS->setCurrentIndex(0);
      ui->Label_UvelichenieVisotiPodvesa->setText("Поднять высоту подвеса антенны БС");
  }

  if (IspolzovanieChTP == "ChTP")
      ui->CBox_IspolzovanieChTP->setCurrentIndex(0);
  else if (IspolzovanieChTP == "Vraschenie")
      ui->CBox_IspolzovanieChTP->setCurrentIndex(1);
  else if (IspolzovanieChTP == "Kombinirovanniy") {
      ui->CBox_IspolzovanieChTP->setCurrentIndex(2);
      ui->Edit_DopustimoeOgranichenie->setValue(DopustimoeOgranichenie);
  }

  ui->Edit_RadiusVliyaniyaAS->setValue(RadiusVliyaniyaAS);
  ui->Edit_EIIMAbonenta->setValue(afRoundTo(EIIMAbonenta, -1));
  ui->Edit_UrovenZapuskaASBS->setValue(UrovenZapuskaASBS);

  if (ModelRaschetaAS == 0 || ModelRaschetaAS == 1 || ModelRaschetaAS == 2 || ModelRaschetaAS == 3 || ModelRaschetaAS == 4 ) {
        ui->Edit_ProcentVremeniAS->setValue(ProcentVremeniAS);
        if(ModelRaschetaAS == 0) {

           ui->Edit_ProcentMestAS->setValue(ProcentMestAS);

           switch (VisotaEtalonnayaAS) {
           case 10:
             ui->CBox_VisotaEtalonnayaAS->setCurrentIndex(0);
             break;
           case 20:
             ui->CBox_VisotaEtalonnayaAS->setCurrentIndex(1);
             break;
           case 30:
             ui->CBox_VisotaEtalonnayaAS->setCurrentIndex(2);
             break;
           }
           ui->CBox_NapravlenieAnalizaAS->setCurrentIndex(NapravlenieAnalizaAS);
        }
  }

  if (UchetZoniObslugivaniya == "NeUchitivat") ui->CBox_UchetZoniObslugivaniya->setCurrentIndex(0);
  else if (UchetZoniObslugivaniya == "UchitivatChTP") ui->CBox_UchetZoniObslugivaniya->setCurrentIndex(1);
  else if (UchetZoniObslugivaniya == "UchitivatRadius") { ui->CBox_UchetZoniObslugivaniya->setCurrentIndex(2);
           ui->Edit_RadiusZoniObslugivaniya->setValue(afRoundTo(RadiusZoniObslugivaniya, -3));
  }

  if(PolyarizaciyaBS == "ChTP")  ui->CBox_PolyarizaciyaBS->setCurrentIndex(0);
  else if(PolyarizaciyaBS == "Ukazannaya")  { ui->CBox_PolyarizaciyaBS->setCurrentIndex(1);

          ui->ChBox_PolyarizaciyaH->setChecked(polH);
          ui->ChBox_PolyarizaciyaV->setChecked(polV);
          ui->ChBox_PolyarizaciyaX->setChecked(polX);
          ui->ChBox_PolyarizaciyaO->setChecked(polO);
  }

  init_IzmenenieMestopologeniyaBS(IzmenenieMestopologeniyaBS);
  init_IzmenenieVisotiPodvesaBS(IzmenenieVisotiPodvesaBS);
  init_IspolzovanieChTPstr(IspolzovanieChTP);
  init_UchetZoniObslugivaniyastr(UchetZoniObslugivaniya);
  init_PolyarizaciyaBSstr(PolyarizaciyaBS);
  init_AS(ui->ChBox_AS->isChecked());
  init_ModelRaschetaAS(ModelRaschetaAS);
}

CalcParameters::~CalcParameters()
{
  delete ui;
}

void CalcParameters::takeExternFromUi()
{
  if (ui->CBox_IzmenenieMestopologeniyaBS->currentIndex() == 0) IzmenenieMestopologeniyaBS = false;
  else IzmenenieMestopologeniyaBS = true;
  if (ui->CBox_IzmenenieVisotiPodvesaBS->currentIndex() == 0) IzmenenieVisotiPodvesaBS = false;
  else IzmenenieVisotiPodvesaBS = true;
  DiapazonChastot = ui->Edit_DiapazoniChastot->text();
  if (ui->CBox_IspolzovanieChTP->currentIndex() == 0) IspolzovanieChTP = "ChTP";
  else if (ui->CBox_IspolzovanieChTP->currentIndex() == 1) IspolzovanieChTP = "Vraschenie";
  else IspolzovanieChTP = "Kombinirovanniy";
  RadiusVliyaniyaAS = ui->Edit_RadiusVliyaniyaAS->value();
  EIIMAbonenta = ui->Edit_EIIMAbonenta->value();
  UrovenZapuskaASBS = ui->Edit_UrovenZapuskaASBS->value();
  ModelRaschetaAS = ui->CBox_ModelRaschetaAS->currentIndex();
  ProcentVremeniAS = ui->Edit_ProcentVremeniAS->value();
  ProcentMestAS = ui->Edit_ProcentMestAS->value();
  VisotaEtalonnayaAS = (ui->CBox_VisotaEtalonnayaAS->currentIndex() * 10) + 10;
  NapravlenieAnalizaAS = ui->CBox_NapravlenieAnalizaAS->currentIndex();
  if (ui->CBox_UchetZoniObslugivaniya->currentIndex() == 0) UchetZoniObslugivaniya = "NeUchitivat";
  else if (ui->CBox_UchetZoniObslugivaniya->currentIndex() == 1) UchetZoniObslugivaniya = "UchitivatChTP";
  else UchetZoniObslugivaniya = "UchitivatRadius";
  if (ui->CBox_PolyarizaciyaBS->currentIndex() == 0) PolyarizaciyaBS = "ChTP";
  else PolyarizaciyaBS = "Ukazannaya";
  if (PolyarizaciyaBS == "Ukazannaya") {
    polH = ui->ChBox_PolyarizaciyaH->isChecked();
    polO = ui->ChBox_PolyarizaciyaO->isChecked();
    polV = ui->ChBox_PolyarizaciyaV->isChecked();
    polX = ui->ChBox_PolyarizaciyaX->isChecked();
  }
}


void CalcParameters::on_Button_Backward_clicked()
{
  takeExternFromUi();
  this->close();
}

void CalcParameters::on_Button_Execute_clicked()
{
  QStringList naimenovanieRES;
  QStringList list;
  QStringList list_from_tipi_res;
  naimenovanieRES = emit signal_take_naimenovanieRES();
  foreach (QString value, naimenovanieRES) {
    list.clear();
    list_from_tipi_res.clear();
    DB_SelectRES(value);
    while (globalQuery.next()) {
      for (int i = 0; i<17; i++)
        list.append(globalQuery.value(i).toString());
    }
    DB_SelectAllFromTipiRes(list[2]);
    while (globalQuery.next()) {
      for (int i = 0; i<7; i++)
      list_from_tipi_res.append(globalQuery.value(i).toString());
    }
    DB_InsertRESRascheta(list,list_from_tipi_res, GUIDRaschetaStr_LoadFromDataBase);
  }

  takeExternFromUi();
  DB_UpdateZnacheniestr();
  start_Calc();
  this->close();
}

void CalcParameters::naimenovanieRES()
{

}

void CalcParameters::init_IzmenenieMestopologeniyaBS(int index)
{
  if (index == 0) ui->Label_RadiusIzmeneniyaMestopologeniyaBS->hide();
  else ui->Label_RadiusIzmeneniyaMestopologeniyaBS->show();
}

void CalcParameters::init_IzmenenieVisotiPodvesaBS(int index)
{
  if(index == 0) ui->Label_UvelichenieVisotiPodvesa->hide();
  else ui->Label_UvelichenieVisotiPodvesa->show();
}

void CalcParameters::init_IspolzovanieChTP(int index)
{
  if(index != 2) {
    ui->Edit_DopustimoeOgranichenie->hide();
    ui->Label_DopustimoeOgranichenie->hide();
    ui->Label_DopustimoeOgranichenieSI->hide();
  }
  else {
    ui->Edit_DopustimoeOgranichenie->show();
    ui->Label_DopustimoeOgranichenie->show();
    ui->Label_DopustimoeOgranichenieSI->show();
  }
}

void CalcParameters::init_IspolzovanieChTPstr(QString str)
{
  if(str != "Kombinirovanniy") {
    ui->Edit_DopustimoeOgranichenie->hide();
    ui->Label_DopustimoeOgranichenie->hide();
    ui->Label_DopustimoeOgranichenieSI->hide();
  }
  else {
    ui->Edit_DopustimoeOgranichenie->show();
    ui->Label_DopustimoeOgranichenie->show();
    ui->Label_DopustimoeOgranichenieSI->show();
  }
}

void CalcParameters::init_UchetZoniObslugivaniya(int index)
{
  if(index != 2) {
    ui->Edit_RadiusZoniObslugivaniya->hide();
    ui->Label_RadiusZoniObslugivaniya->hide();
    ui->Label_RadiusZoniObslugivaniyaSI->hide();
  }
  else {
    ui->Edit_RadiusZoniObslugivaniya->show();
    ui->Label_RadiusZoniObslugivaniya->show();
    ui->Label_RadiusZoniObslugivaniyaSI->show();
  }
}

void CalcParameters::init_UchetZoniObslugivaniyastr(QString str)
{
  if(str != "UchitivatRadius") {
    ui->Edit_RadiusZoniObslugivaniya->hide();
    ui->Label_RadiusZoniObslugivaniya->hide();
    ui->Label_RadiusZoniObslugivaniyaSI->hide();
  }
  else {
    ui->Edit_RadiusZoniObslugivaniya->show();
    ui->Label_RadiusZoniObslugivaniya->show();
    ui->Label_RadiusZoniObslugivaniyaSI->show();
  }
}

void CalcParameters::init_PolyarizaciyaBS(int index)
{
  if (index == 1) {
    ui->ChBox_PolyarizaciyaH->show();
    ui->ChBox_PolyarizaciyaO->show();
    ui->ChBox_PolyarizaciyaV->show();
    ui->ChBox_PolyarizaciyaX->show();
  }
  else {
    ui->ChBox_PolyarizaciyaH->hide();
    ui->ChBox_PolyarizaciyaO->hide();
    ui->ChBox_PolyarizaciyaV->hide();
    ui->ChBox_PolyarizaciyaX->hide();
  }
}

void CalcParameters::init_PolyarizaciyaBSstr(QString str)
{
  if (str == "Ukazannaya") {
    ui->ChBox_PolyarizaciyaH->show();
    ui->ChBox_PolyarizaciyaO->show();
    ui->ChBox_PolyarizaciyaV->show();
    ui->ChBox_PolyarizaciyaX->show();
  }
  else {
    ui->ChBox_PolyarizaciyaH->hide();
    ui->ChBox_PolyarizaciyaO->hide();
    ui->ChBox_PolyarizaciyaV->hide();
    ui->ChBox_PolyarizaciyaX->hide();
   }
}

void CalcParameters::init_ModelRaschetaAS(int index)
{
  if (index == 5) {
    ui->Label_ProcentVremeniAS->hide();
    ui->Edit_ProcentVremeniAS->hide();
    ui->Label_ProcentMestAS->hide();
    ui->Edit_ProcentMestAS->hide();
    ui->Label_VisotaEtalonnayaAS->hide();
    ui->CBox_VisotaEtalonnayaAS->hide();
    ui->Label_NapravlenieAnalizaAS->hide();
    ui->CBox_NapravlenieAnalizaAS->hide();
    ui->line_18->hide();
    ui->line_19->hide();
  }
  else if (index == 0) {
    ui->Label_ProcentVremeniAS->show();
    ui->Edit_ProcentVremeniAS->show();
    ui->Label_ProcentMestAS->show();
    ui->Edit_ProcentMestAS->show();
    ui->Label_VisotaEtalonnayaAS->show();
    ui->CBox_VisotaEtalonnayaAS->show();
    ui->Label_NapravlenieAnalizaAS->show();
    ui->CBox_NapravlenieAnalizaAS->show();
    ui->line_18->show();
    ui->line_19->show();
  }
  else {
    ui->Label_ProcentVremeniAS->show();
    ui->Edit_ProcentVremeniAS->show();
    ui->Label_ProcentMestAS->hide();
    ui->Edit_ProcentMestAS->hide();
    ui->Label_VisotaEtalonnayaAS->hide();
    ui->CBox_VisotaEtalonnayaAS->hide();
    ui->Label_NapravlenieAnalizaAS->hide();
    ui->CBox_NapravlenieAnalizaAS->hide();
    ui->line_18->hide();
    ui->line_19->hide();
  }
}

void CalcParameters::init_AS(bool checked)
{
  if (checked) {
    ui->widget_8->setEnabled(true);
  }
  else ui->widget_8->setEnabled(false);
}

void CalcParameters::start_Calc()
{
  QString program = "/root/build-GSM-1800ARM2Calc-Desktop-Release/GSM-1800ARM2Calc";
  QStringList arguments;
  arguments << "-style" << "fusion";
  QProcess *myProcess = new QProcess();
  myProcess->start(program, arguments);
}

void CalcParameters::on_CBox_IzmenenieMestopologeniyaBS_currentIndexChanged(int index)
{
  init_IzmenenieMestopologeniyaBS(index);
}

void CalcParameters::on_CBox_IzmenenieVisotiPodvesaBS_currentIndexChanged(int index)
{
  init_IzmenenieVisotiPodvesaBS(index);
}

void CalcParameters::on_CBox_IspolzovanieChTP_currentIndexChanged(int index)
{
  init_IspolzovanieChTP(index);
}

void CalcParameters::on_CBox_UchetZoniObslugivaniya_currentIndexChanged(int index)
{
  init_UchetZoniObslugivaniya(index);
}

void CalcParameters::on_CBox_PolyarizaciyaBS_currentIndexChanged(int index)
{
  init_PolyarizaciyaBS(index);
}

void CalcParameters::on_ChBox_AS_toggled(bool checked)
{
  init_AS(checked);
}

void CalcParameters::on_CBox_ModelRaschetaAS_currentIndexChanged(int index)
{
  init_ModelRaschetaAS(index);
}
