#pragma once

#include <QtSql>
#include <QSqlQuery>
#include <QString>
#include <QMessageBox>
#include <QStandardItem>


QSqlError DB_SqlConnection(QString, QString, QString, QString, QString, int);
bool DB_AddConnection();
void DB_InsertRaschet(QString, QString, QString, QString);
void DB_ResetRaschet(QString);
int DB_SelectRaschetByGUIDRaschecta(QString, QString);
void DB_InsertZnachenieStr(QString, QString, QString, int, int);
void DB_InsertChTP(QString, QList<QStandardItem*>);
void DB_InsertRESRascheta(QStringList, QStringList, QString);
void DB_InsertTipRES(QStringList);
void DB_SelectDB();
void DB_SelectRES();
void DB_SelectRES(QString);
void DB_SelectRESrascheta(QString);
void DB_SelectChTP(QString);
void DB_SelectLTRBTochka(QString);
void DB_SelectOtobranyeRES(QString);
void DB_SelectTipiRES();
void DB_SelectExtern(QString);
void DB_SelectAllFromTipiRes(QString);
void DB_TakeIdTipRES();
void DB_DeleteStringInDB(QString);
void DB_TipRES(QString);
QString DB_pathList(QString);
void DB_EditRES(QString, QStringList);
void DB_AddRES(QStringList);
int  DB_Select_idres(QString);
void DB_DeleteRES(QString, bool);
void DB_UpdateZnacheniestr();
void DB_DeleteAllRESrascheta(QString);
void DB_DeleteRESrascheta(QString, QString);
