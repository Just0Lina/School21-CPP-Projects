#include "widgetMaze.h"

#include "ui_widgetMaze.h"

WidgetMaze::WidgetMaze(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::widgetMaze),
      way_(QSize(500, 500), QImage::Format_ARGB32),
      area_(QSize(500, 500), QImage::Format_ARGB32) {}

WidgetMaze::~WidgetMaze() { delete ui; }

void WidgetMaze::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);
  int widthMaze = controller.GetMaze().GetWidth(),
      heightMaze = controller.GetMaze().GetHeight();
  QRect source(0, 0, widthCell * widthMaze, heightCell * heightMaze);
  QRect target(0, 0, 500, 500);
  if (source.width() < target.width()) {
    deltaX = target.width() - source.width();
  } else {
    deltaX = source.width() - target.width();
  }
  if (source.height() < target.height()) {
    deltaY = target.height() - source.height();
  } else {
    deltaY = source.height() - target.height();
  }
  painter.translate(deltaX / 2, deltaY / 2);

  painter.drawImage(source, way_, source);
  painter.drawImage(source, area_, source);
}

void WidgetMaze::DrawAmaze() {
  ClearIm(area_);
  ClearIm(way_);

  QPainter painter;
  painter.begin(&area_);
  QPen pen;
  pen.setColor(QRgb(0xFF4fbcff));
  pen.setWidth(2);
  painter.setPen(pen);
  ChangeCellSize();
  int widthMaze = controller.GetMaze().GetWidth(),
      heightMaze = controller.GetMaze().GetHeight();
  painter.drawLine(0, 0, widthCell * widthMaze, 0);
  painter.drawLine(0, 0, 0, heightMaze * heightCell);
  auto mazeMatrix = controller.GetMaze().GetMaze();
  for (int i = 0; i < heightMaze; ++i) {
    for (int j = 0; j < widthMaze; ++j) {
      if (mazeMatrix[static_cast<size_t>(i)][static_cast<size_t>(j)].down_) {
        painter.drawLine(j * widthCell, (i + 1) * heightCell,
                         (j + 1) * widthCell, (i + 1) * heightCell);
      }
      if (mazeMatrix[static_cast<size_t>(i)][static_cast<size_t>(j)].right_) {
        painter.drawLine((j + 1) * widthCell, i * heightCell,
                         (j + 1) * widthCell, (i + 1) * heightCell);
      }
    }
  }
  update();
  painter.end();
}

void WidgetMaze::mousePressEvent(QMouseEvent *event) {
  Q_UNUSED(event);
  ClearIm(way_);
  if (event->button() == Qt::LeftButton) {
    QPoint start_ = event->pos();
    startPoint_.second = ((start_.x() - deltaX / 2) / widthCell);
    startPoint_.first = ((start_.y() - deltaY / 2) / heightCell);
    //    qDebug() << "START" << startPoint_.first << startPoint_.second;
    if (IsCorrect(startPoint_)) leftButton_ = true;
  } else if (event->button() == Qt::RightButton) {
    QPoint end_ = event->pos();
    endPoint_.second = (end_.x() - deltaX / 2) / widthCell;
    endPoint_.first = (end_.y() - deltaY / 2) / heightCell;
    if (IsCorrect(endPoint_)) rightButton_ = true;
    //    qDebug() <<"END" <<  endPoint_.first << endPoint_.second;
  }

  if (leftButton_ == true && rightButton_ == true) {
    DrawPath();
    leftButton_ = false;
    rightButton_ = false;
  }
  update();
}

void WidgetMaze::DrawPath() {
  QPainter painter;
  painter.begin(&way_);
  controller.GetMaze().OverMaze(startPoint_, endPoint_);
  s21::Maze maze = controller.GetMaze();
  QPen pen;
  pen.setColor(QRgb(0xFFFFFAFF));
  pen.setWidth(2);
  painter.setPen(pen);

  bool turn = false;
  int sW = 0, sH = 0, eW = 0, eH = 0;
  while (!maze.GetPathFinder().empty() &&
         maze.GetPathFinder().back() != startPoint_) {
    if (turn == false) {
      sW = maze.GetPathFinder().back().second;
      sH = maze.GetPathFinder().back().first;
    }
    maze.GetPathFinder().pop_back();

    eW = maze.GetPathFinder().back().second;
    eH = maze.GetPathFinder().back().first;

    if (maze.GetMaze()[sH][sW].path_ - maze.GetMaze()[eH][eW].path_ == 1 ||
        maze.GetMaze()[eH][eW].path_ == -1) {
      turn = false;

      painter.drawLine(sW * widthCell + (widthCell * 0.5),
                       sH * heightCell + (heightCell * 0.5),
                       eW * widthCell + (widthCell * 0.5),
                       eH * heightCell + (heightCell * 0.5));
    } else {
      turn = true;
    }
  }
  painter.end();
}

void WidgetMaze::ClearIm(QImage &image) {
  image.fill(QColor(0, 0, 0, 0));
  update();
}

void WidgetMaze::ChangeCellSize() {
  int widthMaze = controller.GetMaze().GetWidth(),
      heightMaze = controller.GetMaze().GetHeight();
  int widgetSize = 500;
  if (widthMaze != 0 && heightMaze != 0) {
    int hightCorr = widgetSize % heightMaze;
    int widthCorr = widgetSize % widthMaze;
    heightCell = (widgetSize - hightCorr) / heightMaze;
    widthCell = (widgetSize - widthCorr) / widthMaze;
    if (heightCell < widthCell) {
      widthCell = heightCell;
    } else {
      heightCell = widthCell;
    }
  } else {
    widthCell = widgetSize / 10;
    heightCell = widgetSize / 10;
  }
}
