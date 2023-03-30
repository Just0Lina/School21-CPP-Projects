#include "CalculatorModel.h"

double s21::CalculatorModel::calculate(std::string input, Errors &error,
                                  double val) {
  std::stack<double> sign_stack;
  error = Errors::None;
  size_t size = input.size(), i = 0;
  while (i < size) {
    if (isdigit(input[i])) {
      double count = getDigit(input, i);
      sign_stack.push(count);
      ++i;
      continue;
    }
    if (input[i] == 'X') {
      sign_stack.push(val);
      i += 2;
      continue;
    }
    double one = 0, two = 0;
    if (!sign_stack.empty()) {
      one = sign_stack.top();
      sign_stack.pop();
    }
    if (isSign(input[i]) && !sign_stack.empty()) {
      two = sign_stack.top();
      sign_stack.pop();
    }
    if (isSign(input[i]) || input[i] == 'u') {
      one = signCase(input[i], one, two);
      if (one != one) {
        error = Errors::Sth;
        return 0;
      }
    } else if (isTrig(input[i])) {
      one = trigCase(input[i], one);
    }
    i += 2;
    sign_stack.push(one);
  }
  if (!sign_stack.empty()) return sign_stack.top();
  return 0;
}

double s21::CalculatorModel::getDigit(std::string str, size_t &i) {
  double ans = str[i] - '0';
  int exp = 0;
  ++i;

  while (isdigit(str[i]) || str[i] == '.') {
    if (exp) ++exp;
    if (str[i] == '.') {
      exp = 1;
    } else {
      ans = ans * 10 + str[i] - '0';
    }
    ++i;
  }
  if (exp) ans /= pow(10, exp - 1);
  return ans;
}

double s21::CalculatorModel::signCase(int sign, double one, double two) {
  double ans = one;
  switch (sign) {
    case 'u':
      ans *= -1;
      break;
    case '+':
      ans += two;
      break;
    case '-':
      ans = two - one;
      break;
    case '/':
      if (one == 0) {
        return NAN;
      } else {
        ans = two / one;
      }
      break;
    case '*':
      ans *= two;
      break;
    case '%':
      ans = fmod(two, one);
      break;
    case '^':
      ans = pow(two, one);
      break;
  }
  return ans;
}

double s21::CalculatorModel::calculation(std::string str, double val) {
  Errors err = preCalculate(str);
  if (err == Errors::None) {
    return calculate(str, err, val);
  }
  return 0;
}
double s21::CalculatorModel::trigCase(int sign, double one) {
  switch (sign) {
    case 'c':
      return cos(one);
    case 't':
      return tan(one);
    case 's':
      return sin(one);
    case 'S':
      return sqrt(one);
    case 'l':
      return log(one);
    case 'L':
      return log10(one);
    case 'T':
      return atan(one);
    case 'A':
      return asin(one);
    case 'a':
      return acos(one);
  }
  return 0;
}

enum s21::Errors s21::CalculatorModel::preCalculate(std::string &str) {
  SyntaxErrors s(str);
  Errors err = s.syntaxError();
  str = s.get_ans();
  return err;
}

enum s21::Errors s21::CalculatorModel::SyntaxErrors::syntaxError() {
  int bracket = 0;
  size_t size = str_.size();
  int comas = 0;
  while (str_ind_ < size) {
    size_t shift = 0;

    if (isDigit(str_ind_)) {
      if (str_[str_ind_] == '.') ++comas;
      if (comas > 1) return Errors::TooMuchComas;
      ++str_ind_;

      continue;
    }
    comas = 0;
    if (str_ind_ && isdigit(str_[str_ind_ - 1])) {
      ans_.push_back(' ');
      while (!notation_stack.empty() && notation_stack.top() == 'u' &&
             !(str_[str_ind_] == '^')) {
        addOutput();
      }
    }

    if (isBracket(bracket)) {
      sendBracket();
      ++str_ind_;
      continue;
    }
    if (isUnaryOp()) {
      if (str_[str_ind_] == '-') {
        notation_stack.push('u');
      }
      ++str_ind_;
      continue;
    }
    if (str_ind_ > 0 && isSign(str_[str_ind_])) {
      if (zeroDivCase()) {
        return Errors::Div0;
      }
      shift = 1;
      sendSign(str_[str_ind_]);
    } else {
      shift = isTrigan();
      if (shift) {
        ++bracket;
        sendTrig();
        notation_stack.push('(');
      }
    }
    if (shift) {
      if (isCorrectOperation(shift)) {
        str_ind_ += shift;
        continue;
      }
    }
    return Errors::SignErr;
  }
  if (str_ind_ && isdigit(str_[str_ind_ - 1])) {
    ans_.push_back(' ');
    while (!notation_stack.empty() && notation_stack.top() == 'u' &&
           !(str_[str_ind_] == '^')) {
      addOutput();
    }
  }
  if (bracket != 0) return Errors::Brack;
  while (!notation_stack.empty()) {
    addOutput();
  }
  return Errors::None;
}

void s21::CalculatorModel::SyntaxErrors::sendBracket() {
  if (str_[str_ind_] == '(') {
    notation_stack.push(str_[str_ind_]);
  } else {
    if ((!notation_stack.empty()) &&
        (isSign(notation_stack.top()) || notation_stack.top() == 'u')) {
      while (notation_stack.top() != '(') {
        addOutput();
      }
    }
    notation_stack.pop();
    if ((!notation_stack.empty()) && isTrig(notation_stack.top())) {
      addOutput();
    }
  }
}

