#include "msgdlgload.h"
#include "ui_msgdlgload.h"

MsgDlgLoad::MsgDlgLoad(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::MsgDlgLoad)
{
  ui->setupUi(this);
}

MsgDlgLoad::~MsgDlgLoad()
{
  delete ui;
}
