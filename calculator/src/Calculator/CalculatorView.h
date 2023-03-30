#ifndef CALCULATORVIEW_H
#define CALCULATORVIEW_H


#include <QApplication>
#include <QButtonGroup>
#include <QMainWindow>
#include <iostream>

#include "CalculatorController.h"
#include "CreditView.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
namespace s21 {
class CalculatorView : public QMainWindow {
  Q_OBJECT

 public:
  CalculatorView(QWidget *parent = nullptr);
  ~CalculatorView() override;

 private:
  CalculatorController &controller{CalculatorController::getInstance()};
  Ui::MainWindow *ui;
  CreditView credit;
  bool xInLine;
  double xBegin, xEnd, h, X;
  double N;
  QVector<double> x, y;
  void setGraphProp();

 private slots:
  void createGroup();
  void equalClicked();
  void buttonClicked(QAbstractButton *btn);
  //    void xInLine();
  //    void on_eraseButton_clicked();
  void graphClicked();
  void on_credit_triggered();

  void on_usual_triggered();

 signals:
};
}  // namespace s21
#endif  // CALCULATORVIEW_H
