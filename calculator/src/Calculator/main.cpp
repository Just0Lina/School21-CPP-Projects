
#include "CalculatorView.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::CalculatorView view;
  view.setWindowTitle("Calculator");
  view.show();
  return a.exec();
}
