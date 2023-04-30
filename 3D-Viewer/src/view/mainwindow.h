#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qgifimage.h>

#include <QColorDialog>
#include <QDebug>
#include <QDesktopServices>
#include <QFileDialog>
#include <QMainWindow>
#include <QMovie>
#include <QPixmap>
#include <QSettings>
#include <QString>
#include <QTimer>
#include <QUrl>

#include "controller/controller.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class StyleHelper {
 public:
  StyleHelper() = default;
  ~StyleHelper() = default;

  static QString getStyleButton1() {
    return "QPushButton {font: bold; font-size: 20px;"
           "background-color: #DBE2EF; color: #112D4E; "
           "border: 1px solid #112D4E}"
           "QPushButton:pressed {background-color: #BBCAE4}";
  }
};

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:

  void on_buttonChoseFile_clicked();

  void on_sliderScale_valueChanged(int value);
  void on_buttonScale_clicked();

  void on_buttonMove_clicked();

  void on_sliderXMove_valueChanged(int value);
  void on_sliderYMove_valueChanged(int value);
  void on_sliderZMove_valueChanged(int value);

  void on_buttonRotate_clicked();

  void on_sliderXRotation_valueChanged(int value);
  void on_sliderYRotation_valueChanged(int value);
  void on_sliderZRotation_valueChanged(int value);

  void on_buttonColorChangeFace_clicked();
  void on_buttonColorChangeVertex_clicked();
  void on_buttonColorChangeBack_clicked();

  void on_buttonOurHouse_clicked();

  void on_buttonLineChange_clicked();
  void on_buttonVertexChange_clicked();

  void on_comboBox_vertex_currentIndexChanged(int index);
  void on_comboBox_strip_currentIndexChanged(int index);
  void on_comboBox_proection_currentIndexChanged(int index);

  void on_buttonScreenshot_clicked();
  void buttonBMP();
  void buttonJPG();
  void on_buttonGif_clicked();
  void startGif();
  void recordingGif();
  void saveGif();
  void saveSettings();
  void loadSettings();
  void on_originSettings_clicked();
  void deletePush();

 private:
  Ui::MainWindow *ui;
  Controller &controller{Controller::getInstance()};

  QDate date;
  QTime time;
  QTimer *timer;
  int flag = 0, flag1 = 0;
  QString presentTime, presentDate, file, filename, vCount1, fCount1;
  QPushButton *butBMP, *butJPG, *start, *stop;
  QGifImage *gif;
  QImage *img;
  QSettings *settings;
  QColor *colorBack, *lineColor, *verColor;
};
}  // namespace s21

#endif  // MAINWINDOW_H
