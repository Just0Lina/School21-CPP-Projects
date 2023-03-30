#include <gtest/gtest.h>

#include "CalculatorModel.h"
#include "CreditModel.h"
using namespace s21;

TEST(Style, Style1) {
  std::string str = {"-2+5"};
  double ans = -2 + 5;
  CalculatorModel model;
  Errors err = model.preCalculate(str);
  ASSERT_EQ(err, Errors::None);
}

TEST(Style, Style2) {
  std::string str = {"----2"};
  CalculatorModel model;
  Errors err = model.preCalculate(str);
  ASSERT_EQ(err, Errors::SignErr);
}

TEST(Style, Style3) {
  std::string str = {"(2+(4)"};
  CalculatorModel model;
  Errors err = model.preCalculate(str);
  ASSERT_EQ(err, Errors::Brack);
}

TEST(Expr, exp1) {
  std::string str = {
      "((cos(12)+sin(30)-tg(14%3)*ln(29)+log(12)+(32*3)-3^3-sqrt(sqrt(12))+"
      "asin("
      "0.23)+acos(0.5)-atan(0.234)+369547634523/"
      "1342*2^5+3-(-16)+(+3)*(-13))*((-2)^3)+12.3524535743-333.3345365*22^16+"
      "3245.3253245436)/2^32+(+2)^2-(-38.21314342354)/"
      "16.123231-(-93245244352.4452435)"};
  double ans =
      ((cos(12) + sin(30) - tan(14 % 3) * log(29) + log10(12) + (32 * 3) -
        pow(3, 3) - sqrt(sqrt(12)) + asin(0.23) + acos(0.5) - atan(0.234) +
        369547634523 / 1342 * pow(2, 5) + 3 - (-16) + (+3) * (-13)) *
           pow((-2), 3) +
       12.3524535743 - 333.3345365 * pow(22, 16) + 3245.3253245436) /
          pow(2, 32) +
      pow((+2), 2) - (-38.21314342354) / 16.123231 - (-93245244352.4452435);
  CalculatorModel model;
  double answer = model.calculation(str);
  ASSERT_EQ(answer, ans);
}

TEST(Expr, exp2) {
  std::string str = {"2+5"};
  double ans = 2 + 5;
  CalculatorModel model;
  double answer = model.calculation(str);
  ASSERT_EQ(answer, ans);
}

TEST(Expr, exp3) {
  std::string str = {"-2^X"};
  double ans = pow(-2, 3);
  CalculatorModel model;
  double answer = model.calculation(str, 3);
  ASSERT_EQ(answer, ans);
}

TEST(Expr, exp4) {
  std::string str = {"-2/0"};
  CalculatorModel model;
  Errors err = model.preCalculate(str);
  ASSERT_EQ(err, Errors::Div0);
}

TEST(Credit, credit) {
  int duration = 2;             // mounths
  double sum = 2000, bid = 12;  // per year
  CreditModel credit;
  std::vector<double> ans =
      credit.creditCalc(sum, duration, bid, Type::Annuity);
  ASSERT_TRUE(fabs(ans[0] - 1015.02) < 1e-2);
  ASSERT_TRUE(fabs(ans[1] - 2030.05) < 1e-2);
  ASSERT_TRUE(fabs(ans[2] - 30.049751) < 1e-6);

  ans = credit.creditCalc(sum, duration, bid, Type::Diff);
  std::cout << ans[3] << " " << ans[2] << " " << ans[0] << std::endl;

  ASSERT_TRUE(fabs(ans[3] - 30) < 1e-2);
  ASSERT_TRUE(fabs(ans[2] - 2030) < 1e-2);

  ASSERT_TRUE(fabs(ans[0] - 1020) < 1e-1);
  ASSERT_TRUE(fabs(ans[1] - 1010) < 1e-1);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
