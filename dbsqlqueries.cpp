#include "dbsqlqueries.h"
#include "mainwindow.h"
#include "extern.h"

QSqlError DB_SqlConnection(QString driver, QString db_name, QString host, QString user, QString passwd, int port)
{
  int cCount=0;
  QSqlError error = QSqlError();

  currentDB=QString ("Connection_%1").arg(++cCount);
  db=QSqlDatabase::addDatabase(driver);
  db.setDatabaseName(db_name);
  db.setHostName(host);
  db.setPort(port);
  if(!db.open(user, passwd))
  {
      error = db.lastError();
      db = QSqlDatabase();
      QSqlDatabase::removeDatabase(currentDB);
    }
  db=QSqlDatabase::database(currentDB);

  return error;
}

bool DB_AddConnection()
{
  QSqlError err = DB_SqlConnection("QPSQL", "ARM2", "127.0.0.1", "postgres", "", 5432);
  if (err.type() != QSqlError::NoError)
    {
      QMessageBox::warning (nullptr, "Невозможно подключиться к БД", "Произошла ошибка при открытии соединения: "+err.text());
      return false;
    }
  return true;
}

void DB_InsertRaschet(QString GUIDRaschetaStr, QString StandartSvyazi, QString Naimenovanie, QString DirektoriyasRezultatami)
{
  if (!db.isOpen()) return;
  globalQuery.clear();
  QSqlQuery query(db);
  QString SQL_value = QString("INSERT INTO arm2.raschet(guid_rascheta, standart_svyazi, naimenovanie, direktoriya_s_rezultatami)"
                             " VALUES ('%1','%2','%3','%4')").arg (GUIDRaschetaStr).arg (StandartSvyazi)
                                                             .arg (Naimenovanie).arg(DirektoriyasRezultatami);
  query.exec(SQL_value);
  globalQuery = query;

}

void DB_ResetRaschet(QString StandartSvyazi)
{
  if (!db.isOpen()) return;
  globalQuery.clear();
  QSqlQuery query(db);
  QString SQL_value = "";
  SQL_value = "SELECT * FROM arm2.raschet";
  if (StandartSvyazi != "") {
      SQL_value = SQL_value + QString(" WHERE standart_svyazi=").arg(StandartSvyazi);
  }
  SQL_value = SQL_value + " ORDER BY id_rascheta";
  query.exec(SQL_value);
  globalQuery = query;
}

int DB_SelectRaschetByGUIDRaschecta(QString GUIDRaschetaStr, QString StandartSvyazi)
{
  if (!db.isOpen()) return 0;
  globalQuery.clear();
  QSqlQuery query(db);
  QString SQL_value = "";
  if (GUIDRaschetaStr != "") {
      SQL_value = QString("SELECT * FROM arm2.raschet WHERE guid_rascheta = %1").arg(GUIDRaschetaStr);
      if (StandartSvyazi != "")
          SQL_value = SQL_value + QString(" AND standart_svyazi= %1").arg(StandartSvyazi);
      SQL_value = SQL_value + " ORDER BY id_rascheta";
      query.exec(SQL_value);
      globalQuery = query;
      return globalQuery.size();
  }
  else {
      DB_ResetRaschet(StandartSvyazi);
      return 0;
  }
}


void DB_SelectDB()
{
  if (!db.isOpen()) return;
  globalQuery.clear();
  QSqlQuery query(db);
  query.exec("SELECT naimenovanie, guid_rascheta FROM arm2.raschet WHERE standart_svyazi = 'GSM1800' ORDER BY id_rascheta");
  globalQuery = query;
}

