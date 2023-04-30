#ifndef SRC_PHOTOBAB_MODEL_H_
#define SRC_PHOTOBAB_MODEL_H_

#include <QImage>
#include <vector>

namespace s21 {
using Matrix = std::vector<std::vector<double>>;

class Model {
 public:
  Model() = default;
  ~Model() = default;

  QImage Grayscale(const QImage &img);
  QImage Negative(const QImage &img_);
  QImage Toning(const QImage &img_, QColor col);

  QImage Emboss(const QImage &img_);
  QImage Sharpen(const QImage &img_);
  QImage Boxblur(const QImage &img_);
  QImage Gaussian(const QImage &img_);
  QImage Laplacian(const QImage &img_);
  QImage SobelBoth(const QImage &img_);
  QImage SobelLeft(const QImage &img_);
  QImage SobelRight(const QImage &img_);
  QImage CustomSettings(const QImage &img_, Matrix matrix);

  QImage Brightness(const QImage &img_, int val);
  QImage Contrast(const QImage &img_, int val);

  QImage Convolution(const QImage &img_,
                     std::vector<std::vector<double>> matrix_);

  QImage HSL(const QImage &img_, QColor inputHSL_);
  QImage HSV(const QImage &img_, QColor inputHSV_);

 private:
};  // class Model
}  // namespace s21
#endif  // SRC_PHOTOBAB_MODEL_H_
