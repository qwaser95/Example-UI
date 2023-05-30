#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ltrbtochkidata.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  if(DB_AddConnection()) qDebug() << "Подключение к базе данных - успешно";

  Map_unit = new Map(this);
  Map_unit->hide();
  Map_unit->setAutoFillBackground(true);

  ui->PageControl->tabBar()->setVisible(false);

  // СОЕДИНЕНИЕ СИГНАЛОВ СО СЛОТАМИ (вызов диалоговых окон)

  connect(ui->Button_TipiRES,        SIGNAL(clicked()),
         this,                       SLOT(dialog_tipires())) ;

  connect(ui->Button_Onward,         SIGNAL(clicked()),
         this,                       SLOT(dialog_calcparameters())) ;

  connect(ui->Button_SelectRESEdit,  SIGNAL(clicked()),
         this,                       SLOT(dialog_addeditres())) ;

  connect(ui->Button_ChTPPage,       SIGNAL(clicked()),
         this,                       SLOT(select_pageChTP())) ;

  connect(ui->Button_RESPage,        SIGNAL(clicked()),
         this,                       SLOT(select_pageRES())) ;




  DB_SelectDB();

  menu_on_buttonRESAzimutCalc();
  drawTableRES();
  drawTableSelectRES();
  drawTableChTP();
  drawTableRaschet();
  loadDataRES();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::menu_on_buttonRESAzimutCalc()
{
  azimutCalc = new QIcon(":/icons/Icons/ButtonIcons/Azimut Calc.ico");
  azimutClear = new QIcon(":/icons/Icons/ButtonIcons/Azimut Clear.ico");

  calcDataWith = new QAction(*azimutCalc,"... для выделенного РЭС и РЭС в паре с ним", this);
  calcDataFront = new QAction(*azimutCalc,"... для выделенного РЭС и РЭС перед ним", this);
  calcDataAfter = new QAction(*azimutCalc,"... для выделенного РЭС и РЭС после него", this);
  calcDataAll = new QAction(*azimutCalc,".. для всех РЭС, если данные 'Азимут' не заполнены", this);
  calcDataAllWithout = new QAction(*azimutCalc,"... для всех РЭС", this);

  clearDataWith = new QAction(*azimutClear,"... для выделенного РЭС и РЭС в паре с ним", this);
  clearDataFront = new QAction(*azimutClear,"... для выделенного РЭС и РЭС перед ним", this);
  clearDataAfter = new QAction(*azimutClear,"... для выделенного РЭС и РЭС после него", this);
  clearDataAll = new QAction(*azimutClear,"... для всех РЭС", this);

  Menu_RESAzimutCalc = new QMenu(this);
  Menu_calc = new QMenu("Рассчитать данные 'Азимут' ...", this);
  Menu_calc->setIcon(*azimutCalc);
  Menu_clear = new QMenu("Очистить данные 'Азимут' ...", this);
  Menu_clear->setIcon(*azimutClear);

  Menu_calc->addAction(calcDataWith);
  Menu_calc->addAction(calcDataFront);
  Menu_calc->addAction(calcDataAfter);
  Menu_calc->addSeparator();
  Menu_calc->addAction(calcDataAllWithout);
  Menu_calc->addAction(calcDataAll);

  Menu_clear->addAction(clearDataWith);
  Menu_clear->addAction(clearDataFront);
  Menu_clear->addAction(clearDataAfter);
  Menu_clear->addSeparator();
  Menu_clear->addAction(clearDataAll);

  Menu_RESAzimutCalc->addMenu(Menu_calc);
  Menu_RESAzimutCalc->addMenu(Menu_clear);

  ui->Button_RESAzimutCalc->setMenu(Menu_RESAzimutCalc);
}

void MainWindow::drawTableRES()
{
  RbTableHeaderView* hHead = new RbTableHeaderView(Qt::Horizontal,3,18);
  QAbstractItemModel* hModel = hHead->model();
  dataModelRES = new QStandardItemModel;


  hHead->setSpan(0,0,3,0);
  hHead->setSpan(0,1,3,0);
  hHead->setSpan(0,2,0,4);
  hHead->setSpan(1,2,0,2);
  hHead->setSpan(1,4,0,2);
  hHead->setSpan(0,6,0,3);
  hHead->setSpan(1,6,2,0);
  hHead->setSpan(0,6,0,3);
  hHead->setSpan(0,9,2,0);
  hHead->setSpan(0,10,3,0);
  hHead->setSpan(0,11,0,2);
  hHead->setSpan(1,11,2,0);
  hHead->setSpan(0,13,2,0);
  hHead->setSpan(0,14,2,0);
  hHead->setSpan(0,15,2,0);
  hHead->setSpan(0,16,3,0);
  hHead->setSpan(0,17,2,0);
  hModel->setData(hModel->index(0,0),QString("Наименование\nРЭС"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,1),QString("Тип РЭС"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,2),QString("Координаты"),Qt::DisplayRole);
  hModel->setData(hModel->index(1,2),QString("Широта"),Qt::DisplayRole);
  hModel->setData(hModel->index(1,4),QString("Долгота"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,2),QString("стр, ° ' \""),Qt::DisplayRole);
  hModel->setData(hModel->index(2,3),QString("дес, °"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,4),QString("стр, ° ' \""),Qt::DisplayRole);
  hModel->setData(hModel->index(2,5),QString("дес, °"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,5),QString("дес, °"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,6),QString("Азимут"),Qt::DisplayRole);
  hModel->setData(hModel->index(1,6),QString("Тип"),Qt::DisplayRole);
  hModel->setData(hModel->index(1,7),QString("левый"),Qt::DisplayRole);
  hModel->setData(hModel->index(1,8),QString("правый"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,7),QString("°"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,8),QString("°"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,9),QString("Частота"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,9),QString("МГц"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,10),QString("Данные\n«SF»"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,11),QString("Доп. РЭС"),Qt::DisplayRole);
  hModel->setData(hModel->index(1,11),QString("Тип учета"),Qt::DisplayRole);
  hModel->setData(hModel->index(1,12),QString("Радиус"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,12),QString("км"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,13),QString("Порог «1»\n(блок-я)"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,14),QString("Порог «2»\n(интерм-и)"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,15),QString("Порог «3»\n(шум)"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,13),QString("дБВт"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,14),QString("дБВт"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,15),QString("дБВт"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,16),QString("Поляризация"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,17),QString("Место размещения"),Qt::DisplayRole);


  hHead->setRowHeight(0,25);
  hHead->setRowHeight(1,25);
  hHead->setRowHeight(2,25);


  hHead->setColumnWidth(1,80);
  hHead->setColumnWidth(2,80);
  hHead->setColumnWidth(3,80);
  hHead->setColumnWidth(4,80);
  hHead->setColumnWidth(5,80);
  hHead->setColumnWidth(6,80);
  hHead->setColumnWidth(7,60);
  hHead->setColumnWidth(8,60);
  hHead->setColumnWidth(9,70);
  hHead->setColumnWidth(10,70);
  hHead->setColumnWidth(11,100);
  hHead->setColumnWidth(12,60);
  hHead->setColumnWidth(13,70);
  hHead->setColumnWidth(14,70);
  hHead->setColumnWidth(15,70);
  hHead->setColumnWidth(16,90);
  hHead->setColumnWidth(17,160);

  hHead->setStretchLastSection(true);

  hHead->setCellBackgroundColor(hModel->index(0,0),0xcfcfcf);
  hHead->setCellBackgroundColor(hModel->index(0,1),0xcfcfcf);


  ui->DBTable_RES->setModel(dataModelRES);
  ui->DBTable_RES->setHorizontalHeader(hHead);
  ui->DBTable_RES->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  ui->DBTable_RES->verticalHeader()->setDefaultSectionSize(20);
  ui->DBTable_RES->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
}