void DB_InsertZnachenieStr(QString GUIDRaschetaStr, QString Naimenovanie, QString Znachenie, int Indeks, int Tip)
{
  if (!db.isOpen()) return;
  QSqlQuery query(db);
  if (Indeks != NULL)
  query.exec(QString("INSERT INTO arm2.znacheniestr(guid_rascheta, naimenovanie, znachenie, indeks, tip)"
                    " VALUES ('%1','%2','%3','%4','%5')").arg (GUIDRaschetaStr).arg (Naimenovanie)
                                                         .arg(Znachenie).arg(Indeks).arg(Tip));
  else
  query.exec(QString("INSERT INTO arm2.znacheniestr(guid_rascheta, naimenovanie, znachenie, tip)"
                    " VALUES ('%1','%2','%3','%4')").arg (GUIDRaschetaStr).arg (Naimenovanie)
                                                    .arg(Znachenie).arg(Tip));
}

void DB_DeleteStringInDB(QString GUIDRaschetaStr)
{
  if (!db.isOpen()) return;
  QSqlQuery query(db);
  query.exec(QString("DELETE FROM arm2.chtp WHERE guid_rascheta ='%1'").arg(GUIDRaschetaStr));
  query.exec(QString("DELETE FROM arm2.raschet WHERE guid_rascheta ='%1'").arg(GUIDRaschetaStr));
  query.exec(QString("DELETE FROM arm2.resrascheta WHERE guid_rascheta ='%1'").arg(GUIDRaschetaStr));
  query.exec(QString("DELETE FROM arm2.znacheniestr WHERE guid_rascheta ='%1'").arg(GUIDRaschetaStr));
}


QString DB_pathList(QString GUIDRaschetaStr)
{
   if (!db.isOpen()) return "";
   QSqlQuery query(db);
   query.exec(QString("SELECT direktoriya_s_rezultatami FROM arm2.raschet WHERE guid_rascheta ='%1'").arg(GUIDRaschetaStr));
   while (query.next()) {
     return query.value(0).toString();
   }
}


void DB_InsertChTP(QString GUIDRaschetaStr, QList<QStandardItem*> ChTPstr)
{
  QStringList strList;
  for (int i = 0; i <= ChTPstr.size() - 1; i++) {
       strList.append(ChTPstr[i]->text().replace(ChTPstr[i]->text().indexOf(","),1,"."));
       }
  QSqlQuery query(db);
  query.exec(QString("INSERT INTO arm2.chtp(guid_rascheta, nomer_bs, mesto_razmescheniya, shirota_des, dolgota_des, visota_podvesa, visota_ot_urovnya_morya, tip_azimuta, azimut_osnovnoy, azimut_dopolnitelniy, moschnost_na_vihode_peredatchika, poteri_v_aft, moschnost_na_vhode_antenni, koef_usileniya, chastota_peredatchika, chastota_priemnika, ugol_mesta_dn, shirina_dn_po_azimutu, shirina_dn_po_uglu_mesta, radius_zoni_obslugivaniya, polyarizaciya, klass_izlucheniya, eiim_zayavlennaya)"
                    " VALUES ('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13','%14','%15','%16','%17','%18','%19','%20','%21','%22','%23')")
                              .arg (GUIDRaschetaStr).arg (strList[0]).arg(strList[1])
                              .arg(strList[2]).arg(strList[3]).arg(strList[4])
                              .arg(strList[5]).arg(strList[6]).arg(strList[7])
                              .arg(NULL).arg(strList[9]).arg(strList[10])
                              .arg(strList[11]).arg(strList[12]).arg(strList[13])
                              .arg(strList[14]).arg(strList[15]).arg(strList[16])
                              .arg(strList[17]).arg(strList[18]).arg(strList[20])
                              .arg(strList[19]).arg(strList[21]));
}

void DB_SelectRES()
{
  if (!db.isOpen()) return;
  globalQuery.clear();
  QSqlQuery query(db);
  query.exec("SELECT * FROM arm2.res ORDER BY naimenovanie_res");
  globalQuery = query;
}

