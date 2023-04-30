#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setDefaultColor() {
  ui->pictureField->setStyleSheet(
      "QLabel { background-color: #212121; color: #F4F4F4; border-top: 2px "
      "solid #F4F4F4; border-right: 2px solid #F4F4F4; }");
}

void MainWindow::showPic(const QImage img_) {
  ui->pictureField->setPixmap(QPixmap::fromImage(img_));
}

// BUTTONS CLICKED

void MainWindow::on_button_load_clicked() {
  file_ = QFileDialog::getOpenFileName(this, "Open a file", QDir::homePath(),
                                       "bmp (*.bmp)");
  if (!file_.isEmpty()) {
    fileName = file_.split('/');
    name = fileName.last();
    ui->label_filename->setText(name.toUpper());

    width_ = ui->pictureField->width();
    height_ = ui->pictureField->height();
    image_ =
        QImage(file_).scaled(width_ - 60, height_ - 60, Qt::KeepAspectRatio);

    showPic(image_);
  }
}

void MainWindow::on_button_save_clicked() {
  QString fileSave_ =
      QFileDialog::getSaveFileName(this, "Save a file", QDir::homePath());
  fake_.save(fileSave_ + ".bmp", "BMP");
}

void MainWindow::on_button_grayscale_clicked() {
  image_ = controller_.Grayscale(image_);
  fake_ = image_;
  showPic(image_);
}

void MainWindow::on_button_negative_clicked() {
  image_ = controller_.Negative(image_);
  fake_ = image_;
  showPic(image_);
}

void MainWindow::on_button_default_clicked() {
  image_ = QImage(file_).scaled(width_ - 60, height_ - 60, Qt::KeepAspectRatio);
  showPic(image_);
  setDefaultColor();

  ui->slider_bright->setValue(0);
  ui->spin_bright->setValue(0);
  ui->slider_contrast->setValue(0);
  ui->spin_contrast->setValue(0);
  ui->slider_hue_hsl->setValue(0);
  ui->spin_hue_hsl->setValue(0);
  ui->slider_saturation_hsl->setValue(1);
  ui->spin_saturation_hsl->setValue(1);
  ui->slider_lightness->setValue(127);
  ui->spin_lightness->setValue(127);
  ui->slider_hue_hsv->setValue(0);
  ui->spin_hue_hsv->setValue(0);
  ui->slider_saturation_hsv->setValue(1);
  ui->spin_saturation_hsv->setValue(1);
  ui->slider_value->setValue(127);
  ui->spin_value->setValue(127);
}

void MainWindow::on_button_toning_clicked() {
  QColor newColor = QColorDialog::getColor();
  image_ = controller_.Toning(image_, newColor);
  fake_ = image_;
  showPic(image_);
}

void MainWindow::on_button_emboss_clicked() {
  image_ = controller_.Emboss(image_);
  fake_ = image_;
  showPic(image_);
}

void MainWindow::on_button_sharpen_clicked() {
  image_ = controller_.Sharpen(image_);
  fake_ = image_;
  showPic(image_);
}

void MainWindow::on_button_boxblur_clicked() {
  image_ = controller_.Boxblur(image_);
  fake_ = image_;
  showPic(image_);
}

void MainWindow::on_button_gaussian_clicked() {
  image_ = controller_.Gaussian(image_);
  fake_ = image_;
  showPic(image_);
}

void MainWindow::on_button_laplacian_clicked() {
  image_ = controller_.Laplacian(image_);
  fake_ = image_;
  showPic(image_);
}

void MainWindow::on_botton_sobel_left_clicked() {
  image_ = controller_.SobelLeft(image_);
  fake_ = image_;
  showPic(image_);
}

void MainWindow::on_button_sobel_right_clicked() {
  image_ = controller_.SobelRight(image_);
  fake_ = image_;
  showPic(image_);
}

void MainWindow::on_button_sobel_both_clicked() {
  image_ = controller_.SobelBoth(image_);
  fake_ = image_;
  showPic(image_);
}

void MainWindow::on_button_custom_clicked() {
  CustomSettings cusSet(ui->sizeMatrixRow->value(),
                        ui->sizeMatrixColumn->value());
  cusSet.setModal(true);
  cusSet.exec();
  image_ = controller_.CustomSettings(image_, cusSet.GetMatrix());
  fake_ = image_;
  showPic(image_);
}

// BUTTONS PRESSED
void MainWindow::on_button_grayscale_pressed() {
  ui->pictureField->setStyleSheet(
      "QLabel { background-color : #caf0f8; color: #F4F4F4; border-top: 2px "
      "solid #F4F4F4; border-right: 2px solid #F4F4F4;}");
}

void MainWindow::on_button_negative_pressed() {
  ui->pictureField->setStyleSheet(
      "QLabel { background-color : #ade8f4; color: #F4F4F4; border-top: 2px "
      "solid #F4F4F4; border-right: 2px solid #F4F4F4;}");
}

