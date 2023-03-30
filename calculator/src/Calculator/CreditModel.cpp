#include "CreditModel.h"

std::pair<double, double> s21::CreditModel::getAnnPays(double &sum,
                                                  double &monthly_pay,
                                                  double &coef) {
  double monthPerc = (sum)*coef;
  double payForMainDuty = monthly_pay - monthPerc;
  sum -= payForMainDuty;
  return std::make_pair(payForMainDuty, monthPerc);
}

std::vector<double> s21::CreditModel::creditCalc(double sum, int duration,
                                            double perc, enum Type type) {
  std::vector<double> data;
  double  totalPayment = 0, monthlyPayment;
  double percForMounth = getPercForMounth(perc);
  if (type == Type::Annuity) {
    monthlyPayment = getMounthlyPayAnn(percForMounth, duration, sum);
    data.push_back(monthlyPayment);
    totalPayment = getFullPaymentAnn(monthlyPayment, duration);
    data.push_back(totalPayment);
    std::cout << getFullPaymentAnn(monthlyPayment, duration) << std::endl;

  } else {
    double payForMainDuty = getPayForMainDuty(sum, duration);
    data.push_back(getMounthlyPayDiff(payForMainDuty, sum, percForMounth));
    double tmpSum = sum;
    for (int i = 0; i < duration; ++i) {
      monthlyPayment =
          getMounthlyPayDiff(payForMainDuty, tmpSum, percForMounth);
      totalPayment += monthlyPayment;
      tmpSum -= payForMainDuty;
    }
    data.push_back(monthlyPayment);
    data.push_back(totalPayment);
  }
  data.push_back(getOverpay(totalPayment, sum));
  std::cout << " d" << totalPayment << std::endl;
  std::cout << getOverpay(totalPayment, sum) << std::endl;

  return data;
}

double s21::CreditModel::getMounthlyPayAnn(double &percForMounth, int &duration,
                                      double &sum) {
  double annCoef = percForMounth * pow((1 + percForMounth), duration) /
                   (pow((1 + percForMounth), duration) - 1);
  return sum * annCoef;
}

double s21::CreditModel::getMounthlyPayDiff(double &payForMainDuty, double sum,
                                       double &perc) {
  return payForMainDuty + (sum)*perc;
}

double s21::CreditModel::getPercForMounth(double &bid) { return bid / (100 * 12); }

double s21::CreditModel::getFullPaymentAnn(double monthlyPay, int duration) {
  return monthlyPay * duration;
}

double s21::CreditModel::getPayForMainDuty(double sum, int dur) { return sum / dur; }

double s21::CreditModel::getOverpay(double fullPayment, double sum) {
  return fullPayment - sum;
}

