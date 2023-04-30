#include "customsettings.h"

#include "ui_customsettings.h"

CustomSettings::CustomSettings(int row, int col, QWidget* parent)
    : QDialog(parent), ui(new Ui::CustomSettings), row_(row), col_(col) {
  QGridLayout* layout = new QGridLayout(this);
  matrix.resize(row);
  for (int i = 0; i < row; ++i) {
    matrix[i].resize(col);
  }
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      QSpinBox* newButton = new QSpinBox(this);
      newButton->setRange(-10000, 10000);
      newButton->QAbstractSpinBox::setButtonSymbols(
          QAbstractSpinBox::NoButtons);
      newButton->setValue(1);
      list.append(newButton);
      layout->addWidget(newButton, i, j);
      newButton->setStyleSheet(
          "QSpinBox {\n	border: 1px solid #F4F4F4;\n	background-color: "
          "#212121;\n	color: #F4F4F4;\n}\n\nQSpinBox:hover {\n     "
          "background-color: #e0c3fc;\n	color: "
          "#212121;\n }");
      // newButton->setText("Apply settings");
      // qDebug() << i << " " << j;
    }
  }
  setLayout(layout);
  //  QPushButton* newButton = new QPushButton(this);
  //  newButton->setText("Apply settings");
  //  connect(newButton, &QPushButton::clicked, this, &CustomSettings::Apply);
  //  layout->addWidget(newButton, row, 0, row, col);
  //  layout->setSpacing(0);
  //  newButton->setStyleSheet(
  //      "QPushButton {\n	border: 1px solid #F4F4F4;\n
  //      background-color: "
  //      "#212121;\n	color: #F4F4F4;\n}\n\nQPushButton:pressed {\n     "
  //      "background-color: #F4F4F4;\n	color: #9e2a2b;\n "
  //      "}\n\nQPushButton:hover {\n     background-color: #e0c3fc;\n	color: "
  //      "#212121;\n }");
  ui->setupUi(this);
}

CustomSettings::~CustomSettings() { delete ui; }

void CustomSettings::on_apply_btn_clicked() {
  int r = 0, c = 0;
  for (auto& el : list) {
    matrix[r][c] = el->value();
    if (c < col_ - 1)
      ++c;
    else {
      ++r;
      c = 0;
    }
  }
  close();
}