void MainWindow::drawTableSelectRES()
{
  RbTableHeaderView* hHead = new RbTableHeaderView(Qt::Horizontal,3,14);
  QAbstractItemModel* hModel = hHead->model();
  mymodelSelectRES = new MyModel(nullptr);

  connect(mymodelSelectRES, SIGNAL(rowsInserted(const QModelIndex, int, int)),
          this,             SLOT(test_slot(const QModelIndex, int, int)), Qt::DirectConnection);

  hHead->setSpan(0,0,3,0);
  hHead->setSpan(0,1,3,0);
  hHead->setSpan(0,2,3,0);
  hHead->setSpan(0,3,0,3);
  hHead->setSpan(1,3,2,0);
  hHead->setSpan(0,3,0,3);
  hHead->setSpan(0,6,2,0);
  hHead->setSpan(0,7,3,0);
  hHead->setSpan(0,8,0,2);
  hHead->setSpan(1,8,2,0);
  hHead->setSpan(0,10,2,0);
  hHead->setSpan(0,11,2,0);
  hHead->setSpan(0,12,2,0);
  hHead->setSpan(0,13,3,0);
  hModel->setData(hModel->index(0,0),QString(""),Qt::DisplayRole);
  hModel->setData(hModel->index(0,1),QString("Наименование\nРЭС"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,2),QString("Тип РЭС"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,3),QString("Азимут"),Qt::DisplayRole);
  hModel->setData(hModel->index(1,3),QString("Тип"),Qt::DisplayRole);
  hModel->setData(hModel->index(1,4),QString("левый"),Qt::DisplayRole);
  hModel->setData(hModel->index(1,5),QString("правый"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,4),QString("°"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,5),QString("°"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,6),QString("Частота"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,6),QString("МГц"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,7),QString("Данные\n«SF»"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,8),QString("Доп. РЭС"),Qt::DisplayRole);
  hModel->setData(hModel->index(1,8),QString("Тип учета"),Qt::DisplayRole);
  hModel->setData(hModel->index(1,9),QString("Радиус"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,9),QString("км"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,10),QString("Порог «1»\n(блок-я)"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,11),QString("Порог «2»\n(интерм-и)"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,12),QString("Порог «3»\n(шум)"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,10),QString("дБВт"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,11),QString("дБВт"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,12),QString("дБВт"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,13),QString("Поляризация"),Qt::DisplayRole);
  hHead->setStretchLastSection(true);
  hHead->setColumnWidth(0,7);



  ui->DBTable_SelectRES->setModel(mymodelSelectRES);
  ui->DBTable_SelectRES->setHorizontalHeader(hHead);
  ui->DBTable_SelectRES->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  ui->DBTable_SelectRES->verticalHeader()->setDefaultSectionSize(20);
  ui->DBTable_SelectRES->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
  ui->DBTable_SelectRES->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
}

