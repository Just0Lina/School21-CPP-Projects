#include "widgetCave.h"

#include <QBrush>

#include "ui_widgetCave.h"

WidgetCave::WidgetCave(QWidget *parent)
    : QWidget(parent), ui(new Ui::widgetCave) {
  ui->setupUi(this);
}

WidgetCave::~WidgetCave() { delete ui; }

void WidgetCave::paintEvent(QPaintEvent *) {
  QPainter painter(this);

  QPen pen;
  pen.setColor(QRgb(0xFF4fbcff));
  pen.setWidth(2);
  painter.setPen(pen);
  int widgetSize = 500;
  int width = controller.GetCave().GetWidth(),
      height = controller.GetCave().GetHeight();
  if (width && controller.GetCave().GetHeight()) {
    int widthCell = widgetSize / width;
    int heightCell = widgetSize / height;
    painter.drawRect(0, 0, widthCell * width, heightCell * height);
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        auto caveMatrix = controller.GetCave().GetCave();
        if (caveMatrix[static_cast<size_t>(i)][static_cast<size_t>(j)]) {
          painter.fillRect(j * widthCell, i * heightCell, widthCell, heightCell,
                           QBrush(QRgb(0xFF4fbcff)));
        }
      }
    }
  }
}
