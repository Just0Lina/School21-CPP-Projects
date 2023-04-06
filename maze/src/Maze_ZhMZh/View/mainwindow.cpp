#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->nextStep->hide();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_generateCave_clicked() {
  int height = ui->heightCave->value(), width = ui->widthCave->value();
  int birth = ui->birth->value(), death = ui->death->value();
  ui->widgetCave->controller.GenerateObject(Type::Cave, 4, height, width, birth,
                                            death);
  UpdateCave();
  update();
}

void MainWindow::on_generateMaze_clicked() {
  int height = ui->heightMaze->value(), width = ui->widthMaze->value();
  controller.GenerateObject(Type::Maze, 2, height, width);
  ui->widgetMaze->DrawAmaze();
  update();
}

void MainWindow::UpdateCave() {
  if (ui->autoMode->isChecked()) {
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_image_function()));
    timer->start(ui->timer->value());
  }
}

void MainWindow::on_loadCave_clicked() {
  QString filename = QFileDialog::getOpenFileName(
      this, "Open a file", QDir::homePath(), "txt (*.txt)");
  std::string filename_ = filename.toStdString();
  controller.LoadObject(Type::Cave, filename_, ui->birth->value(),
                        ui->death->value());
  ui->heightCave->setValue(controller.GetCave().GetHeight());
  ui->widthCave->setValue(controller.GetCave().GetWidth());
  UpdateCave();
//  update();
}

void MainWindow::on_loadMaze_clicked() {
  QString filename = QFileDialog::getOpenFileName(
      this, "Open a file", QDir::homePath(), "txt (*.txt)");
  std::string filename_ = filename.toStdString();
  controller.LoadObject(Type::Maze, filename_);
  int height = controller.GetMaze().GetHeight(),
      width = controller.GetMaze().GetWidth();
  ui->heightMaze->setValue(height);
  ui->widthMaze->setValue(width);
  if (height != 0 && width != 0) {
    ui->widgetMaze->DrawAmaze();
    update();
  }
}

void MainWindow::timer_image_function() {
  if (controller.GetCave().UpdateScene()) {
  }
  update();
}

void MainWindow::on_stepMode_clicked() {
  ui->timer->hide();
  ui->nextStep->show();
  timer->stop();
}

void MainWindow::on_autoMode_clicked() {
  ui->nextStep->hide();
  ui->timer->show();
  timer->start(ui->timer->value());
}

void MainWindow::on_death_valueChanged(int arg1) {
  controller.GetCave().SetDeath(arg1);
}

void MainWindow::on_birth_valueChanged(int arg1) {
  controller.GetCave().SetBirth(arg1);
}

void MainWindow::on_nextStep_clicked() {
  if (controller.GetCave().UpdateScene()) {
  }
  update();
}

void MainWindow::on_timer_valueChanged(int arg1) { timer->start(arg1); }