void MainWindow::drawTableChTP()
{
  select_pageRES();

  RbTableHeaderView* hHead = new RbTableHeaderView(Qt::Horizontal,4,23);
  QAbstractItemModel* hModel = hHead->model();
  dataModelChTP = new QStandardItemModel;

  hHead->setSpan(0,0,4,0);
  hHead->setSpan(0,1,2,4);
  hHead->setSpan(2,1,1,2);
  hHead->setSpan(2,3,1,2);
  hHead->setSpan(0,5,3,1);
  hHead->setSpan(0,6,2,3);
  hHead->setSpan(2,6,2,1);
  hHead->setSpan(0,9,3,1);
  hHead->setSpan(0,10,3,1);
  hHead->setSpan(0,11,3,1);
  hHead->setSpan(0,12,3,1);
  hHead->setSpan(0,13,2,2);
  hHead->setSpan(0,15,1,3);
  hHead->setSpan(1,15,2,1);
  hHead->setSpan(1,16,1,2);
  hHead->setSpan(0,18,3,1);
  hHead->setSpan(0,19,4,1);
  hHead->setSpan(0,20,4,1);
  hHead->setSpan(0,21,3,1);
  hHead->setSpan(0,22,4,1);
  hModel->setData(hModel->index(0,0),QString("Номер базовой \n станции"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,1),QString("Координаты"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,1),QString("Широта"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,3),QString("Долгота"),Qt::DisplayRole);
  hModel->setData(hModel->index(3,1),QString("стр, ° ' \""),Qt::DisplayRole);
  hModel->setData(hModel->index(3,2),QString("дес, °"),Qt::DisplayRole);
  hModel->setData(hModel->index(3,3),QString("стр, ° ' \""),Qt::DisplayRole);
  hModel->setData(hModel->index(3,4),QString("дес, °"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,5),QString("Высота \n подвеса"),Qt::DisplayRole);
  hModel->setData(hModel->index(3,5),QString("м"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,6),QString("Азимут"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,6),QString("Тип"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,7),QString("левый"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,8),QString("правый"),Qt::DisplayRole);
  hModel->setData(hModel->index(3,7),QString("°"),Qt::DisplayRole);
  hModel->setData(hModel->index(3,8),QString("°"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,9),QString("Мощность на \n выходе \n передатчика"),Qt::DisplayRole);
  hModel->setData(hModel->index(3,9),QString("Вт"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,10),QString("Потери в \nАФТ"),Qt::DisplayRole);
  hModel->setData(hModel->index(3,10),QString("дБ"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,11),QString("Мощность на\n входе\n антенны"),Qt::DisplayRole);
  hModel->setData(hModel->index(3,11),QString("Вт"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,12),QString("Коэффицеиент\n усиления\n антенны"),Qt::DisplayRole);
  hModel->setData(hModel->index(3,12),QString("дБ"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,13),QString("Частота"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,13),QString("передатчика"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,14),QString("приемника"),Qt::DisplayRole);
  hModel->setData(hModel->index(3,13),QString("МГц"),Qt::DisplayRole);
  hModel->setData(hModel->index(3,14),QString("МГц"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,15),QString("Диаграмма направленности"),Qt::DisplayRole);
  hModel->setData(hModel->index(1,15),QString("Угол \n места"),Qt::DisplayRole);
  hModel->setData(hModel->index(3,15),QString("°"),Qt::DisplayRole);
  hModel->setData(hModel->index(1,16),QString("Ширина в"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,16),QString("гориз. \n плоскости"),Qt::DisplayRole);
  hModel->setData(hModel->index(2,17),QString("верт. \n плоскости"),Qt::DisplayRole);
  hModel->setData(hModel->index(3,16),QString("°"),Qt::DisplayRole);
  hModel->setData(hModel->index(3,17),QString("°"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,18),QString("Радиус \n зоны \n обслуживания"),Qt::DisplayRole);
  hModel->setData(hModel->index(3,18),QString("км"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,19),QString("Класс\n излучения"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,20),QString("Поляризация"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,21),QString("ЭИИМ \n заявл."),Qt::DisplayRole);
  hModel->setData(hModel->index(3,21),QString("дБВт"),Qt::DisplayRole);
  hModel->setData(hModel->index(0,22),QString("Место размещения"),Qt::DisplayRole);
  hHead->setRowHeight(2,35);
  hHead->setColumnWidth(0,120);
  hHead->setColumnWidth(22,150);
  hHead->setStretchLastSection(true);


  ui->DBTable_ChTP->setModel(dataModelChTP);
  ui->DBTable_ChTP->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  ui->DBTable_ChTP->verticalHeader()->setDefaultSectionSize(20);
  ui->DBTable_ChTP->setHorizontalHeader(hHead);
}

void MainWindow::drawTableRaschet()
{
  ui->TableWidget_Raschet->horizontalHeader()->setVisible(false);
  ui->TableWidget_Raschet->resizeColumnToContents(0);
  ui->TableWidget_Raschet->insertColumn(0);
  ui->TableWidget_Raschet->verticalHeader()->setDefaultSectionSize(20);

  while (globalQuery.next()) {
    list.append(globalQuery.value(0).toString());
    GUID_list.append(globalQuery.value(1).toString());
  }
  ui->TableWidget_Raschet->setRowCount(list.size());
  for (int i=0; i<=list.size()-1; i++) {
   QTableWidgetItem *newItem = new QTableWidgetItem(list[i]);
   ui->TableWidget_Raschet->setItem(i,0,newItem);
  }
}

void MainWindow::loadDataChTPfromCSV(QString pathcsv, QString GUIDRaschetaStr)
{
  int i = 0;
  if (pathcsv != ""){

    dataModelChTP->clear();
    QFile filecsv(pathcsv + "/" + afShortDirectoryName(pathcsv) + " (БС).csv");

    if(filecsv.exists()) {

      filecsv.open(QIODevice::ReadOnly);
      QTextStream in(&filecsv);
      in.setCodec("Windows-1251");
      while (!in.atEnd()) {

        QList<QStandardItem*> items;
        QString line = in.readLine();

        for (QString item : line.split(";")) {
          items.append(new QStandardItem(item));
        }
        items.removeLast();
        items.removeAt(2);
        items.removeAt(2);
        items.removeAt(2);
        items.removeAt(2);
        items.removeAt(18);
        if(i >= 1) DB_InsertChTP(GUIDRaschetaStr, items);
        items.append(new QStandardItem(items[1]->text()));
        items.removeAt(1);
        items.insert(1, new QStandardItem(afGeoCoordDesToStr(items[1]->text().replace(items[1]->text().indexOf(","),1,".").toDouble())));
        items.insert(3, new QStandardItem(afGeoCoordDesToStr(items[3]->text().replace(items[3]->text().indexOf(","),1,".").toDouble())));
        items.removeAt(6);
        items[6] = new QStandardItem("Азимут");
        if (i >= 1) dataModelChTP->appendRow(items);
        i++;
      }
      filecsv.close();
    }
  }
}

