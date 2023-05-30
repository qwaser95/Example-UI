#pragma once

#include <QTextCodec>
#include <QWidget>
#include <QtSql>
#include <QSqlQuery>
#include <QMenu>
#include <QTextCodec>
#include <QHeaderView>
#include <QAbstractTableModel>
#include <QMessageBox>
#include <QResizeEvent>
#include <QDebug>
#include <qheaderview.h>
#include <QStandardItemModel>
#include <QUuid>
#include <QSettings>
#include <QStyle>
#include <QDesktopWidget>
#include <QTableWidgetItem>

#include "tipires.h"
#include "auxiliaryfunctions.h"
#include "calcparameters.h"
#include "addeditres.h"
#include "map.h"
#include "loadfromdirectory.h"
#include "stringlistmodel.h"
#include "RbTableHeaderView.h"
#include "mymodel.h"
#include "checkboxdelegate.h"
#include "dbsqlqueries.h"

// База данных
extern QSqlDatabase db;
extern QString currentDB;
extern QSqlQuery globalQuery;
extern QString GUIDRaschetaStr_LoadFromDataBase;
extern QString MaskaNaimenovaniya_LoadFromDataBase;
extern QString DirektoriyasRezultatami_LoadFromDataBase;

// Параметры расчёта
extern QMap<double, double> LTTochka;
extern QMap<double, double> RBTochka;
extern double VisotaScheta;
extern double VisotaPodvesaAbonenta;
extern double RadiusIzmeneniyaMestopologeniyaBS;
extern double RadiusZoniObslugivaniya;
extern double RadiusVliyaniyaAS;
extern double UvelichenieVisotiPodvesa;
extern double EIIMAbonenta;
extern QString OperatorSvyaziRP;
extern QString TerritoriyaRP;
extern QString ShifrRChZ;
extern QString DiapazonChastot;
extern QString IspolzovanieChTP;
extern QString UchetZoniObslugivaniya;
extern QString PolyarizaciyaBS;
extern int DopustimoeOgranichenie;
extern int UrovenZapuskaASBS;
extern int ModelRaschetaAS;
extern int ProcentVremeniAS;
extern int ProcentMestAS;
extern int VisotaEtalonnayaAS;
extern int NapravlenieAnalizaAS;
extern bool IzmenenieMestopologeniyaBS;
extern bool IzmenenieVisotiPodvesaBS;
extern bool AS_Check;
extern bool BS_Check;
extern bool polH;
extern bool polV;
extern bool polX;
extern bool polO;
