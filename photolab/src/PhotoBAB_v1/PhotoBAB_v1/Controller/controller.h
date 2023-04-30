#ifndef SRC_PHOTOBAB_CONTROLLER_CONTROLLER_H_
#define SRC_PHOTOBAB_CONTROLLER_CONTROLLER_H_

#include <iostream>

#include "../Model/model.h"
namespace s21 {
class Controller {
 public:
  QImage Grayscale(const QImage &img_) { return model_.Grayscale(img_); }
  QImage Negative(const QImage &img_) { return model_.Negative(img_); }
  QImage Toning(const QImage &img_, QColor col) {
    return model_.Toning(img_, col);
  }
  QImage Emboss(const QImage &img_) { return model_.Emboss(img_); }
  QImage Sharpen(const QImage &img_) { return model_.Sharpen(img_); }
  QImage Boxblur(const QImage &img_) { return model_.Boxblur(img_); }
  QImage Gaussian(const QImage &img_) { return model_.Gaussian(img_); }
  QImage Laplacian(const QImage &img_) { return model_.Laplacian(img_); }
  QImage SobelLeft(const QImage &img_) { return model_.SobelLeft(img_); }
  QImage SobelRight(const QImage &img_) { return model_.SobelRight(img_); }
  QImage SobelBoth(const QImage &img_) { return model_.SobelBoth(img_); }
  QImage CustomSettings(const QImage &img_, const Matrix &m) {
    return model_.CustomSettings(img_, m);
  }
  QImage Brightness(const QImage &img_, int val) {
    return model_.Brightness(img_, val);
  }
  QImage Contrast(const QImage &img_, int val) {
    return model_.Contrast(img_, val);
  }
  QImage HSL(const QImage &img_, QColor inputHSL_) {
    return model_.HSL(img_, inputHSL_);
  }
  QImage HSV(const QImage &img_, QColor inputHSV_) {
    return model_.HSV(img_, inputHSV_);
  }

 private:
  Model model_;

};  // class Controller
}  // namespace s21

#endif  // SRC_PHOTOBAB_CONTROLLER_CONTROLLER_H_
