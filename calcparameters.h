#pragma once

#include <QDialog>

namespace Ui {
class CalcParameters;
}

class CalcParameters : public QDialog
{
  Q_OBJECT

public:
  explicit CalcParameters(QWidget *parent = 0);
  ~CalcParameters();

  void takeExternFromUi();
private slots:

  void on_Button_Backward_clicked();
  void on_Button_Execute_clicked();

  void on_CBox_IzmenenieMestopologeniyaBS_currentIndexChanged(int index);
  void on_CBox_IzmenenieVisotiPodvesaBS_currentIndexChanged(int index);
  void on_CBox_IspolzovanieChTP_currentIndexChanged(int index);
  void on_CBox_UchetZoniObslugivaniya_currentIndexChanged(int index);
  void on_CBox_PolyarizaciyaBS_currentIndexChanged(int index);
  void on_ChBox_AS_toggled(bool checked);
  void on_CBox_ModelRaschetaAS_currentIndexChanged(int index);

private:
  Ui::CalcParameters *ui = nullptr;

  void naimenovanieRES();

  void init_IzmenenieMestopologeniyaBS(int);
  void init_IzmenenieVisotiPodvesaBS(int);
  void init_IspolzovanieChTP(int);
  void init_IspolzovanieChTPstr(QString);
  void init_UchetZoniObslugivaniya(int);
  void init_UchetZoniObslugivaniyastr(QString);
  void init_PolyarizaciyaBS(int);
  void init_PolyarizaciyaBSstr(QString);
  void init_ModelRaschetaAS(int);
  void init_AS(bool);
  void start_Calc();

signals:
  QStringList signal_take_naimenovanieRES();

};