void MainWindow::on_button_toning_pressed() {
  ui->pictureField->setStyleSheet(
      "QLabel {  background-color: #90e0ef; color: #F4F4F4; border-top: 2px "
      "solid #F4F4F4; border-right: 2px solid #F4F4F4;}");
}

void MainWindow::on_button_emboss_pressed() {
  ui->pictureField->setStyleSheet(
      "QLabel {  background-color: #8187dc; color: #F4F4F4; border-top: 2px "
      "solid #F4F4F4; border-right: 2px solid #F4F4F4;}");
}

void MainWindow::on_button_sharpen_pressed() {
  ui->pictureField->setStyleSheet(
      "QLabel {  background-color: #8e94f2; color: #F4F4F4; border-top: 2px "
      "solid #F4F4F4; border-right: 2px solid #F4F4F4;}");
}

void MainWindow::on_button_boxblur_pressed() {
  ui->pictureField->setStyleSheet(
      "QLabel {  background-color: #9fa0ff; color: #F4F4F4; border-top: 2px "
      "solid #F4F4F4; border-right: 2px solid #F4F4F4;}");
}

void MainWindow::on_button_gaussian_pressed() {
  ui->pictureField->setStyleSheet(
      "QLabel {  background-color: #ada7ff; color: #F4F4F4; border-top: 2px "
      "solid #F4F4F4; border-right: 2px solid #F4F4F4;}");
}

void MainWindow::on_button_laplacian_pressed() {
  ui->pictureField->setStyleSheet(
      "QLabel {  background-color: #bbadff; color: #F4F4F4; border-top: 2px "
      "solid #F4F4F4; border-right: 2px solid #F4F4F4;}");
}

void MainWindow::on_botton_sobel_left_pressed() {
  ui->pictureField->setStyleSheet(
      "QLabel {  background-color: #cbb2fe; color: #F4F4F4; border-top: 2px "
      "solid #F4F4F4; border-right: 2px solid #F4F4F4;}");
}

void MainWindow::on_button_sobel_right_pressed() {
  ui->pictureField->setStyleSheet(
      "QLabel {  background-color: #dab6fc; color: #F4F4F4; border-top: 2px "
      "solid #F4F4F4; border-right: 2px solid #F4F4F4;}");
}

void MainWindow::on_button_sobel_both_pressed() {
  ui->pictureField->setStyleSheet(
      "QLabel {  background-color: #ddbdfc; color: #F4F4F4; border-top: 2px "
      "solid #F4F4F4; border-right: 2px solid #F4F4F4;}");
}

void MainWindow::on_button_custom_pressed() {
  ui->pictureField->setStyleSheet(
      "QLabel {  background-color: #e0c3fc; color: #F4F4F4; border-top: 2px "
      "solid #F4F4F4; border-right: 2px solid #F4F4F4;}");
}

void MainWindow::on_button_bright_pressed() {
  ui->pictureField->setStyleSheet(
      "QLabel {  background-color: #48cae4; color: #F4F4F4; border-top: 2px "
      "solid #F4F4F4; border-right: 2px solid #F4F4F4;}");
}

void MainWindow::on_button_contrast_pressed() {
  ui->pictureField->setStyleSheet(
      "QLabel {  background-color: #00b4d8; color: #F4F4F4; border-top: 2px "
      "solid #F4F4F4; border-right: 2px solid #F4F4F4;}");
}

void MainWindow::on_button_hsl_pressed() {
  ui->pictureField->setStyleSheet(
      "QLabel {  background-color: #64b5f6; color: #F4F4F4; border-top: 2px "
      "solid #F4F4F4; border-right: 2px solid #F4F4F4;}");
}

void MainWindow::on_button_hsv_pressed() {
  ui->pictureField->setStyleSheet(
      "QLabel {  background-color: #1565c0; color: #F4F4F4; border-top: 2px "
      "solid #F4F4F4; border-right: 2px solid #F4F4F4;}");
}

// BUTTONS RELEASED
void MainWindow::on_button_grayscale_released() { setDefaultColor(); }

void MainWindow::on_button_negative_released() { setDefaultColor(); }

void MainWindow::on_button_toning_released() { setDefaultColor(); }

void MainWindow::on_button_emboss_released() { setDefaultColor(); }

void MainWindow::on_button_sharpen_released() { setDefaultColor(); }

void MainWindow::on_button_boxblur_released() { setDefaultColor(); }

void MainWindow::on_button_gaussian_released() { setDefaultColor(); }

void MainWindow::on_button_laplacian_released() { setDefaultColor(); }

void MainWindow::on_botton_sobel_left_released() { setDefaultColor(); }

void MainWindow::on_button_sobel_right_released() { setDefaultColor(); }

void MainWindow::on_button_sobel_both_released() { setDefaultColor(); }

void MainWindow::on_button_custom_released() { setDefaultColor(); }

void MainWindow::on_button_bright_released() { setDefaultColor(); }

