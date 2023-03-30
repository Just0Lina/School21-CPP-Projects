#ifndef CREDITVIEW_H
#define CREDITVIEW_H


#include <QDialog>
#include <cmath>

#include "CalculatorController.h"

namespace Ui {
class CreditView;
}
namespace s21 {
class CreditView : public QDialog {
  Q_OBJECT

 public:
  explicit CreditView(QWidget *parent = nullptr);
  ~CreditView() override;

 private:
  CalculatorController &controller{CalculatorController::getInstance()};
  Ui::CreditView *ui;
  inline void fixDuration(int &durType, int &dur);
  std::pair<double, double> annuityPayment(double sum, double &bid, int &dur);
  std::pair<double, double> differentiatedPayment(double sum, double &bid,
                                                  int &dur);
  void createTableView(int dur);
  inline QString getFormatedString(double n);

 private slots:
  void countClicked();

  void on_table_clicked(const QModelIndex &index);
};
}  // namespace s21
#endif  // CREDITVIEW_H
