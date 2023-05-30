#pragma once

#include <QDialog>

namespace Ui {
class MsgDlgLoad;
}

class MsgDlgLoad : public QDialog
{
  Q_OBJECT

public:
  explicit MsgDlgLoad(QWidget *parent = 0);
  ~MsgDlgLoad();

private:
  Ui::MsgDlgLoad *ui = nullptr;
};