void MainWindow::loadDataChTPfromDB(QString GUIDRaschetaStr)
{
  dataModelChTP->clear();
  DB_SelectChTP(GUIDRaschetaStr);
  while (globalQuery.next()) {
    QList<QStandardItem*> items;
    for(int i = 0; i < 21;i++) items.append(new QStandardItem(globalQuery.value(i).toString()));

    items.insert(1, new QStandardItem(afGeoCoordDesToStr(items[1]->text().replace(items[1]->text().indexOf(","),1,".").toDouble())));
    items.insert(3, new QStandardItem(afGeoCoordDesToStr(items[3]->text().replace(items[3]->text().indexOf(","),1,".").toDouble())));
    switch (items[6]->text().toInt()) {
      case 0:
        items[6] = new QStandardItem("Азимут");
      break;
      case 1:
        items[6] = new QStandardItem("Вращение");
      break;
      case 2:
        items[6] = new QStandardItem("Сектор");
      break;
    }
    dataModelChTP->appendRow(items);
  }
  ui->Button_SelectingRESTerritoriyaChastota->setEnabled(true);
}

void MainWindow::pereborChastot()
{
  mymodelSelectRES->clear();
  QVector <double> chastotyChtP;
  QVector <double> unikChastoty;
  bool isChastota;
  for (int i = 0; i < dataModelChTP->rowCount(); i++) {
      chastotyChtP.append(dataModelChTP->item(i, 13)->text().toDouble());
      chastotyChtP.append(dataModelChTP->item(i, 14)->text().toDouble());
  }
  unikChastoty.append(chastotyChtP[0]);
  for (int i = 1; i < chastotyChtP.size();i++) {
       isChastota = true;
       for( int x = 0; x <= unikChastoty.size() - 1; x++) {
          if(chastotyChtP[i] == unikChastoty[x]) {
            isChastota = true;
            break;
          }
          else
            isChastota = false;
       }
       if (!isChastota)
       unikChastoty.append(chastotyChtP[i]);
  }

  QList<QStandardItem*> items;
  for( int i = 0; i < dataModelRES->rowCount(); i++) {
    for (int x = 0; x < unikChastoty.size();x++) {
      if (dataModelRES->item(i, 3)->text().toDouble() < LTTochka.firstKey() &&
          dataModelRES->item(i, 5)->text().toDouble() > LTTochka.first()    &&
          dataModelRES->item(i, 3)->text().toDouble() > RBTochka.firstKey() &&
          dataModelRES->item(i, 5)->text().toDouble() < RBTochka.first()    &&
          dataModelRES->item(i, 9)->text().toDouble() >= unikChastoty[x] - ui->Edit_OtstuppoChastote->value() &&
          dataModelRES->item(i, 9)->text().toDouble() <= unikChastoty[x] + ui->Edit_OtstuppoChastote->value()) {
        items.append(new QStandardItem(QString("")));
        items.append(new QStandardItem(dataModelRES->item(i, 0)->text()));
        items.append(new QStandardItem(dataModelRES->item(i, 1)->text()));
        for (int j = 6; j < 17; j++) {
          items.append(new QStandardItem(dataModelRES->item(i, j)->text()));
        }
        mymodelSelectRES->appendRow(items);
        items.clear();
        break;
      }
    }
  }

}

void MainWindow::loadDataRES()
{
  dataModelRES->clear();
  DB_SelectRES();
  while (globalQuery.next()) {
    QList<QStandardItem*> items;
    for(int i = 1;i < 18;i++)  items.append(new QStandardItem(globalQuery.value(i).toString()));

    items.append(items[2]);
    items.removeAt(2);
    items.insert(2, new QStandardItem(afGeoCoordDesToStr(items[2]->text().replace(items[2]->text().indexOf(","),1,".").toDouble())));
    items.insert(4, new QStandardItem(afGeoCoordDesToStr(items[4]->text().replace(items[4]->text().indexOf(","),1,".").toDouble())));
    items.removeAt(6);
    switch (items[6]->text().toInt()) {
      case 0:
        items[6] = new QStandardItem("Азимут");
      break;
      case 1:
        items[6] = new QStandardItem("Вращение");
      break;
      case 2:
        items[6] = new QStandardItem("Сектор");
      break;
    }
    switch (items[11]->text().toInt()) {
      case 0:
        items[11] = new QStandardItem("без учёта");
      break;
      case 1:
        items[11] = new QStandardItem("с учётом «R»");
      break;
      case 2:
        items[11] = new QStandardItem("с учётом «R+»");
      break;
    }
    dataModelRES->appendRow(items);
  }

  ui->DBTable_RES->selectRow(0);
}

void MainWindow::refreshTableRaschet(bool stayCurrentRow)
{
  list.clear();
  GUID_list.clear();
  DB_SelectDB();
  while (globalQuery.next()) {
    list.append(globalQuery.value(0).toString());
    GUID_list.append(globalQuery.value(1).toString());
  }
  ui->TableWidget_Raschet->clear();
  ui->TableWidget_Raschet->setRowCount(list.size());
  for (int i=0; i<=list.size()-1; i++) {
    QTableWidgetItem *newItem = new QTableWidgetItem(list[i]);
    ui->TableWidget_Raschet->setItem(i,0,newItem);
  }
  if (stayCurrentRow) {
    for (int i = 0; i < ui->TableWidget_Raschet->rowCount();i++)
          ui->TableWidget_Raschet->item(i,0)->setBackgroundColor(QColor("white"));
    ui->TableWidget_Raschet->item(ui->TableWidget_Raschet->rowCount() - 1,0)->setBackgroundColor(QColor("#ffd700"));
    ui->Label_Naimenovanie->setText(ui->TableWidget_Raschet->item(ui->TableWidget_Raschet->rowCount() - 1,0)->text());
  }
}

