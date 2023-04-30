#include "model.h"

#include <math.h>

#include <iostream>

namespace s21 {

QImage Model::Grayscale(const QImage &img_) {
  QImage temp = img_.convertToFormat(QImage::Format_Grayscale8);
  for (int i = 0; i < temp.width(); ++i) {
    for (int j = 0; j < temp.height(); ++j) {
      int gray = qGray(temp.pixel(i, j));
      temp.setPixel(i, j, qRgb(gray, gray, gray));
    }
  }
  return temp;
}

QImage Model::Negative(const QImage &img_) {
  QImage temp(img_);
  for (int i = 0; i < temp.width(); ++i) {
    for (int j = 0; j < temp.height(); j++) {
      QColor rgb = temp.pixelColor(i, j);
      temp.setPixelColor(
          i, j, qRgb(255 - rgb.red(), 255 - rgb.green(), 255 - rgb.blue()));
    }
  }
  return temp;
}

QImage Model::Toning(const QImage &img_, QColor col) {
  QColor rgb1 = col.toRgb();
  QImage temp(img_);
  for (int i = 0; i < temp.width(); ++i) {
    for (int j = 0; j < temp.height(); ++j) {
      QColor rgb = temp.pixelColor(i, j);
      temp.setPixelColor(
          i, j,
          qRgb(rgb.red() * rgb1.red() / 255, rgb.green() * rgb1.green() / 255,
               rgb.blue() * rgb1.blue() / 255));
    }
  }
  return temp;
}

QImage Model::Emboss(const QImage &img_) {
  Matrix matrix{{-2.0, -1.0, 0.0}, {-1.0, 1.0, 1.0}, {0.0, 1.0, 2.0}};
  return Convolution(img_, matrix);
}

QImage Model::Sharpen(const QImage &img_) {
  Matrix matrix{{-1.0, -1.0, -1.0}, {-1.0, 9.0, -1.0}, {-1.0, -1.0, -1.0}};
  return Convolution(img_, matrix);
}

QImage Model::Boxblur(const QImage &img_) {
  Matrix matrix{{1 / 9.0, 1 / 9.0, 1 / 9.0},
                {1 / 9.0, 1 / 9.0, 1 / 9.0},
                {1 / 9.0, 1 / 9.0, 1 / 9.0}};
  return Convolution(img_, matrix);
}

QImage Model::Gaussian(const QImage &img_) {
  Matrix matrix{{1 / 16.0, 2 / 16.0, 1 / 16.0},
                {2 / 16.0, 4 / 16.0, 2 / 16.0},
                {1 / 16.0, 2 / 16.0, 1 / 16.0}};
  return Convolution(img_, matrix);
}

QImage Model::Laplacian(const QImage &img_) {
  Matrix matrix{{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
  return Convolution(img_, matrix);
}

QImage Model::SobelLeft(const QImage &img_) {
  Matrix matrix{{1, 0, -1}, {2, 0, -2}, {1, 0, -1}};
  return Convolution(img_, matrix);
}

QImage Model::SobelRight(const QImage &img_) {
  Matrix matrix{{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
  return Convolution(img_, matrix);
}

QImage Model::SobelBoth(const QImage &img_) {
  auto tmpImg = SobelLeft(img_);
  return SobelRight(tmpImg);
}

QImage Model::CustomSettings(const QImage &img_, const Matrix m) {
  return Convolution(img_, m);
}

QImage Model::Convolution(const QImage &img_,
                          std::vector<std::vector<double>> matrix_) {
  QImage temp(img_);
  QColor color;
  int matrixWidth = matrix_[0].size();
  int matrixHeight = matrix_.size();
  double red, green, blue;
  int pixPosX, pixPosY;
  for (int i = 0; i < img_.width(); ++i) {
    for (int j = 0; j < img_.height(); ++j) {
      red = 0;
      green = 0;
      blue = 0;

      for (int k = 0; k < matrixWidth; ++k) {
        for (int m = 0; m < matrixHeight; ++m) {
          pixPosX = i + (k - (matrixWidth / 2));
          pixPosY = j + (m - (matrixHeight / 2));
          if ((pixPosX < 0) || (pixPosX >= img_.width()) || (pixPosY < 0) ||
              (pixPosY >= img_.height()))
            continue;

          double kVal = matrix_[m][k];
          color = img_.pixelColor(pixPosX, pixPosY);
          red += color.red() * kVal;
          green += color.green() * kVal;
          blue += color.blue() * kVal;
        }
      }
      red = qBound(0, static_cast<int>(floor(red)), 255);

      green = qBound(0, static_cast<int>(floor(green)), 255);

      blue = qBound(0, static_cast<int>(floor(blue)), 255);

      temp.setPixel(i, j, qRgb(red, green, blue));
    }
  }
  return temp;
}

QImage Model::Brightness(const QImage &img_, int val) {
  QImage temp(img_);
  QRgb color;
  for (int i = 0; i < img_.width(); ++i) {
    for (int j = 0; j < img_.height(); ++j) {
      color = img_.pixel(i, j);
      int r = qBound(0, val + qRed(color), 255);
      int g = qBound(0, val + qGreen(color), 255);
      int b = qBound(0, val + qBlue(color), 255);

      temp.setPixel(i, j, qRgb(r, g, b));
    }
  }
  return temp;
}

QImage Model::Contrast(const QImage &img_, int val) {
  QImage temp(img_);

  for (int i = 0; i < img_.width(); ++i) {
    for (int j = 0; j < img_.height(); ++j) {
      QColor color = img_.pixelColor(i, j);
      double contrast = (100.0 + val) / 100.0;
      int r = qBound(
          0, static_cast<int>(((color.red() - 127) * contrast) + 127), 255);
      int g = qBound(
          0, static_cast<int>(((color.green() - 127) * contrast) + 127), 255);
      int b = qBound(
          0, static_cast<int>(((color.blue() - 127) * contrast) + 127), 255);

      temp.setPixel(i, j, qRgb(r, g, b));
    }
  }
  return temp;
}

QImage Model::HSL(const QImage &img_, QColor inputHSL_) {
  QImage temp(img_);
  for (int i = 0; i < img_.width(); ++i) {
    for (int j = 0; j < img_.height(); ++j) {
      QColor color = temp.pixelColor(i, j);
      color.toHsl();
      int h = (color.hue() + inputHSL_.hue());
      int s =
          qBound(0, (color.saturation() + (inputHSL_.saturation() % 100)), 255);
      int l = qBound(0, (color.lightness() * inputHSL_.lightness()) / 100, 255);
      color.setHsl(h, s, l);
      temp.setPixelColor(i, j, color);
    }
  }
  return temp;
}

QImage Model::HSV(const QImage &img_, QColor inputHSL_) {
  QImage temp(img_);
  for (int i = 0; i < img_.width(); ++i) {
    for (int j = 0; j < img_.height(); ++j) {
      QColor color = temp.pixelColor(i, j);
      color.toHsv();
      int h = (color.hue() + inputHSL_.hue());
      int s =
          qBound(0, (color.saturation() + (inputHSL_.saturation() % 100)), 255);
      int v = qBound(0, (color.lightness() * inputHSL_.value()) / 100, 255);
      color.setHsv(h, s, v);
      temp.setPixelColor(i, j, color);
    }
  }
  return temp;
}

}  // namespace s21
