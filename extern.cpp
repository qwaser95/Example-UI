#include "extern.h"

//________База данных__________
QSqlDatabase db;
QString currentDB;
QSqlQuery globalQuery;
QString GUIDRaschetaStr_LoadFromDataBase;
QString MaskaNaimenovaniya_LoadFromDataBase;
QString DirektoriyasRezultatami_LoadFromDataBase;

//______Параметры расчёта_______
    //широта долгота
QMap<double, double> LTTochka;
QMap<double, double> RBTochka;
    //широта долгота

double VisotaScheta;
double VisotaPodvesaAbonenta;
double RadiusIzmeneniyaMestopologeniyaBS;
double RadiusZoniObslugivaniya;
double RadiusVliyaniyaAS;
double UvelichenieVisotiPodvesa;
double EIIMAbonenta;
QString OperatorSvyaziRP;
QString TerritoriyaRP;
QString ShifrRChZ;
QString DiapazonChastot;
QString IspolzovanieChTP;
QString UchetZoniObslugivaniya;
QString PolyarizaciyaBS;
int DopustimoeOgranichenie;
int UrovenZapuskaASBS;
int ModelRaschetaAS;
int ProcentVremeniAS;
int ProcentMestAS;
int VisotaEtalonnayaAS;
int NapravlenieAnalizaAS;
bool IzmenenieMestopologeniyaBS;
bool IzmenenieVisotiPodvesaBS;
bool AS_Check;
bool BS_Check;
bool polH;
bool polV;
bool polX;
bool polO;
