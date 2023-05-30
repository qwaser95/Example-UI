#pragma once

#include <QDialog>

namespace Ui {
class Map;
}

class Map : public QDialog
{
  Q_OBJECT

public:
  explicit Map(QWidget *parent = 0);
  ~Map();

private:
  Ui::Map *ui = nullptr;
};