int MainWindow::loadRezultatiARM1FromDirectory(const QString &DirectoryPath)
{
  int result = 0;
  QUuid guid;
  QString GUID = guid.createUuid().toString().toUpper();
  QString MaskaNaimenovaniya = afShortDirectoryName(DirectoryPath);
  if (MaskaNaimenovaniya.indexOf("[АРМ#2] ") >= 0)
      MaskaNaimenovaniya.remove(0, 8);

  QString StandartSvyazi = "";
  QString path = DirectoryPath + "/" + "[АРМ#2] " + MaskaNaimenovaniya + " (параметры).ini";

  QDir *dirr = new QDir;
  if (dirr->exists(path)) {
      QSettings sett(path, QSettings::IniFormat);
      sett.beginGroup("ParametriRascheta");
      StandartSvyazi = sett.value("StandartSvyazi","").toString();
      sett.endGroup();
  }
  if (StandartSvyazi == "GSM1800") {
      DB_InsertRaschet(GUID, StandartSvyazi, MaskaNaimenovaniya, DirectoryPath);
      GUIDRaschetaStr_LoadFromDataBase = GUID;
      MaskaNaimenovaniya_LoadFromDataBase = MaskaNaimenovaniya;
      DirektoriyasRezultatami_LoadFromDataBase = DirectoryPath;
      path = DirektoriyasRezultatami_LoadFromDataBase + "/" + "[АРМ#2] " + MaskaNaimenovaniya_LoadFromDataBase + " (параметры).ini";
      ZamenaZapyatoy(path);
      if (dirr->exists(path)) {
          QSettings sett(path, QSettings::IniFormat);
          sett.setIniCodec("UTF-8");

          sett.beginGroup("OblastKarti");
          LTTochka.clear();
          RBTochka.clear();
          LTTochka[sett.value("ShirotaLT", -1).toDouble()] = sett.value("DolgotaLT", -1).toDouble();
          RBTochka[sett.value("ShirotaRB", -1).toDouble()] = sett.value("DolgotaRB", -1).toDouble();
          sett.endGroup();

          qDebug() << LTTochka;
          qDebug() << RBTochka;

          //.... создание записи о координатах левого верхнего угла ....
          DB_InsertZnachenieStr(GUID, "LTKarti.ShirotaDes", QString::number(LTTochka.firstKey(), 'f', 13), 0, 1);
          DB_InsertZnachenieStr(GUID, "LTKarti.DolgotaDes", QString::number(LTTochka.first(), 'f', 13), 0, 1);
          //.... создание записи о координатах правого нижнего угла ....
          DB_InsertZnachenieStr(GUID, "RBKarti.ShirotaDes", QString::number(RBTochka.firstKey(), 'f', 13), 0, 1);
          DB_InsertZnachenieStr(GUID, "RBKarti.DolgotaDes", QString::number(RBTochka.first(), 'f', 13), 0, 1);
          sett.beginGroup("ParametriRascheta");
           //.... высота счета ....
          VisotaScheta = sett.value("VisotaScheta", 30).toDouble();
          sett.endGroup();

          sett.beginGroup("ARM2");
          //.... оператор связи в родительном падеже ....
          OperatorSvyaziRP = sett.value("OperatorSvyaziRP", "").toString();
          //.... создание записи об операторе связи в родительном падеже ....
          DB_InsertZnachenieStr(GUID, "OperatorSvyaziRP", OperatorSvyaziRP, 0, 1);
          //.... территория в родительном падеже ....
          TerritoriyaRP = sett.value("TerritoriyaRP", "").toString();
          //.... создание записи о территории в родительном падеже ....
          DB_InsertZnachenieStr(GUID, "TerritoriyaRP", TerritoriyaRP, 0, 1);
          //.... шифр РЧЗ ....
          ShifrRChZ = sett.value("ShifrRChZ", "").toString();
          //.... создание записи о шифре РЧЗ ....
          DB_InsertZnachenieStr(GUID, "ShifrRChZ", ShifrRChZ, 0, 1);
          //.... диапазон частот ....
          DiapazonChastot = sett.value("DiapazoniChastot", "1805,2-1879,8").toString();
          // Какие-то операции, но это не точно
          //.... создание записи о диапазонах частот ....
          DB_InsertZnachenieStr(GUID, "DiapazoniChastot", DiapazonChastot, 0, 1);
          sett.endGroup();

          sett.beginGroup("ParametriRascheta");
          //.... изменение местоположения БС ....
          IzmenenieMestopologeniyaBS = sett.value("IzmenenieMestopologeniyaBS", false).toBool();
           //.... создание записи об изменении местоположения БС ....
          DB_InsertZnachenieStr(GUID, "IzmenenieMestopologeniyaBS", QString::number(IzmenenieMestopologeniyaBS), 0, 1);

          if (IzmenenieMestopologeniyaBS == true) {
              //.... радиус изменения местоположения БС ....
              RadiusIzmeneniyaMestopologeniyaBS = sett.value("RadiusIzmeneniyaMestopologeniyaBS", 0.5).toDouble() * 1000;
              //.... создание записи о радиусе изменения местоположения БС ....
              DB_InsertZnachenieStr(GUID, "RadiusIzmeneniyaMestopologeniyaBS", QString::number(round(RadiusIzmeneniyaMestopologeniyaBS)), 0, 1);
          }

          //.... изменение высоты подвеса антенны БС ....
          IzmenenieVisotiPodvesaBS = sett.value("IzmenenieVisotiPodvesaBS", false).toBool();
          //.... создание записи об изменении высоты подвеса антенны БС ....
          DB_InsertZnachenieStr(GUID, "IzmenenieVisotiPodvesaBS", QString::number(IzmenenieVisotiPodvesaBS), 0, 1);

          if (IzmenenieVisotiPodvesaBS == true) {
              //.... поднять высоту подвеса антенны БС на ....
              UvelichenieVisotiPodvesa = sett.value("UvelichenieVisotiPodvesa", 15).toDouble();
              //.... создание записи о поднятии высоты подвеса антенны БС на ....
              DB_InsertZnachenieStr(GUID, "UvelichenieVisotiPodvesa", QString::number(UvelichenieVisotiPodvesa), 0, 1);
          }

          sett.endGroup();

          sett.beginGroup("ARM2");
          //.... режим работы базовых станций ....
          IspolzovanieChTP = sett.value("IspolzovanieChTP", "").toString();
          DB_InsertZnachenieStr(GUID, "IspolzovanieChTP", IspolzovanieChTP, 0, 1);

          if (IspolzovanieChTP == "Kombinirovanniy") {
          //.... допустимое ограничение ....
              DopustimoeOgranichenie = sett.value("DopustimoeOgranichenie", -1).toInt();
          //.... создание записи о допустимом ограничении
          //     при работе базовых станций
          //     в комбинированном режиме ....
              DB_InsertZnachenieStr(GUID, "DopustimoeOgranichenie", QString::number(DopustimoeOgranichenie), 0, 1);
          }

          //.... создание записи о расчете от абонентских станций ....
          AS_Check = false;
          DB_InsertZnachenieStr(GUID, "RaschetAS", QString::number(AS_Check), 0, 1);
          //.... радиус учета влияния абонентских станций ....
          RadiusVliyaniyaAS = sett.value("RadiusVliyaniyaAS", 25).toDouble();
          //.... создание записи о радиусе учета влияния абонентских станций ....
          DB_InsertZnachenieStr(GUID, "RadiusVliyaniyaAS", QString::number(RadiusVliyaniyaAS), 0, 1);
          //.... высота подвеса абонента ....
          VisotaPodvesaAbonenta = sett.value("VisotaPodvesaAbonenta", 1.5).toDouble();
          //.... создание записи о высоте подвеса абонента ....
          DB_InsertZnachenieStr(GUID, "VisotaPodvesaAbonenta", QString::number(afRoundTo(VisotaPodvesaAbonenta, -2)), 0, 1);
          //.... ЭИИМ абонента ....
          EIIMAbonenta = sett.value("EIIMAbonenta", -3).toDouble();
          //.... создание записи о ЭИИМ абонента ....
          DB_InsertZnachenieStr(GUID, "EIIMAbonenta", QString::number(afRoundTo(EIIMAbonenta, -1)), 0, 1);
          //.... уровень запуска АС базовой станцией ....
          UrovenZapuskaASBS = sett.value("UrovenZapuskaASBS", -200).toInt();
          //.... создание записи о уровене запуска АС базовой станцией ....
          DB_InsertZnachenieStr(GUID, "UrovenZapuskaASBS", QString::number(UrovenZapuskaASBS), 0, 1);
          //.... модель расчета при учете АС ....
          ModelRaschetaAS = sett.value("ModelRaschetaAS", 0).toInt();
          //.... создание записи о модели расчета при учете АС ....
          //.... 0 - P.1546
          //     1 - ХАТА (Город)
          //     2 - ХАТА (Пригород)
          //     3 - ХАТА (Сельская местность)
          //     4 - ХАТА (Открытое пространство)
          //     5 - свободное пространство ....
          DB_InsertZnachenieStr(GUID, "ModelRaschetaAS", QString::number(ModelRaschetaAS), 0, 1);

          if (ModelRaschetaAS == 0 || ModelRaschetaAS == 1 || ModelRaschetaAS == 2 || ModelRaschetaAS == 3 || ModelRaschetaAS == 4 ) {
              //.... процент времени при учете АС ....
              ProcentVremeniAS = sett.value("ProcentVremeniAS", 50).toInt();
              //.... создание записи о значении процента времени при учете АС ....
              DB_InsertZnachenieStr(GUID, "ProcentVremeniAS", QString::number(ProcentVremeniAS), 0, 1);

              if(ModelRaschetaAS == 0) {
                 //.... процент мест при учете АС ....
                 ProcentMestAS = sett.value("ProcentMestAS", 10).toInt();
                 //.... создание записи о значении процента места при учете АС
                 //     для модели расчета P.1546 ....
                 DB_InsertZnachenieStr(GUID, "ProcentMestAS", QString::number(ProcentMestAS), 0, 1);
                 //.... эталонная высота при учете АС ....
                 VisotaEtalonnayaAS = sett.value("VisotaEtalonnayaAS", 10).toInt();
                 //.... создание записи о эталонной высоте при учете АС
                 //     для модели расчета P.1546 ....
                 DB_InsertZnachenieStr(GUID, "VisotaEtalonnayaAS", QString::number(VisotaEtalonnayaAS), 0, 1);
                 //.... направление анализа при учете АС ....
                 NapravlenieAnalizaAS = sett.value("NapravlenieAnalizaAS", 1).toInt();
                 //.... создание записи о направлении анализа при учете АС
                 //     для модели расчета P.1546 ....
                 DB_InsertZnachenieStr(GUID, "NapravlenieAnalizaAS", QString::number(NapravlenieAnalizaAS), 0, 1);
              }
          }

          //.... зона обслуживания при учете АС ....
          UchetZoniObslugivaniya = sett.value("UchetZoniObslugivaniya", "NeUchitivat").toString();
          //.... создание записи о зоне обслуживания при учете АС ....
          DB_InsertZnachenieStr(GUID, "UchetZoniObslugivaniya", UchetZoniObslugivaniya, 0, 1);

          if (UchetZoniObslugivaniya == "UchitivatRadius") {
              //.... радиус зоны обслуживаия при учете АС ....
              RadiusZoniObslugivaniya = sett.value("RadiusZoniObslugivaniya", 10).toDouble();
              //.... создание записи о радиусе зоны обслуживаия при учете АС ....
              DB_InsertZnachenieStr(GUID, "RadiusZoniObslugivaniya", QString::number(RadiusZoniObslugivaniya), 0, 1);
          }
         //.... создание записи о расчете без учета абонетских станций (БС) ....
         BS_Check = true;
         DB_InsertZnachenieStr(GUID, "RaschetBS", QString::number(BS_Check), 0, 1);
         //.... поляризация базовых станций ....
         PolyarizaciyaBS = sett.value("PolyarizaciyaBS", "Ukazannaya").toString();
         //.... создание записи о поляризации базовых станций ....
         DB_InsertZnachenieStr(GUID, "PolyarizaciyaBS", PolyarizaciyaBS, 0, 1);
         if(PolyarizaciyaBS == "Ukazannaya")  {

            QString sUkazannayaPolyarizaciyaBS = sett.value("UkazannayaPolyarizaciyaBS", "VX").toString();

            polH = sUkazannayaPolyarizaciyaBS.indexOf("H") >= 0;
            polV = sUkazannayaPolyarizaciyaBS.indexOf("V") >= 0;
            polX = sUkazannayaPolyarizaciyaBS.indexOf("X") >= 0;
            polO = sUkazannayaPolyarizaciyaBS.indexOf("O") >= 0;
            DB_InsertZnachenieStr(GUID, "UkazannayaPolyarizaciyaBS", sUkazannayaPolyarizaciyaBS, 0, 1);
         }

         // выгрузка карты
         //.... выгрузка высот ....
         if (dirr->exists(DirektoriyasRezultatami_LoadFromDataBase + "/" + "[АРМ#2] " + MaskaNaimenovaniya_LoadFromDataBase + " (высоты).zip")) {

         }


      }

  }
  // загрузка данных ЧТП в БД и таблицу из csv
  loadDataChTPfromCSV(DB_pathList(GUID),GUID);
  ui->Button_SelectingRESTerritoriyaChastota->setEnabled(true);
  return result;
}