void MainWindow::on_button_contrast_released() { setDefaultColor(); }

void MainWindow::on_button_hsl_released() { setDefaultColor(); }

void MainWindow::on_button_hsv_released() { setDefaultColor(); }

void MainWindow::on_slider_bright_valueChanged(int value) {
  ui->spin_bright->setValue(value);
}

void MainWindow::on_slider_contrast_valueChanged(int value) {
  ui->spin_contrast->setValue(value);
}

void MainWindow::on_button_bright_clicked() {
  int val = ui->spin_bright->value();
  ui->slider_bright->setValue(val);

  fake_ = controller_.Brightness(image_, val);
  showPic(fake_);
}

void MainWindow::on_button_contrast_clicked() {
  int val = ui->spin_contrast->value();
  ui->slider_contrast->setValue(val);

  fake_ = controller_.Contrast(image_, val);
  showPic(fake_);
}

void MainWindow::on_slider_bright_sliderReleased() {
  int val = ui->spin_bright->value();
  ui->slider_bright->setValue(val);

  fake_ = controller_.Brightness(image_, val);
  showPic(fake_);
}

void MainWindow::on_slider_contrast_sliderReleased() {
  int val = ui->spin_contrast->value();
  ui->slider_contrast->setValue(val);

  fake_ = controller_.Contrast(image_, val);
  showPic(fake_);
}

// HSL

void MainWindow::on_slider_hue_sliderReleased() {
  int val = ui->spin_hue_hsl->value();
  ui->spin_hue_hsl->setValue(val);

  int hue_ = ui->spin_hue_hsl->value();
  int saturation_ = ui->spin_saturation_hsl->value();
  int lightness_ = ui->spin_lightness->value();
  int alpha = 255;

  QColor inputHSL_ = QColor::fromHsl(hue_, saturation_, lightness_, alpha);
  fake_ = controller_.HSL(image_, inputHSL_);
  showPic(fake_);
}

void MainWindow::on_button_hsl_clicked() {
  int hue_ = ui->spin_hue_hsl->value();
  int saturation_ = ui->spin_saturation_hsl->value();
  int lightness_ = ui->spin_lightness->value();

  ui->slider_hue_hsl->setValue(hue_);
  ui->slider_saturation_hsl->setValue(saturation_);
  ui->slider_lightness->setValue(lightness_);

  QColor inputHSL_ = QColor::fromHsl(hue_ % 360, saturation_, lightness_);

  fake_ = controller_.HSL(image_, inputHSL_);
  showPic(fake_);
}

void MainWindow::on_slider_hue_hsl_sliderReleased() {
  int val = ui->spin_hue_hsl->value();
  ui->slider_hue_hsl->setValue(val);
}

void MainWindow::on_slider_hue_hsl_valueChanged(int value) {
  ui->spin_hue_hsl->setValue(value);
}

void MainWindow::on_slider_saturation_hsl_sliderReleased() {
  int val = ui->spin_saturation_hsl->value();
  ui->slider_saturation_hsl->setValue(val);
}

void MainWindow::on_slider_saturation_hsl_valueChanged(int value) {
  ui->spin_saturation_hsl->setValue(value);
}

void MainWindow::on_slider_lightness_sliderReleased() {
  int val = ui->spin_lightness->value();
  ui->slider_lightness->setValue(val);
}

void MainWindow::on_slider_lightness_valueChanged(int value) {
  ui->spin_lightness->setValue(value);
}

// HSV

void MainWindow::on_slider_hue_hsv_sliderReleased() {
  int val = ui->spin_hue_hsv->value();
  ui->slider_hue_hsv->setValue(val);
}

void MainWindow::on_slider_hue_hsv_valueChanged(int value) {
  ui->spin_hue_hsv->setValue(value);
}

void MainWindow::on_slider_saturation_hsv_sliderReleased() {
  int val = ui->spin_saturation_hsv->value();
  ui->slider_saturation_hsv->setValue(val);
}

void MainWindow::on_slider_saturation_hsv_valueChanged(int value) {
  ui->spin_saturation_hsv->setValue(value);
}

void MainWindow::on_slider_value_sliderReleased() {
  int val = ui->spin_value->value();
  ui->slider_value->setValue(val);
}

void MainWindow::on_slider_value_valueChanged(int value) {
  ui->spin_value->setValue(value);
}

void MainWindow::on_button_hsv_clicked() {
  int hue_ = ui->spin_hue_hsv->value();
  int saturation_ = ui->spin_saturation_hsv->value();
  int value_ = ui->spin_value->value();

  ui->slider_hue_hsv->setValue(hue_);
  ui->slider_saturation_hsv->setValue(saturation_);
  ui->slider_value->setValue(value_);

  QColor inputHSV_ = QColor::fromHsv(hue_ % 360, saturation_, value_);

  fake_ = controller_.HSV(image_, inputHSV_);
  showPic(fake_);
}
