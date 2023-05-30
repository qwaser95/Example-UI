#include "loadfromdirectory.h"
#include "ui_loadfromdirectory.h"
#include "mainwindow.h"


LoadFromDirectory::LoadFromDirectory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadFromDirectory)
{
    ui->setupUi(this);
    model = new QFileSystemModel;
    model->setRootPath("/home");
    model->setReadOnly(true);
    model->setFilter(QDir::AllDirs);
    ui->treeView->setModel(model);
    ui->treeView->setColumnWidth(0,300);
}

LoadFromDirectory::~LoadFromDirectory()
{
    delete ui;
}

void LoadFromDirectory::on_pushButton_clicked()
{
    int iResult = 0;
    QString sDirectoryPath;

    if (ui->lineEdit->text()=="")
    {
        this->close();
        return;
    }
    else
    {
        sDirectoryPath = ui->lineEdit->text();
        QDir *dir = new QDir(sDirectoryPath);
        if(dir->exists()) {
            iResult = emit signal_loadRezultatiARM1FromDirectory(ui->lineEdit->text());
        }
    }
    this->close();
    emit signal_refreshTableRaschet(true);
}

void LoadFromDirectory::on_treeView_clicked(const QModelIndex &index)
{
    Q_UNUSED(index)
    QModelIndexList lst = ui->treeView->selectionModel()->selectedIndexes();
    ui->lineEdit->setText(model->filePath(lst.at(0)));
}