QStringList MainWindow::take_naimenovanieRES()
{
  QStringList naimenovanieRESList;
    for (int i = 0;i < mymodelSelectRES->rowCount(); i++) {
       naimenovanieRESList.append(mymodelSelectRES->item(i, 1)->text());
    }
    return naimenovanieRESList;
}

void MainWindow::dialog_tipires()
{
  TipiRes dialog (this);
  dialog.exec();
}

void MainWindow::dialog_calcparameters()
{
  CalcWindow = new CalcParameters(this);

  connect (CalcWindow,     SIGNAL(signal_take_naimenovanieRES()),
           this,           SLOT(take_naimenovanieRES()));

  CalcWindow->exec();


}

void MainWindow::dialog_addeditres()
{
//  AddEditRES dialog (this);
//  dialog.exec();
}

void MainWindow::select_pageChTP()
{
  ui->PageControl->setCurrentIndex(0);
  ui->Button_ChTPPage->setCursor(Qt::ArrowCursor);
  ui->Button_RESPage->setCursor(Qt::PointingHandCursor);
  ui->Button_ChTPPage->setStyleSheet("QPushButton {border: none;"
                                     "             font-weight: bold;}");
  ui->Button_RESPage->setStyleSheet("QPushButton {font-weight: normal;}");
}

