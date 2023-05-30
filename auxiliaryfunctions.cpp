#include "mainwindow.h"
#include "auxiliaryfunctions.h"


QString afShortDirectoryName(QString LongDirectoryName)
{
  QString result = LongDirectoryName;
  int l = LongDirectoryName.length();
  if (result[l] == "/") result.remove(l,1);
  while (result.indexOf("/") >= 0) {
     result.remove(0, result.indexOf("/") + 1);
  }
  return result;
}

void ZamenaZapyatoy(QString path)
{
   QStringList buffer;
   QFile file (path);
   if (file.open(QIODevice::ReadWrite) && file.exists()) {
     buffer.append(file.readLine());
     if (buffer[0] != "Rewrited\n") {
         while (!file.atEnd()) {
            buffer.append(QTextCodec::codecForName("Windows-1251")->toUnicode(file.readLine()));
         }
         for (int i=0; i <= buffer.size() - 1; i++) {
            buffer[i].replace(buffer[i].indexOf(","),1,".");
         }
         file.resize(0);
         QTextStream in(&file);
         in << "Rewrited\n";
         foreach(QString s, buffer)
         {
            in << s;
         }
     }
     file.close();
   }
}



double afRoundTo(double value, int digit)
{
  double factor = 0, divider = 0;
  factor = 1/qPow(10.0,digit);
  divider = qPow(10.0,digit);
  return round(factor*value)*divider;
}

QString afGeoCoordDesToStr(double GeoCoordDes)
{
  QString sGradusi = "",
          sMinuti = "",
          sSecundi = "";
  double Gradusi = 0,
         Minuti = 0,
         Secundi = 0;

  Gradusi     = trunc(GeoCoordDes);
  GeoCoordDes = (GeoCoordDes - Gradusi) * 60;
  Minuti      = trunc(GeoCoordDes);
  GeoCoordDes = (GeoCoordDes - Minuti) * 60;
  Secundi     = round(GeoCoordDes);

  if (Secundi == 60) {
      Secundi = 0;
      Minuti++;
  }
  if (Minuti == 60) {
      Minuti = 0;
      Gradusi++;
  }
  if (Gradusi >= 360)
      Gradusi = Gradusi - 360;

  sGradusi = QString::number(round(Gradusi));
  if (Minuti < 10) sMinuti = "0" + QString::number(round(Minuti));
  else sMinuti = QString::number(round(Minuti));
  if (Secundi < 10) sSecundi = "0" + QString::number(round(Secundi));
  else sSecundi = QString::number(round(Secundi));

  return QString("%1°%2'%3\"").arg(sGradusi).arg(sMinuti).arg(sSecundi);
}
