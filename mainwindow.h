#pragma once

#include <QMainWindow>
#include "extern.h"

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  Ui::MainWindow *ui                = nullptr;

  QStandardItemModel* dataModelChTP = nullptr;
  QStandardItemModel* dataModelRES  = nullptr;
  MyModel* mymodelSelectRES         = nullptr;
  AddEditRES *dialog                = nullptr;

private:
  Map *Map_unit                     = nullptr;
  LoadFromDirectory *LoadWindow     = nullptr;
  CalcParameters *CalcWindow        = nullptr;
  QMenu *Menu_RESAzimutCalc         = nullptr;
  QMenu *Menu_calc                  = nullptr;
  QMenu *Menu_clear                 = nullptr;
  QAction *calcDataWith             = nullptr;    // ... для выделенного РЭС и РЭС в паре с ним
  QAction *calcDataFront            = nullptr;    // ... для выделенного РЭС и РЭС перед ним
  QAction *calcDataAfter            = nullptr;    // ... для выделенного РЭС и РЭС после него
  QAction *calcDataAllWithout       = nullptr;    // ... для всех РЭС, если данные "Азимут" не заполнены
  QAction *calcDataAll              = nullptr;    // ... для всех РЭС

  QAction *clearDataWith            = nullptr;    // ... для выделенного РЭС и РЭС в паре с ним
  QAction *clearDataFront           = nullptr;    // ... для выделенного РЭС и РЭС перед ним
  QAction *clearDataAfter           = nullptr;    // ... для выделенного РЭС и РЭС после него
  QAction *clearDataAll             = nullptr;    // ... для всех РЭС

  QIcon *azimutCalc                 = nullptr;
  QIcon *azimutClear                = nullptr;

  QHeaderView *header               = nullptr;


  QStringList list;
  QStringList GUID_list;
  QStringList *informationIniFile   = nullptr;

  void menu_on_buttonRESAzimutCalc();
  void drawTableRES();
  void drawTableSelectRES();
  void drawTableChTP();
  void drawTableRaschet();
  void loadDataChTPfromCSV(QString, QString);
  void loadDataChTPfromDB(QString);
  void loadDataRES();
  void pereborChastot();

private slots:
  void dialog_tipires();
  void dialog_calcparameters();
  void dialog_addeditres();
  void select_pageChTP();
  void select_pageRES();


  void on_Button_MapShow_clicked();
  void on_Button_LoadRezultatiARM1_clicked();
  void on_TableWidget_Raschet_itemDoubleClicked(QTableWidgetItem *item);

  void on_Button_RaschetDelete_clicked();
  void on_Button_RaschetDeleteAll_clicked();
  void on_Button_RefreshAll_clicked();
  void on_DBTable_RES_doubleClicked(const QModelIndex &index);
  void on_Button_RESEdit_clicked();
  void on_Button_SelectRESEdit_clicked();
  void on_Button_RESInsert_clicked();
  void on_Button_SelectingRESTerritoriyaChastota_clicked();
  void test_slot(const QModelIndex, int, int);
  void on_Button_SelectingRES_clicked();
  void on_Button_SelectRESDelete_clicked();
  void on_Button_SelectRESDeleteAll_clicked();
  void on_Button_RESDelete_clicked();
  void on_Button_RESDeleteAll_clicked();

public slots:
  void refreshTableRaschet(bool);
  int loadRezultatiARM1FromDirectory(const QString&);
  QStringList take_naimenovanieRES();

protected:
  void resizeEvent(QResizeEvent*e);
};
