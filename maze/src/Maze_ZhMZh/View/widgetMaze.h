#ifndef WIDGETMAZE_H
#define WIDGETMAZE_H

#include <QFileDialog>
#include <QMouseEvent>
#include <QPainter>
#include <QWidget>

#include "Controller/controller.h"

namespace Ui {
class widgetMaze;
}

class WidgetMaze : public QWidget {
  Q_OBJECT

 public:
  explicit WidgetMaze(QWidget *parent = nullptr);
  ~WidgetMaze();

  void paintEvent(QPaintEvent *) override;
  void mousePressEvent(QMouseEvent *event) override;
  void DrawAmaze();
  void DrawPath();
  void ClearIm(QImage &image);
  void ChangeCellSize();
  bool IsCorrect(std::pair<int, int> p) {
    int widthMaze = controller.GetMaze().GetWidth(),
        heightMaze = controller.GetMaze().GetHeight();
    if (p.first < heightMaze && p.second < widthMaze) {
      return true;
    }
    return false;
  }

  Controller &controller{Controller::getInstance()};

 private:
  Ui::widgetMaze *ui;

  double heightCell;
  double widthCell;

  std::pair<int, int> startPoint_;
  std::pair<int, int> endPoint_;
  bool leftButton_;
  bool rightButton_;
  int deltaX, deltaY;

  QImage way_;
  QImage area_;
};

#endif  // WIDGETMAZE_H
