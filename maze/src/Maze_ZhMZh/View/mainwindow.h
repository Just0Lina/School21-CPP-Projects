#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QTimer>

#include "../Controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  QTimer *timer = new QTimer(this);
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_loadCave_clicked();
  void on_loadMaze_clicked();

  void on_generateMaze_clicked();
  void on_generateCave_clicked();
  void UpdateCave();

 private:
  Ui::MainWindow *ui;
  Controller &controller{Controller::getInstance()};

 private slots:
  void timer_image_function();

  void on_stepMode_clicked();
  void on_autoMode_clicked();
  void on_death_valueChanged(int arg1);
  void on_birth_valueChanged(int arg1);
  void on_nextStep_clicked();
  void on_timer_valueChanged(int arg1);
};
#endif  // MAINWINDOW_H