void DB_SelectChTP(QString GUIDRaschetaStr)
{
  if (!db.isOpen()) return;
  globalQuery.clear();
  QSqlQuery query(db);
  query.exec(QString("SELECT nomer_bs, shirota_des, dolgota_des, visota_podvesa, tip_azimuta, azimut_osnovnoy, azimut_dopolnitelniy, moschnost_na_vihode_peredatchika, poteri_v_aft, moschnost_na_vhode_antenni, koef_usileniya, chastota_peredatchika, chastota_priemnika, ugol_mesta_dn, shirina_dn_po_azimutu, shirina_dn_po_uglu_mesta, radius_zoni_obslugivaniya, klass_izlucheniya, polyarizaciya, eiim_zayavlennaya, mesto_razmescheniya FROM arm2.chtp WHERE guid_rascheta ='%1'").arg(GUIDRaschetaStr));
  globalQuery = query;
}

void DB_SelectLTRBTochka(QString GUID)
{
  if (!db.isOpen()) return;
  globalQuery.clear();
  QSqlQuery query(db);
  query.exec(QString("SELECT znachenie FROM arm2.znacheniestr WHERE guid_rascheta ='%1' "
                     "AND (naimenovanie ='LTKarti.ShirotaDes' OR naimenovanie ='LTKarti.DolgotaDes' "
                     "OR naimenovanie ='RBKarti.ShirotaDes' OR naimenovanie ='RBKarti.DolgotaDes')").arg(GUID));
  globalQuery = query;
}


void DB_SelectOtobranyeRES(QString GUID)
{
  if (!db.isOpen()) return;
  globalQuery.clear();
  QSqlQuery query(db);
  query.exec(QString("SELECT naimenovanie_res, naimenovanie_tipa_res, tip_azimuta, azimut_osnovnoy, azimut_dopolnitelny, chastota, oslablenie_sf, tip_ucheta_dop_res, radius_dop_res, porog1, porog2, porog3, polyarizaciya FROM arm2.resrascheta WHERE guidrascheta = '%1'").arg(GUID));
  globalQuery = query;
}

void DB_SelectTipiRES()
{
  if (!db.isOpen()) return;
  globalQuery.clear();
  QSqlQuery query(db);
  query.exec("SELECT * FROM arm2.tipires");
  globalQuery = query;
}

void DB_InsertRESRascheta(QStringList listRES, QStringList listTipRES, QString GUID)
{
  if (!db.isOpen()) return;
  if (listRES[5] == "0") listRES[5] = "null";
  else listRES[5] = "'" + listRES[5] + "'";
  globalQuery.clear();
  QSqlQuery query(db);
  query.exec(QString("INSERT INTO arm2.resrascheta(guidrascheta, id_osnovnogo_dannogo, naimenovanie_res, naimenovanie_tipa_res, shirota_des, "
                     "dolgota_des, visota_nasipi, tip_azimuta, azimut_osnovnoy, azimut_dopolnitelniy, tip_ucheta_dop_res, radius_dop_res, "
                     "porog1, porog2, porog3, visota_podvesa, visota_ot_urovnya_morya, poteri_v_aft, koef_usileniya, uroven_bldn, "
                     "shirina_dn_po_azimutu, shirina_dn_po_uglu_mesta, polyarizaciya, chastota, oslablenie_sf) "
                     "VALUES ('%1', '%2', '%3', '%4', '%5', '%6', %7, '%8', '%9', '%10', '%11', '%12', '%13', '%14', '%15', '%16', '%17', '%18', "
                             "'%19', '%20', '%21', '%22', '%23', '%24', '%25')")
                             .arg(GUID).arg(listRES[0]).arg(listRES[1]).arg(listRES[2]).arg(listRES[3]).arg(listRES[4]).arg(listRES[5])
                             .arg(listRES[6]).arg(listRES[7]).arg(listRES[8]).arg(listRES[9]).arg(listRES[10]).arg(listRES[11]).arg(listRES[12])
                             .arg(listRES[13]).arg(VisotaPodvesaAbonenta).arg(NULL).arg(listTipRES[2]).arg(listTipRES[3]).arg(listTipRES[4]).arg(listTipRES[5])
                             .arg(listTipRES[6]).arg(listRES[14]).arg(listRES[15]).arg(listRES[16]));
}