void MainWindow::select_pageRES()
{
  ui->PageControl->setCurrentIndex(1);
  ui->Button_ChTPPage->setCursor(Qt::PointingHandCursor);
  ui->Button_RESPage->setCursor(Qt::ArrowCursor);
  ui->Button_ChTPPage->setStyleSheet("QPushButton {}");
  ui->Button_RESPage->setStyleSheet("QPushButton {border: none;"
                                    "             font-weight: bold}");
}

void MainWindow::on_Button_MapShow_clicked()
{
  if (ui->Button_MapShow->text()==" Отобразить информацию на карте")
  {
    Map_unit->move(this->width()-555,this->height()-580);
    Map_unit->show();
    ui->Button_MapShow->setText(" Скрыть информацию на карте");
  }
  else
  {
    Map_unit->hide();
    ui->Button_MapShow->setText(" Отобразить информацию на карте");
  }
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
  QSize size = e->size();
  Map_unit->move(size.width()-555,size.height()-580);
}

void MainWindow::on_Button_LoadRezultatiARM1_clicked()
{
  LoadWindow = new LoadFromDirectory(this);

  connect(LoadWindow,              SIGNAL(signal_refreshTableRaschet(bool)),
          this,                    SLOT(refreshTableRaschet(bool)));

  connect(LoadWindow,              SIGNAL(signal_loadRezultatiARM1FromDirectory(const QString&)),
          this,                    SLOT(loadRezultatiARM1FromDirectory(const QString&)));

  LoadWindow->exec();
}

void MainWindow::on_TableWidget_Raschet_itemDoubleClicked(QTableWidgetItem *item)
{
  DB_SelectLTRBTochka(GUID_list[item->row()]);

  QVector <double> massiv;
  while (globalQuery.next()) {
    massiv.append(globalQuery.value(0).toDouble());
  }
  LTTochka.clear();
  RBTochka.clear();
  LTTochka[massiv[0]] = massiv[1];
  RBTochka[massiv[2]] = massiv[3];

  ui->Label_Naimenovanie->setText(list[item->row()]);
  loadDataChTPfromDB(GUID_list[item->row()]);

  for (int i = 0; i < ui->TableWidget_Raschet->rowCount();i++)
    ui->TableWidget_Raschet->item(i,0)->setBackgroundColor(QColor("white"));
  item->setBackgroundColor(QColor(255,215,0));

  mymodelSelectRES->clear();

  GUIDRaschetaStr_LoadFromDataBase = GUID_list[item->row()];
  DB_SelectExtern(GUIDRaschetaStr_LoadFromDataBase);
  DB_SelectRESrascheta(GUIDRaschetaStr_LoadFromDataBase);
  if (globalQuery.size() == 0) QMessageBox::information(this, "Информация", "Отсутствуют данные по РЭС, отобранным для\n"
                                                                            "расчета.\n"
                                                                            "Нет данных, удовлетворяющих запросу к таблице\n"
                                                                            "[RESRascheta]", QMessageBox::Close);
  else {
    while (globalQuery.next()) {
      QList<QStandardItem*> items;
      for(int i = 0; i < 13;i++) items.append(new QStandardItem(globalQuery.value(i).toString()));
      items.insert(0, new QStandardItem(""));
      mymodelSelectRES->appendRow(items);
    }
  }
}

