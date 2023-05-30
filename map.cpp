#include "map.h"
#include "ui_map.h"
#include <QGraphicsPixmapItem>

Map::Map(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Map)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint  );
    QPixmap pixmap("");
    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem;
    QGraphicsScene *scene = new QGraphicsScene;
    pixmapItem->setVisible(true);
    pixmapItem->setPixmap(pixmap);
    scene->addItem(pixmapItem);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    scene->setSceneRect(0,0,pixmap.width(), pixmap.height());
    ui->graphicsView->setScene(scene);
    double scaleWith = ui->graphicsView->parentWidget()->width()-6;
    double scaleHeight = ui->graphicsView->parentWidget()->height()-6;
    ui->graphicsView->scale(scaleWith/pixmap.width(), scaleHeight/pixmap.height());
}

Map::~Map()
{
    delete ui;
}
