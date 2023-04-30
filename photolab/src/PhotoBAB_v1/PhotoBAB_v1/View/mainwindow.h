#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>

#include "../Controller/controller.h"
#include "customsettings.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:

  void on_button_load_clicked();
  void on_button_grayscale_clicked();
  void on_button_negative_pressed();
  void on_button_default_clicked();
  void on_button_toning_clicked();
  void on_button_emboss_clicked();
  void on_button_sharpen_clicked();
  void on_button_boxblur_clicked();
  void on_button_gaussian_clicked();
  void on_button_laplacian_clicked();
  void on_botton_sobel_left_clicked();
  void on_button_sobel_right_clicked();
  void on_button_sobel_both_clicked();
  void on_button_custom_clicked();
  void on_button_grayscale_released();
  void on_button_grayscale_pressed();
  void on_button_negative_clicked();
  void on_button_negative_released();
  void on_button_toning_pressed();
  void on_button_toning_released();
  void on_button_emboss_pressed();
  void on_button_emboss_released();

  void setDefaultColor();
  void showPic(const QImage img_);

  void on_button_sharpen_pressed();
  void on_button_boxblur_pressed();
  void on_button_gaussian_pressed();
  void on_botton_sobel_left_pressed();
  void on_button_sobel_right_pressed();
  void on_button_sobel_both_pressed();
  void on_button_custom_pressed();
  void on_button_sharpen_released();
  void on_button_boxblur_released();
  void on_button_gaussian_released();
  void on_button_laplacian_pressed();
  void on_button_laplacian_released();
  void on_botton_sobel_left_released();
  void on_button_sobel_right_released();
  void on_button_sobel_both_released();
  void on_button_custom_released();
  void on_slider_bright_valueChanged(int value);
  void on_slider_contrast_valueChanged(int value);
  void on_button_bright_clicked();
  void on_button_contrast_clicked();
  void on_button_bright_pressed();
  void on_button_bright_released();
  void on_button_contrast_pressed();
  void on_button_contrast_released();
  void on_button_hsl_released();
  void on_button_hsl_pressed();
  void on_button_hsv_pressed();
  void on_button_hsv_released();

  void on_slider_bright_sliderReleased();
  void on_slider_contrast_sliderReleased();
  void on_slider_hue_sliderReleased();
  void on_button_hsl_clicked();
  void on_slider_hue_hsl_sliderReleased();
  void on_slider_hue_hsl_valueChanged(int value);
  void on_slider_saturation_hsl_sliderReleased();
  void on_slider_saturation_hsl_valueChanged(int value);
  void on_slider_lightness_sliderReleased();
  void on_slider_lightness_valueChanged(int value);
  void on_slider_hue_hsv_sliderReleased();
  void on_slider_hue_hsv_valueChanged(int value);
  void on_slider_saturation_hsv_sliderReleased();
  void on_slider_saturation_hsv_valueChanged(int value);
  void on_slider_value_sliderReleased();
  void on_slider_value_valueChanged(int value);

  void on_button_hsv_clicked();

  void on_button_save_clicked();

 private:
  Ui::MainWindow *ui = nullptr;
  s21::Controller controller_;

  QImage image_;
  QImage fake_;
  QString file_;

  QList<QString> fileName;
  QString name;

  int width_ = 0;
  int height_ = 0;
};

//}  // namespace s21
#endif  // MAINWINDOW_H
