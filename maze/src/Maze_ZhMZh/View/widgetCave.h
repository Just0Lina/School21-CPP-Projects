#ifndef WIDGETCAVE_H
#define WIDGETCAVE_H

#include <QPainter>
#include <QWidget>

#include "Controller/controller.h"

namespace Ui {
class widgetCave;
}

class WidgetCave : public QWidget {
  Q_OBJECT

 public:
  explicit WidgetCave(QWidget *parent = nullptr);
  ~WidgetCave() override;
  void paintEvent(QPaintEvent *) override;
  Controller &controller{Controller::getInstance()};

 private:
  Ui::widgetCave *ui;
};

#endif  // WIDGETCAVE_H
