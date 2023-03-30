#ifndef CALCULATORCONTROLLER_H
#define CALCULATORCONTROLLER_H

#include <QString>

#include "CalculatorModel.h"
#include "CreditModel.h"
namespace s21 {

class CalculatorController {
 private:
  CalculatorController() = default;
  ~CalculatorController() = default;

 public:
  static CalculatorController &getInstance() {
    static CalculatorController controller;
    return controller;
  }

  QString calculate(QString str, double x = 0);
  QString getErrorType(Errors error);
  enum Errors preCalculate(QString &str);
  std::pair<double, double> creditCalc(double &, double &, double &coef);
  double getMounthlyPayAnn(double &percForMounth, int &duration, double &sum);
  double getMounthlyPayDiff(double &payForMainDuty, double sum, double &perc);
  double getPercForMounth(double &bid);
  double getFullPaymentAnn(double monthlyPay, int duration);
  double getPayForMainDuty(double sum, int dur);
  double getOverpay(double fullPayment, double sum);

 private:
  CalculatorModel model;
  CreditModel modelCredit;
};
}  // namespace s21

#endif  // CALCULATORCONTROLLER_H