void DB_SelectRES(QString naimenovanie)
{
  if (!db.isOpen()) return;
  globalQuery.clear();
  QSqlQuery query(db);
  query.exec(QString("SELECT idres, naimenovanie_res, naimenovanie_tipa_res, shirota_des, dolgota_des, visota_nasipi, tip_azimuta, azimut_osnovnoy, azimut_dopolnitelniy, tip_ucheta_dop_res, radius_dop_res, porog1, porog2, porog3, polyarizaciya, chastota, oslablenie_sf  FROM arm2.res WHERE naimenovanie_res='%1'").arg(naimenovanie));
  globalQuery = query;
}

void DB_TipRES(QString naimenovanie)
{
  if (!db.isOpen()) return;
  QSqlQuery query(db);
  query.exec(QString("DELETE FROM arm2.tipires WHERE naimenovanie_tipa_res = '%1'").arg(naimenovanie));
}



void DB_InsertTipRES(QStringList dataRES)
{
  if (!db.isOpen()) return;
  QSqlQuery query(db);
  query.exec(QString("INSERT INTO arm2.tipires(id_tipa_res, naimenovanie_tipa_res, poteri_v_aft, koef_usileniya, uroven_bldn, shirina_dn_po_azimutu, shirina_dn_po_uglu_mesta) "
                     "VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7')")
                     .arg(dataRES[0]).arg(dataRES[1]).arg(dataRES[2])
                     .arg(dataRES[3]).arg(dataRES[4]).arg(dataRES[5])
                     .arg(dataRES[6]));
}
void DB_SelectExtern(QString GUID)
{
  if (!db.isOpen()) return;
  QSqlQuery query(db);
  query.exec(QString("SELECT znachenie FROM arm2.znacheniestr WHERE guid_rascheta ='%1' AND naimenovanie ='DiapazoniChastot'").arg(GUID));
  query.next();
  DiapazonChastot = query.value(0).toString();
  query.clear();
  query.exec(QString("SELECT znachenie FROM arm2.znacheniestr WHERE guid_rascheta ='%1' AND naimenovanie ='IzmenenieMestopologeniyaBS'").arg(GUID));
  query.next();
  IzmenenieMestopologeniyaBS = query.value(0).toBool();
  query.clear();
  query.exec(QString("SELECT znachenie FROM arm2.znacheniestr WHERE guid_rascheta ='%1' AND naimenovanie ='RadiusIzmeneniyaMestopologeniyaBS'").arg(GUID));
  query.next();
  RadiusIzmeneniyaMestopologeniyaBS = query.value(0).toDouble();
  query.clear();
  query.exec(QString("SELECT znachenie FROM arm2.znacheniestr WHERE guid_rascheta ='%1' AND naimenovanie ='IzmenenieVisotiPodvesaBS'").arg(GUID));
  query.next();
  IzmenenieVisotiPodvesaBS = query.value(0).toBool();
  query.clear();
  query.exec(QString("SELECT znachenie FROM arm2.znacheniestr WHERE guid_rascheta ='%1' AND naimenovanie ='UvelichenieVisotiPodvesa'").arg(GUID));
  query.next();
  UvelichenieVisotiPodvesa = query.value(0).toDouble();
  query.clear();
  query.exec(QString("SELECT znachenie FROM arm2.znacheniestr WHERE guid_rascheta ='%1' AND naimenovanie ='IspolzovanieChTP'").arg(GUID));
  query.next();
  IspolzovanieChTP = query.value(0).toString();
  query.clear();
  query.exec(QString("SELECT znachenie FROM arm2.znacheniestr WHERE guid_rascheta ='%1' AND naimenovanie ='RadiusVliyaniyaAS'").arg(GUID));
  query.next();
  RadiusVliyaniyaAS = query.value(0).toDouble();
  query.clear();
  query.exec(QString("SELECT znachenie FROM arm2.znacheniestr WHERE guid_rascheta ='%1' AND naimenovanie ='VisotaPodvesaAbonenta'").arg(GUID));
  query.next();
  VisotaPodvesaAbonenta = query.value(0).toDouble();
  query.clear();
  query.exec(QString("SELECT znachenie FROM arm2.znacheniestr WHERE guid_rascheta ='%1' AND naimenovanie ='EIIMAbonenta'").arg(GUID));
  query.next();
  EIIMAbonenta = query.value(0).toDouble();
  query.clear();
  query.exec(QString("SELECT znachenie FROM arm2.znacheniestr WHERE guid_rascheta ='%1' AND naimenovanie ='UrovenZapuskaASBS'").arg(GUID));
  query.next();
  UrovenZapuskaASBS = query.value(0).toInt();
  query.clear();
  query.exec(QString("SELECT znachenie FROM arm2.znacheniestr WHERE guid_rascheta ='%1' AND naimenovanie ='ModelRaschetaAS'").arg(GUID));
  query.next();
  ModelRaschetaAS = query.value(0).toInt();
  query.clear();
  query.exec(QString("SELECT znachenie FROM arm2.znacheniestr WHERE guid_rascheta ='%1' AND naimenovanie ='ProcentVremeniAS'").arg(GUID));
  query.next();
  ProcentVremeniAS = query.value(0).toInt();
  query.clear();
  query.exec(QString("SELECT znachenie FROM arm2.znacheniestr WHERE guid_rascheta ='%1' AND naimenovanie ='ProcentMestAS'").arg(GUID));
  query.next();
  ProcentMestAS = query.value(0).toInt();
  query.clear();
  query.exec(QString("SELECT znachenie FROM arm2.znacheniestr WHERE guid_rascheta ='%1' AND naimenovanie ='VisotaEtalonnayaAS'").arg(GUID));
  query.next();
  VisotaEtalonnayaAS = query.value(0).toInt();
  query.clear();
  query.exec(QString("SELECT znachenie FROM arm2.znacheniestr WHERE guid_rascheta ='%1' AND naimenovanie ='NapravlenieAnalizaAS'").arg(GUID));
  query.next();
  NapravlenieAnalizaAS = query.value(0).toInt();
  query.clear();
  query.exec(QString("SELECT znachenie FROM arm2.znacheniestr WHERE guid_rascheta ='%1' AND naimenovanie ='UchetZoniObslugivaniya'").arg(GUID));
  query.next();
  UchetZoniObslugivaniya = query.value(0).toString();
  query.clear();
  query.exec(QString("SELECT znachenie FROM arm2.znacheniestr WHERE guid_rascheta ='%1' AND naimenovanie ='RaschetBS'").arg(GUID));
  query.next();
  BS_Check = query.value(0).toBool();
  query.clear();
  query.exec(QString("SELECT znachenie FROM arm2.znacheniestr WHERE guid_rascheta ='%1' AND naimenovanie ='PolyarizaciyaBS'").arg(GUID));
  query.next();
  PolyarizaciyaBS = query.value(0).toString();
  query.clear();
  query.exec(QString("SELECT znachenie FROM arm2.znacheniestr WHERE guid_rascheta ='%1' AND naimenovanie ='UkazannayaPolyarizaciyaBS'").arg(GUID));
  query.next();
  QString UkazannayaPolyarizaciyaBS = query.value(0).toString();
  if (UkazannayaPolyarizaciyaBS.indexOf("V")>=0)
    polV = true;
  if (UkazannayaPolyarizaciyaBS.indexOf("O")>=0)
    polO = true;
  if (UkazannayaPolyarizaciyaBS.indexOf("X")>=0)
    polX = true;
  if (UkazannayaPolyarizaciyaBS.indexOf("H")>=0)
    polH = true;
  query.clear();
  query.exec(QString("SELECT znachenie FROM arm2.znacheniestr WHERE guid_rascheta ='%1' AND naimenovanie ='RaschetAS'").arg(GUID));
  query.next();
  AS_Check = query.value(0).toBool();
  query.clear();
}

