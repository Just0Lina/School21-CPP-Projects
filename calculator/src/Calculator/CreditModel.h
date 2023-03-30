#ifndef CREDITMODEL_H
#define CREDITMODEL_H



#include <cmath>
#include <iostream>
#include <vector>
namespace s21 {
enum Type { Annuity, Diff };
class CreditModel {
 public:
  CreditModel() = default;
  ~CreditModel() = default;
  std::pair<double, double> getAnnPays(double &sum, double &monthly_pay,
                                       double &coef);
  std::vector<double> creditCalc(double sum, int duration, double perc,
                                 enum Type);
  double getMounthlyPayAnn(double &percForMounth, int &duration, double &sum);
  double getMounthlyPayDiff(double &payForMainDuty, double sum, double &perc);
  double getPercForMounth(double &bid);
  double getFullPaymentAnn(double monthlyPay, int duration);
  double getPayForMainDuty(double sum, int dur);
  double getOverpay(double fullPayment, double sum);

 private:
};
}  // namespace s21
#endif  // CREDITMODEL_H