void s21::CalculatorModel::SyntaxErrors::sendSign(char val) {
  char stack_top = !notation_stack.empty() ? notation_stack.top() : 0;
  if (val == '+' || val == '-') {
    if (!notation_stack.empty() && (isSign(stack_top))) {
      while (!notation_stack.empty() && notation_stack.top() != '(') {
        addOutput();
      }
    }
  } else if (val == '*' || val == '/' || val == '%') {
    if (!notation_stack.empty() && (stack_top == '*' || stack_top == '/' ||
                                    stack_top == '^' || stack_top == '%')) {
      addOutput();
    }
  } else {
    if (!notation_stack.empty() && (stack_top == '^')) {
      addOutput();
    }
  }
  notation_stack.push(val);
}

void s21::CalculatorModel::SyntaxErrors::sendTrig() {
  char next_let = str_[str_ind_ + 1];
  switch (str_[str_ind_]) {
    case 'c':
      notation_stack.push('c');
      break;
    case 't':
      notation_stack.push('t');
      break;
    case 's':
      if (next_let == 'i') {
        notation_stack.push('s');  // sin
      } else {
        notation_stack.push('S');  // sqrt
      }
      break;
    case 'l':
      if (next_let == 'o') {
        notation_stack.push('L');  // log
      } else {
        notation_stack.push('l');  // ln
      }
      break;
    case 'a':
      if (next_let == 's') {
        notation_stack.push('A');  // asin
      } else if (next_let == 'c') {
        notation_stack.push('a');  // acos
      } else {
        notation_stack.push('T');  // atan
      }
      break;
  }
}

void s21::CalculatorModel::SyntaxErrors::addOutput() {
  ans_.push_back(notation_stack.top());
  ans_.push_back(' ');
  notation_stack.pop();
}

bool s21::CalculatorModel::SyntaxErrors::zeroDivCase() {
  return str_[str_ind_] == '/' && str_ind_ < str_.size() &&
         str_[str_ind_ + 1] == '0' &&
         (str_ind_ == static_cast<size_t>(str_.size()) - 2 ||
          str_[str_ind_ + 2] != '.');
}

bool s21::CalculatorModel::SyntaxErrors::isDigit(int str_ind) {
  size_t i = str_ind > 0 ? static_cast<size_t>(str_ind) : str_ind_;
  if (isdigit(str_[i])) {
    if (i && str_[i - 1] == 'X') {
      return false;
    } else {
      ans_.push_back(str_[i]);
    }
    return true;
  }
  if (str_[i] == 'X') {
    if (i && isdigit(str_[i - 1])) {
      return false;
    } else {
      ans_.push_back('X');
      ans_.push_back(' ');
    }
    return true;
  }

  if (i && str_[i] == '.') {
    if ((i + 1 == str_.size() ||
         (i + 1 < str_.size() && isdigit(str_[i + 1]))) &&
        isdigit(str_[i - 1])) {
      ans_.push_back('.');
      return true;
    }
    return false;
  }
  return false;
}

bool s21::CalculatorModel::SyntaxErrors::isCorrectOperation(size_t shift) {
  if ((shift == 1 &&
       (isdigit(str_[str_ind_ - 1]) || str_[str_ind_ - 1] == ')' ||
        str_[str_ind_ - 1] == 'X')) ||
      (shift > 1 && (!str_ind_ || isSign(str_[str_ind_ - 1]) ||
                     str_[str_ind_ - 1] == '('))) {
    return true;
  }
  return false;
}

bool s21::CalculatorModel::SyntaxErrors::isBracket(int &bracket) {
  if (str_[str_ind_] == '(' && (str_ind_ + 1 < str_.size()) &&
      str_[str_ind_ + 1] != ')' &&
      (!str_ind_ || !isdigit(str_ind_ - 1) || str_[str_ind_ - 1] != 'X')) {
    bracket += 1;
    return true;
  } else if (str_[str_ind_] == ')' && bracket > 0) {
    bracket -= 1;
    return true;
  }
  return false;
}

bool s21::CalculatorModel::SyntaxErrors::isUnaryOp(int str_ind) {
  size_t i = str_ind > 0 ? (size_t)str_ind : str_ind_;
  return (!i || str_[i - 1] == '(') && (str_[i] == '-' || str_[i] == '+');
}

bool s21::CalculatorModel::isSign(int sign) {
  return (sign == '+' || sign == '-' || sign == '*' || sign == '/' ||
          sign == '%' || sign == '^');
}

size_t s21::CalculatorModel::SyntaxErrors::isTrigan(int str_ind) {
  size_t i = str_ind > 0 ? (size_t)str_ind : str_ind_;
  size_t shift = 0;
  if (str_[i] == 'a') {
    if (str_.substr(i, 5) == "acos(" || str_.substr(i, 5) == "asin(" ||
        str_.substr(i, 5) == "atan(") {
      shift = 5;
    }
  } else if (str_[i] == 's') {
    if (str_.substr(i, 4) == "sin(")
      shift = 4;
    else if (str_.substr(i, 5) == "sqrt(")
      shift = 5;
  } else if (str_[i] == 'l') {
    if (str_.substr(i, 4) == "log(")
      shift = 4;
    else if (str_.substr(i, 3) == "ln(")
      shift = 3;
  } else if (str_.substr(i, 4) == "cos(") {
    shift = 4;
  } else if (str_.substr(i, 3) == "tg(") {
    shift = 3;
  }
  return shift;
}

bool s21::CalculatorModel::isTrig(char a) {
  return a == 'c' || a == 't' || a == 's' || a == 'S' || a == 'l' || a == 'L' ||
         a == 'a' || a == 'A' || a == 'T';
}