void DB_TakeIdTipRES()
{
  if (!db.isOpen()) return;
  globalQuery.clear();
  QSqlQuery query(db);
  query.exec(QString("SELECT max(id_tipa_res) FROM arm2.tipires"));
  globalQuery = query;
}

void DB_SelectAllFromTipiRes(QString naimenovanie_tipa_res)
{
  if (!db.isOpen()) return;
  globalQuery.clear();
  QSqlQuery query(db);
  query.exec(QString("SELECT * FROM arm2.tipires WHERE naimenovanie_tipa_res = '%1'").arg(naimenovanie_tipa_res));
  globalQuery = query;
}

void DB_EditRES(QString row, QStringList dataRES)
{
  if (!db.isOpen()) return;
  QSqlQuery query(db);
  query.exec(QString("UPDATE arm2.res SET naimenovanie_res = '%2', naimenovanie_tipa_res = '%3', mesto_razmescheniya = '%4', "
                     "shirota_des = '%6', dolgota_des = '%7', tip_azimuta = '%8', azimut_osnovnoy = '%9', azimut_dopolnitelniy = '%10', "
                     "chastota = '%11', oslablenie_sf = '%12', tip_ucheta_dop_res = '%13', radius_dop_res = '%14', "
                     "porog1 = '%15', porog2 = '%16', porog3 = '%17', polyarizaciya = '%18' WHERE idres = '%1'")
                     .arg(row).arg(dataRES[0]).arg(dataRES[1]).arg(dataRES[2]).arg(dataRES[4]).arg(dataRES[6])
                     .arg(dataRES[7]).arg(dataRES[8]).arg(dataRES[9]).arg(dataRES[10]).arg(dataRES[11]).arg(dataRES[12])
                     .arg(dataRES[13]).arg(dataRES[14]).arg(dataRES[15]).arg(dataRES[16]).arg(dataRES[17]));
}

