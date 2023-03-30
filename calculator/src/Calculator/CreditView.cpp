#include "CreditView.h"

#include "ui_CreditView.h"

const int hight = 500;
const int wide = 750;
namespace s21 {
CreditView::CreditView(QWidget *parent)
    : QDialog(parent), ui(new Ui::CreditView) {
  ui->setupUi(this);
  QPalette pal = QPalette();
  pal.setColor(QPalette::Window, QColor(231, 238, 240));
  this->setPalette(pal);
  this->setFixedSize(QSize(wide, hight));
  connect(ui->count, SIGNAL(clicked()), this, SLOT(countClicked()));
}

CreditView::~CreditView() { delete ui; }

void CreditView::fixDuration(int &durType, int &dur) {
  if (durType == -2) {
    std::cout << durType << std::endl;
    dur *= 12;
  }
}

std::pair<double, double> CreditView::annuityPayment(double sum, double &bid,
                                                     int &duration) {
  double percForMounth = controller.getPercForMounth(bid);
  double monthlyPay =
      controller.getMounthlyPayAnn(percForMounth, duration, sum);

  for (int i = 0; i < ui->table->rowCount(); ++i) {
    auto temp = controller.creditCalc(sum, monthlyPay, percForMounth);
    std::vector<double> vec = {static_cast<double>(i + 1), monthlyPay,
                               temp.first, temp.second, sum};
    for (int j = 0; j < ui->table->columnCount(); ++j) {
      QTableWidgetItem *it = new QTableWidgetItem;
      if (j == 0)
        it->setText(QString::number(vec[static_cast<size_t>(j)]));
      else
        it->setText(getFormatedString(vec[static_cast<size_t>(j)]));
      ui->table->setItem(i, j, it);
    }
  }

  double fullPayment = controller.getFullPaymentAnn(
      std::ceil(monthlyPay * 100) / 100.0, duration);
  return std::pair<double, double>(monthlyPay, fullPayment);
}

std::pair<double, double> CreditView::differentiatedPayment(double sum,
                                                            double &bid,
                                                            int &dur) {
  double perc = controller.getPercForMounth(bid);
  double payForMainDuty = controller.getPayForMainDuty(sum, dur);
  double monthlyPay = 0;
  double fullPayment = 0,
         firstPay = controller.getMounthlyPayDiff(payForMainDuty, sum, perc);
  for (int i = 0; i < ui->table->rowCount(); ++i) {
    monthlyPay = controller.getMounthlyPayDiff(payForMainDuty, sum, perc);
    fullPayment += monthlyPay;
    sum -= payForMainDuty;
    std::vector<double> vec = {static_cast<double>(i + 1), monthlyPay,
                               payForMainDuty, (monthlyPay - payForMainDuty),
                               sum};
    for (int j = 0; j < ui->table->columnCount(); ++j) {
      QTableWidgetItem *it = new QTableWidgetItem;
      if (j == 0)
        it->setText(QString::number(vec[static_cast<size_t>(j)]));
      else
        it->setText(getFormatedString(vec[static_cast<size_t>(j)]));
      ui->table->setItem(i, j, it);
    }
  }

  ui->monthlyPay->setText(getFormatedString(firstPay) + " ... " +
                          getFormatedString(monthlyPay));
  return std::pair<double, double>(monthlyPay, fullPayment);
}

void CreditView::createTableView(int dur) {
  QStringList horHeaderList({"Номер платежа", "Сумма платежа", "Основной долг",
                             "Проценты", "Остаток долга"});
  ui->table->setColumnCount(static_cast<int>(horHeaderList.size()));
  ui->table->horizontalHeader()->setVisible(true);
  ui->table->setHorizontalHeaderLabels(horHeaderList);
  ui->table->setRowCount(dur);
  ui->table->verticalHeader()->hide();
}

QString CreditView::getFormatedString(double n) {
  return QString::number(n, 'f', 2);
}

void CreditView::countClicked() {
  this->setFixedSize(wide + 500, hight);
  double sum = ui->creditSum->value();
  int durType = ui->durationType->checkedId();
  int dur = ui->duration->value();
  double bid = ui->bid->value();
  QString payType = ui->payType->checkedButton()->text();
  fixDuration(durType, dur);
  // qDebug() << "HERE";

  createTableView(dur);
  // qDebug() << "HERE";

  double monthlyPay, fullPayment;
  if (payType == "Аннуитетный") {
    auto item = annuityPayment(sum, bid, dur);  // gets monthlyPay/fullPayment
    monthlyPay = item.first;
    fullPayment = item.second;

    ui->monthlyPay->setText(getFormatedString(monthlyPay));
  } else {
    auto item = differentiatedPayment(sum, bid, dur);
    fullPayment = item.second;
  }
  ui->fullSum->setText(getFormatedString(fullPayment));
  double overpay = controller.getOverpay(fullPayment, sum);
  ui->overpayment->setText(getFormatedString(overpay));
}

void CreditView::on_table_clicked(const QModelIndex &index) {
  ui->table->selectRow(index.row());
}
}
