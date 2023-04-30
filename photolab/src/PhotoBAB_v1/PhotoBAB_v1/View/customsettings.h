#ifndef CUSTOMSETTINGS_H
#define CUSTOMSETTINGS_H

#include <QDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QSpinBox>
#include <iostream>

//#include "Controller/controller.h"
using Matrixx = std::vector<std::vector<double>>;

namespace Ui {
class CustomSettings;
}

class CustomSettings : public QDialog {
  Q_OBJECT

 public:
  explicit CustomSettings(int row, int col, QWidget *parent = nullptr);
  ~CustomSettings();
  std::vector<std::vector<double>> GetMatrix() { return matrix; }
  QList<QSpinBox *> list;
 public slots:  // notice this. it makes it a slot
                //    void valueChanged(); // to be called when clicked

 private slots:
  void on_apply_btn_clicked();

 private:
  //    s21::Controller controller_;
  Ui::CustomSettings *ui;
  std::vector<std::vector<double>> matrix;
  int row_, col_;
  //    QGridLayout *layout = nullptr ;
};

#endif  // CUSTOMSETTINGS_H