void DB_AddRES(QStringList dataRES)
{
  if (!db.isOpen()) return;
  QSqlQuery query(db);
  if (dataRES[9] != "0") {
   query.exec(QString("INSERT INTO arm2.res(naimenovanie_res, naimenovanie_tipa_res, mesto_razmescheniya, shirota_des, dolgota_des, tip_azimuta, azimut_osnovnoy, azimut_dopolnitelniy, chastota, oslablenie_sf, tip_ucheta_dop_res, radius_dop_res, porog1, porog2, porog3, polyarizaciya)"
                      " VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10', '%11', '%12', '%13', '%14', '%15', '%16')")
                       .arg(dataRES[0]).arg(dataRES[1]).arg(dataRES[2]).arg(dataRES[4]).arg(dataRES[6]).arg(dataRES[7]).arg(dataRES[8])
                       .arg(dataRES[9]).arg(dataRES[10]).arg(dataRES[11]).arg(dataRES[12]).arg(dataRES[13]).arg(dataRES[14]).arg(dataRES[15])
                       .arg(dataRES[16]).arg(dataRES[17]));
  }
  else {
    query.exec(QString("INSERT INTO arm2.res(naimenovanie_res, naimenovanie_tipa_res, mesto_razmescheniya, shirota_des, dolgota_des, tip_azimuta, azimut_osnovnoy, azimut_dopolnitelniy, chastota, oslablenie_sf, tip_ucheta_dop_res, radius_dop_res, porog1, porog2, porog3, polyarizaciya)"
                      " VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', null, '%8', '%9', '%10', '%11', '%12', '%13', '%14', '%15')")
                       .arg(dataRES[0]).arg(dataRES[1]).arg(dataRES[2]).arg(dataRES[4]).arg(dataRES[6]).arg(dataRES[7]).arg(dataRES[8])
                       .arg(dataRES[10]).arg(dataRES[11]).arg(dataRES[12]).arg(dataRES[13]).arg(dataRES[14]).arg(dataRES[15])
                       .arg(dataRES[16]).arg(dataRES[17]));
  }
}

int DB_Select_idres(QString naimenovanie_RES)
{
  if (!db.isOpen()) return 0;
  QSqlQuery query(db);
  query.exec(QString("SELECT idres FROM arm2.res WHERE naimenovanie_res = '%1'").arg(naimenovanie_RES));
  query.next();
  return query.value(0).toInt();
}

