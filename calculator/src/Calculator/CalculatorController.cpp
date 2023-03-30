#include "CalculatorController.h"
QString s21::CalculatorController::calculate(QString str, double x) {
  Errors err = Errors::None;
  double ans = model.calculate(str.toStdString(), err, x);
  if (err != Errors::None) {
    return getErrorType(err);
  }
  return QString::number(ans);
}

QString s21::CalculatorController::getErrorType(Errors error) {
  if (error == Errors::Div0)
    return "Division by zero happened!";
  else if (error == Errors::Infinity)
    return "Infinity returned!";
  else if (error == Errors::Brack)
    return "Control reaches of brackets";
  else if (error == Errors::InProgress)
    return "Still testing";
  else if (error == Errors::Sth)
    return "You got syntax error!";
  else if (error == Errors::SignErr)
    return "You got syntax error with signs!";
  else if (error == Errors::TooMuchComas)
    return "You got too much comas in one number!";
  else
    return "Error happend!";
}

enum s21::Errors s21::CalculatorController::preCalculate(QString &str) {
  std::string modStr = str.toStdString();
  Errors err = model.preCalculate(modStr);
  str = QString::fromUtf8(modStr.c_str());
  return err;
}

std::pair<double, double> s21::CalculatorController::creditCalc(
    double &sum, double &monthlyPay, double &percForMounth) {
  return modelCredit.getAnnPays(sum, monthlyPay, percForMounth);
}

double s21::CalculatorController::getMounthlyPayDiff(double &payForMainDuty,
                                                double sum, double &perc) {
  return modelCredit.getMounthlyPayDiff(payForMainDuty, sum, perc);
}

double s21::CalculatorController::getMounthlyPayAnn(double &percForMounth,
                                               int &duration, double &sum) {
  return modelCredit.getMounthlyPayAnn(percForMounth, duration, sum);
}

double s21::CalculatorController::getPercForMounth(double &bid) {
  return modelCredit.getPercForMounth(bid);
}

double s21::CalculatorController::getFullPaymentAnn(double monthlyPay,
                                               int duration) {
  return modelCredit.getFullPaymentAnn(monthlyPay, duration);
}

double s21::CalculatorController::getPayForMainDuty(double sum, int dur) {
  return modelCredit.getPayForMainDuty(sum, dur);
}

double s21::CalculatorController::getOverpay(double fullPayment, double sum) {
  return modelCredit.getOverpay(fullPayment, sum);
}
