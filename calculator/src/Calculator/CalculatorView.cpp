
#include "CalculatorView.h"

#include "StyleHelper.h"
#include "qcustomplot.h"
#include "ui_CalculatorView.h"

#define HIGHT 500
#define WIDTH 750
#define ADD_WIDTH 430

s21::CalculatorView::~CalculatorView() { delete ui; }

s21::CalculatorView::CalculatorView(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), xInLine(false) {
  ui->setupUi(this);
  this->setFixedSize(QSize(WIDTH, HIGHT));
  ui->Display->setText("0.0");
  createGroup();

  QPalette pal = QPalette();
  pal.setColor(QPalette::Window, QColor(231, 238, 240));
  this->setPalette(pal);
  QPalette pal2 = QPalette();
  pal2.setColor(QPalette::Base, QColor(243, 246, 248));
  pal2.setColor(QPalette::Text, QColor(18, 69, 89));
  ui->Display->setPalette(pal2);

  connect(ui->buttonGraph, SIGNAL(clicked()), this, SLOT(graphClicked()));
  connect(ui->buttonEqual, SIGNAL(clicked()), this, SLOT(equalClicked()));
}

void s21::CalculatorView::on_credit_triggered() {
  credit.show();
  hide();
}

void s21::CalculatorView::on_usual_triggered() {
  show();
  credit.hide();
}

void s21::CalculatorView::createGroup() {
  ui->buttonGraph->setStyleSheet(StyleHelper::getStyleButton1());
  ui->buttonEqual->setStyleSheet(StyleHelper::getStyleButton1());
  for (auto &i : ui->numGroup->buttons())
    i->setStyleSheet(StyleHelper::getStyleButton3());
  for (auto &i : ui->trigGroup->buttons())
    i->setStyleSheet(StyleHelper::getStyleButton2());
  for (auto &i : ui->signGroup->buttons())
    i->setStyleSheet(StyleHelper::getStyleButton1());
  connect(ui->trigGroup, SIGNAL(buttonClicked(QAbstractButton *)), this,
          SLOT(buttonClicked(QAbstractButton *)));
  connect(ui->signGroup, SIGNAL(buttonClicked(QAbstractButton *)), this,
          SLOT(buttonClicked(QAbstractButton *)));
  connect(ui->numGroup, SIGNAL(buttonClicked(QAbstractButton *)), this,
          SLOT(buttonClicked(QAbstractButton *)));
}

void s21::CalculatorView::buttonClicked(QAbstractButton *button) {
  QString butVal = button->text();
  QString str = ui->Display->text();
  if (str == "0.0") {
    ui->Display->clear();
    ui->Display->setText(butVal);
  } else {
    ui->Display->insert(butVal);
  }
  if (butVal.endsWith("s") || butVal.endsWith("n") || butVal.endsWith("t") ||
      butVal.endsWith("g")) {
    ui->Display->insert("(");
  } else if (butVal == "AC") {
    this->setFixedSize(QSize(WIDTH, HIGHT));
    if (ui->graph->graphCount()) ui->graph->clearGraphs();
    ui->Display->setText("0.0");
    ui->answer->clear();
    xInLine = false;
  } else if (butVal == "C") {
    if (str.endsWith('X')) xInLine = false;
    str.chop(1);
    if (str.isEmpty())
      ui->Display->setText("0.0");
    else
      ui->Display->setText(str);
  } else if (butVal == 'X')
    xInLine = true;
}

void s21::CalculatorView::graphClicked() {
  if (ui->graph->graphCount()) ui->graph->clearGraphs();
  ui->graph->setBackground(QColor::fromRgb(218, 229, 233));
  this->setFixedSize(QSize(WIDTH + ADD_WIDTH, HIGHT));
  xBegin = ui->valueFrom->value();
  xEnd = ui->valueTo->value();
  ui->graph->xAxis->setRange(ui->valueFrom->value(), ui->valueFrom->value());
  ui->graph->yAxis->setRange(ui->valueFrom->value(), ui->valueFrom->value());
  ui->graph->replot();
  ui->graph->setInteraction(QCP::iRangeZoom, true);
  ui->graph->setInteraction(QCP::iRangeDrag, true);

  N = 10000;
  h = (xEnd - xBegin) / N;
  if (xBegin == xEnd) return;
  QString str1 = ui->Display->text();
  QByteArray ba = str1.toLatin1();
  QString str = ui->Display->text();
  Errors res = controller.preCalculate(str);
  if (res == Errors::None) {
    for (X = xBegin; X <= xEnd; X += h) {
      QString res = controller.calculate(str, X);
      double Y = res.toDouble();
      x.push_back(X);
      y.push_back(Y);
    }
  } else {
    ui->answer->setText(controller.getErrorType(res));
  }
  if (!ui->graph->graphCount()) {
    ui->graph->addGraph();
    setGraphProp();
    QLinearGradient gradient(ui->graph->rect().topLeft(),
                             ui->graph->rect().topRight());
    gradient.setColorAt(0.0, QColor::fromRgb(109, 150, 165));
    gradient.setColorAt(1.0, QColor::fromRgb(255, 255, 255));
    QPen pen(gradient, 5);
    ui->graph->graph(0)->setPen(pen);
    ui->graph->graph(0)->addData(x, y);
    ui->graph->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssDot);
    ui->graph->replot();
    x.clear();
    y.clear();
  }
}

void s21::CalculatorView::setGraphProp() {
  QColor pal(109, 150, 165);
  ui->graph->xAxis->setBasePen(QPen(pal));
  ui->graph->xAxis->setLabelColor(pal);
  ui->graph->xAxis->setTickLabelColor(pal);
  ui->graph->xAxis->setTickPen(QPen(pal));
  ui->graph->xAxis->setSubTickPen(QPen(pal));

  ui->graph->yAxis->setBasePen(QPen(pal));
  ui->graph->yAxis->setLabelColor(pal);
  ui->graph->yAxis->setTickLabelColor(pal);
  ui->graph->yAxis->setTickPen(QPen(pal));
  ui->graph->yAxis->setSubTickPen(QPen(pal));
}
void s21::CalculatorView::equalClicked() {
  QString str = ui->Display->text();
  Errors res = controller.preCalculate(str);
  if (res == Errors::None) {
    if (!xInLine) {
      ui->answer->setText(controller.calculate(str));
    } else
      ui->answer->setText(controller.calculate(str, ui->doubleX->value()));
  } else {
    ui->answer->setText(controller.getErrorType(res));
  }
}