void DB_DeleteRES(QString naimenovanie_RES, bool all)
{
  if (!db.isOpen()) return;
  QSqlQuery query(db);
  if (!all) query.exec(QString("DELETE FROM arm2.res WHERE naimenovanie_res = '%1'").arg(naimenovanie_RES));
  else query.exec("DELETE FROM arm2.res");
}

void DB_UpdateZnacheniestr()
{
  if (!db.isOpen()) return;
  QString UkazannayaPolyarizaciyaBS;
  QSqlQuery query(db);
  query.exec(QString("UPDATE arm2.znacheniestr SET znachenie = '%2' WHERE guid_rascheta ='%1' AND naimenovanie ='DiapazoniChastot'").arg(GUIDRaschetaStr_LoadFromDataBase).arg(DiapazonChastot));
  query.exec(QString("UPDATE arm2.znacheniestr SET znachenie = '%2' WHERE guid_rascheta ='%1' AND naimenovanie ='IzmenenieMestopologeniyaBS'").arg(GUIDRaschetaStr_LoadFromDataBase).arg(IzmenenieMestopologeniyaBS));
  query.exec(QString("UPDATE arm2.znacheniestr SET znachenie = '%2' WHERE guid_rascheta ='%1' AND naimenovanie ='RadiusIzmeneniyaMestopologeniyaBS'").arg(GUIDRaschetaStr_LoadFromDataBase).arg(RadiusIzmeneniyaMestopologeniyaBS));
  query.exec(QString("UPDATE arm2.znacheniestr SET znachenie = '%2' WHERE guid_rascheta ='%1' AND naimenovanie ='IzmenenieVisotiPodvesaBS'").arg(GUIDRaschetaStr_LoadFromDataBase).arg(IzmenenieVisotiPodvesaBS));
  query.exec(QString("UPDATE arm2.znacheniestr SET znachenie = '%2' WHERE guid_rascheta ='%1' AND naimenovanie ='UvelichenieVisotiPodvesa'").arg(GUIDRaschetaStr_LoadFromDataBase).arg(UvelichenieVisotiPodvesa));
  query.exec(QString("UPDATE arm2.znacheniestr SET znachenie = '%2' WHERE guid_rascheta ='%1' AND naimenovanie ='IspolzovanieChTP'").arg(GUIDRaschetaStr_LoadFromDataBase).arg(IspolzovanieChTP));
  query.exec(QString("UPDATE arm2.znacheniestr SET znachenie = '%2' WHERE guid_rascheta ='%1' AND naimenovanie ='RadiusVliyaniyaAS'").arg(GUIDRaschetaStr_LoadFromDataBase).arg(RadiusVliyaniyaAS));
  query.exec(QString("UPDATE arm2.znacheniestr SET znachenie = '%2' WHERE guid_rascheta ='%1' AND naimenovanie ='VisotaPodvesaAbonenta'").arg(GUIDRaschetaStr_LoadFromDataBase).arg(VisotaPodvesaAbonenta));
  query.exec(QString("UPDATE arm2.znacheniestr SET znachenie = '%2' WHERE guid_rascheta ='%1' AND naimenovanie ='EIIMAbonenta'").arg(GUIDRaschetaStr_LoadFromDataBase).arg(EIIMAbonenta));
  query.exec(QString("UPDATE arm2.znacheniestr SET znachenie = '%2' WHERE guid_rascheta ='%1' AND naimenovanie ='UrovenZapuskaASBS'").arg(GUIDRaschetaStr_LoadFromDataBase).arg(UrovenZapuskaASBS));
  query.exec(QString("UPDATE arm2.znacheniestr SET znachenie = '%2' WHERE guid_rascheta ='%1' AND naimenovanie ='ModelRaschetaAS'").arg(GUIDRaschetaStr_LoadFromDataBase).arg(ModelRaschetaAS));
  query.exec(QString("UPDATE arm2.znacheniestr SET znachenie = '%2' WHERE guid_rascheta ='%1' AND naimenovanie ='ProcentVremeniAS'").arg(GUIDRaschetaStr_LoadFromDataBase).arg(ProcentVremeniAS));
  query.exec(QString("UPDATE arm2.znacheniestr SET znachenie = '%2' WHERE guid_rascheta ='%1' AND naimenovanie ='ProcentMestAS'").arg(GUIDRaschetaStr_LoadFromDataBase).arg(ProcentMestAS));
  query.exec(QString("UPDATE arm2.znacheniestr SET znachenie = '%2' WHERE guid_rascheta ='%1' AND naimenovanie ='VisotaEtalonnayaAS'").arg(GUIDRaschetaStr_LoadFromDataBase).arg(VisotaEtalonnayaAS));
  query.exec(QString("UPDATE arm2.znacheniestr SET znachenie = '%2' WHERE guid_rascheta ='%1' AND naimenovanie ='NapravlenieAnalizaAS'").arg(GUIDRaschetaStr_LoadFromDataBase).arg(NapravlenieAnalizaAS));
  query.exec(QString("UPDATE arm2.znacheniestr SET znachenie = '%2' WHERE guid_rascheta ='%1' AND naimenovanie ='UchetZoniObslugivaniya'").arg(GUIDRaschetaStr_LoadFromDataBase).arg(UchetZoniObslugivaniya));
  query.exec(QString("UPDATE arm2.znacheniestr SET znachenie = '%2' WHERE guid_rascheta ='%1' AND naimenovanie ='RaschetBS'").arg(GUIDRaschetaStr_LoadFromDataBase).arg(BS_Check));
  query.exec(QString("UPDATE arm2.znacheniestr SET znachenie = '%2' WHERE guid_rascheta ='%1' AND naimenovanie ='PolyarizaciyaBS'").arg(GUIDRaschetaStr_LoadFromDataBase).arg(PolyarizaciyaBS));
  if (polH) UkazannayaPolyarizaciyaBS.append("H");
  if (polO) UkazannayaPolyarizaciyaBS.append("O");
  if (polV) UkazannayaPolyarizaciyaBS.append("V");
  if (polX) UkazannayaPolyarizaciyaBS.append("X");
  query.exec(QString("UPDATE arm2.znacheniestr SET znachenie = '%2' WHERE guid_rascheta ='%1' AND naimenovanie ='UkazannayaPolyarizaciyaBS'").arg(GUIDRaschetaStr_LoadFromDataBase).arg(UkazannayaPolyarizaciyaBS));
  query.exec(QString("UPDATE arm2.znacheniestr SET znachenie = '%2' WHERE guid_rascheta ='%1' AND naimenovanie ='RaschetAS'").arg(GUIDRaschetaStr_LoadFromDataBase).arg(AS_Check));
}

void DB_SelectRESrascheta(QString GUID)
{
  if (!db.isOpen()) return;
  globalQuery.clear();
  QSqlQuery query(db);
  query.exec(QString("SELECT naimenovanie_res, naimenovanie_tipa_res, tip_azimuta, azimut_osnovnoy, azimut_dopolnitelniy, chastota, oslablenie_sf, tip_ucheta_dop_res, radius_dop_res, porog1, porog2, porog3, polyarizaciya  FROM arm2.resrascheta WHERE guidrascheta = '%1'").arg(GUID));
  globalQuery = query;
}

void DB_DeleteAllRESrascheta(QString GUID)
{
  if (!db.isOpen()) return;
  QSqlQuery query(db);
  query.exec(QString("DELETE FROM arm2.resrascheta WHERE guidrascheta = '%1'").arg(GUID));
}

void DB_DeleteRESrascheta(QString GUID, QString naimenovanie)
{
  if (!db.isOpen()) return;
  QSqlQuery query(db);
  query.exec(QString("DELETE FROM arm2.resrascheta WHERE guidrascheta = '%1' AND naimenovanie_res = '%2'").arg(GUID).arg(naimenovanie));
}