void MainWindow::on_Button_RaschetDelete_clicked()
{
  if (GUID_list.isEmpty()) return;
  DB_DeleteStringInDB(GUID_list[ui->TableWidget_Raschet->currentRow()]);
  if( ui->TableWidget_Raschet->item(ui->TableWidget_Raschet->currentRow(),0)->backgroundColor().name() == "#ffd700") {
      dataModelChTP->clear();
      ui->Label_Naimenovanie->clear();
      refreshTableRaschet(false);
     }
  else refreshTableRaschet(true);
}


void MainWindow::on_Button_RaschetDeleteAll_clicked()
{
  for (int i=0; i<=ui->TableWidget_Raschet->rowCount()-1; i++) DB_DeleteStringInDB(GUID_list[i]);
  dataModelChTP->clear();
  ui->Label_Naimenovanie->clear();
  refreshTableRaschet(false);
}

void MainWindow::on_Button_RefreshAll_clicked()
{
  if (db.isOpen())
    refreshTableRaschet(true);
}



void MainWindow::on_DBTable_RES_doubleClicked(const QModelIndex &index)
{
  int row = index.row();
  QStringList dataRes;
  for (int i = 0;i < dataModelRES->columnCount(); i++) {
      dataRes.append(dataModelRES->item(row, i)->text());
  }

  dialog = new AddEditRES(true, "Редактирование записи (данные по РЭС)",dataRes, this, DB_Select_idres(dataRes[0]));
  dialog->exec();

  loadDataRES();
  ui->DBTable_RES->selectRow(row);
}

void MainWindow::on_Button_RESEdit_clicked()
{
  if (dataModelRES->columnCount() == 0) return;
  int row = ui->DBTable_RES->currentIndex().row();
  QStringList dataRes;
  for (int i = 0;i < dataModelRES->columnCount(); i++) {
      dataRes.append(dataModelRES->item(row, i)->text());
  }

  dialog = new AddEditRES(true, "Редактирование записи (данные по РЭС)",dataRes, this, DB_Select_idres(dataRes[0]));
  dialog->exec();

  loadDataRES();
  ui->DBTable_RES->selectRow(row);
}

void MainWindow::on_Button_SelectRESEdit_clicked()
{
  QStringList dataRes;

  dialog = new AddEditRES(true, "Редактирование записи (данные по РЭС, отобранного для расчета)", dataRes, this, DB_Select_idres(dataRes[0]));
  dialog->exec();
}

void MainWindow::on_Button_RESInsert_clicked()
{
  QStringList dataRes;

  dialog = new AddEditRES(false, "Создание новой записи (данные по РЭС)", dataRes, this);
  dialog->exec();

  loadDataRES();
  ui->DBTable_RES->selectRow(dataModelRES->rowCount());
}

void MainWindow::on_Button_SelectingRESTerritoriyaChastota_clicked()
{
  pereborChastot();
}

void MainWindow::test_slot(const QModelIndex, int first, int last)
{
  if(first == 0 && last == 0) {
    ui->Button_SelectRESSetDefaultParameters->setEnabled(true);
    ui->Button_SelectRESAllSetDefaultParameters->setEnabled(true);
    ui->Button_SelectRESEdit->setEnabled(true);
    ui->Button_SelectRESDelete->setEnabled(true);
    ui->Button_SelectRESDeleteAll->setEnabled(true);
    ui->Button_SelectRESSaveToFile->setEnabled(true);
  }
}

void MainWindow::on_Button_SelectingRES_clicked()
{
  int i = ui->DBTable_RES->currentIndex().row();
  if (i == -1) return;
  QString name = dataModelRES->item(i, 0)->text();
  for (int j=0; j<mymodelSelectRES->rowCount(); j++) {
    if (name == mymodelSelectRES->item(j,1)->text()){
      QMessageBox::warning(this,"Предупреждение", "Данная РЭС уже выбрана.", QMessageBox::Close);
      return;
    }
  }
  QList<QStandardItem*> items;
  items.append(new QStandardItem(QString("")));
  items.append(new QStandardItem(dataModelRES->item(i, 0)->text()));
  items.append(new QStandardItem(dataModelRES->item(i, 1)->text()));
  for (int j = 6; j < 17; j++) {
    items.append(new QStandardItem(dataModelRES->item(i, j)->text()));
  }
  mymodelSelectRES->appendRow(items);
}

void MainWindow::on_Button_SelectRESDelete_clicked()
{
  DB_DeleteRESrascheta(GUIDRaschetaStr_LoadFromDataBase, mymodelSelectRES->item(ui->DBTable_SelectRES->currentIndex().row(), 1)->text());
  mymodelSelectRES->removeRow(ui->DBTable_SelectRES->currentIndex().row());
}

void MainWindow::on_Button_SelectRESDeleteAll_clicked()
{
  DB_DeleteAllRESrascheta(GUIDRaschetaStr_LoadFromDataBase);
  mymodelSelectRES->clear();
}

void MainWindow::on_Button_RESDelete_clicked()
{
  int itemRow = ui->DBTable_RES->currentIndex().row();
  if (itemRow == -1) return;
  DB_DeleteRES(dataModelRES->item(itemRow, 0)->text(), false);
  loadDataRES();
}

void MainWindow::on_Button_RESDeleteAll_clicked()
{
  QMessageBox msgBox;
  int itemRow;
  msgBox.setText("Удалить все записи о РЭС ?");
  msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
  msgBox.setDefaultButton(QMessageBox::Cancel);
  int ret = msgBox.exec();
  switch (ret) {
    case QMessageBox::Ok:
        itemRow = ui->DBTable_RES->currentIndex().row();
        if (itemRow == -1) return;
        DB_DeleteRES(dataModelRES->item(itemRow, 0)->text(), true);
        break;
    case QMessageBox::Cancel:
        break;
  }
}
