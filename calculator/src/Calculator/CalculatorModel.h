#ifndef CALCULATORMODEL_H
#define CALCULATORMODEL_H


#include <cctype>
#include <cmath>
#include <iostream>
#include <stack>
#include <string>
namespace s21 {
enum Errors {
  None,
  Div0,
  Infinity,
  Brack,
  InProgress,
  SignErr,
  Sth,
  TooMuchComas
};

class CalculatorModel {
 public:
  CalculatorModel() = default;
  ~CalculatorModel() = default;
  enum Errors preCalculate(std::string &str);
  double calculate(std::string str, Errors &error, double x = 0);
  double getDigit(std::string str, size_t &ind);
  static bool isSign(int sign);
  static bool isTrig(char i);
  double trigCase(int sign, double one);
  double signCase(int sign, double one, double two);
  double calculation(std::string str, double val = 0);

  class SyntaxErrors {
   public:
    std::string get_ans() { return ans_; }
    SyntaxErrors(std::string str) : str_(str) {}
    enum Errors syntaxError();

   private:
    bool isDigit(int str_ind = -1);
    bool isBracket(int &bracket);
    bool isUnaryOp(int str_ind = -1);
    bool isCorrectOperation(size_t shift);
    bool zeroDivCase();
    void sendSign(char val);
    void sendBracket();
    void sendTrig();
    size_t isTrigan(int i = -1);
    void addDigit();
    void addOutput();

    std::stack<char> notation_stack;
    size_t str_ind_ = 0;
    std::string str_;
    std::string ans_;
  };
};
}  // namespace s21
#endif  // CALCULATORMODEL_H

/* SYNTAX CHECKED:
 * (((())))
 * ((((88-6)
 * sin(9*cos(88%X))
 * -sin(9*cos(88%X)/0)
 * -sin(9*cos(88%X)/atan(atan(X)))
 * -(-(-(-4)))+4
 * tg(7*9)
 */
