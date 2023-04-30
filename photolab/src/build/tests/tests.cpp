#include <gtest/gtest.h>

#include <QImage>
#include <fstream>

// #include <iostream>

#include "../PhotoBAB_v1/Model/model.h"

double err = 1e-1;

TEST(FILTER, GRAYSCALE) {
  s21::Model model_;
  QImage org_("../../misc/images/sample.png");
  QImage cmp_("../../misc/images/sample-bw-average.png");

  QImage res = model_.Grayscale(org_);
  for (int i = 0; i < res.width(); ++i) {
    for (int j = 0; j < res.height(); ++j) {
      ASSERT_NEAR(res.pixelColor(i, j).redF(), cmp_.pixelColor(i, j).redF(),
                  err);
      ASSERT_NEAR(res.pixelColor(i, j).greenF(), cmp_.pixelColor(i, j).greenF(),
                  err);
      ASSERT_NEAR(res.pixelColor(i, j).blueF(), cmp_.pixelColor(i, j).blueF(),
                  err);
    }
  }
}
TEST(FILTER, NEGATIVE) {
  s21::Model model_;

  QImage org_("../../misc/images/sample.png");
  QImage cmp_("../../misc/images/sample-negative.png");

  QImage res(model_.Negative(org_));

  for (int i = 0; i < res.width(); ++i) {
    for (int j = 0; j < res.height(); ++j) {
      ASSERT_NEAR(res.pixelColor(i, j).redF(), cmp_.pixelColor(i, j).redF(),
                  err);
      ASSERT_NEAR(res.pixelColor(i, j).greenF(), cmp_.pixelColor(i, j).greenF(),
                  err);
      ASSERT_NEAR(res.pixelColor(i, j).blueF(), cmp_.pixelColor(i, j).blueF(),
                  err);
    }
  }
}

TEST(FILTER, GAUSSAIN) {
  s21::Model model_;
  QImage org_("../../misc/images/sample-bw-dissat.png");
  QImage cmp_("../../misc/images/sample-gaussian-blur.png");

  QImage res(model_.Gaussian(org_));

  for (int i = 1; i < 10; ++i) {
    for (int j = 1; j < 10; ++j) {
      ASSERT_NEAR(res.pixelColor(i, j).redF(), cmp_.pixelColor(i, j).redF(),
                  err);
      ASSERT_NEAR(res.pixelColor(i, j).greenF(), cmp_.pixelColor(i, j).greenF(),
                  err);
      ASSERT_NEAR(res.pixelColor(i, j).blueF(), cmp_.pixelColor(i, j).blueF(),
                  err);
    }
  }
}

TEST(FILTER, sobelLeft) {
  s21::Model model_;

  QImage org_("../../misc/images/sample-bw-dissat.png");
  QImage cmp_("../../misc/images/sample-sobel-left.png");

  QImage res(model_.SobelLeft(model_.Grayscale(org_)));

  for (int i = 1; i < 10; ++i) {
    for (int j = 1; j < 10; ++j) {
      ASSERT_NEAR(res.pixelColor(i, j).redF(), cmp_.pixelColor(i, j).redF(),
                  err);
      ASSERT_NEAR(res.pixelColor(i, j).greenF(), cmp_.pixelColor(i, j).greenF(),
                  err);
      ASSERT_NEAR(res.pixelColor(i, j).blueF(), cmp_.pixelColor(i, j).blueF(),
                  err);
    }
  }
}

TEST(FILTER, sobelRight) {
  s21::Model model_;

  QImage org_("../../misc/images/sample-bw-dissat.png");
  QImage cmp_("../../misc/images/sample-sobel-right.png");

  QImage res(model_.SobelRight(model_.Grayscale(org_)));

  for (int i = 1; i < 10; ++i) {
    for (int j = 1; j < 10; ++j) {
      ASSERT_NEAR(res.pixelColor(i, j).redF(), cmp_.pixelColor(i, j).redF(),
                  err);
      ASSERT_NEAR(res.pixelColor(i, j).greenF(), cmp_.pixelColor(i, j).greenF(),
                  err);
      ASSERT_NEAR(res.pixelColor(i, j).blueF(), cmp_.pixelColor(i, j).blueF(),
                  err);
    }
  }
}

TEST(FILTER, LAPLACICN) {
  s21::Model model_;

  QImage org_("../../misc/images/sample-bw-dissat.png");
  QImage cmp_("../../misc/images/sample-outline.png");

  QImage res(model_.Laplacian(model_.Grayscale(org_)));
  for (int i = 1; i < 10; ++i) {
    for (int j = 1; j < 10; ++j) {
      ASSERT_NEAR(res.pixelColor(i, j).redF(), cmp_.pixelColor(i, j).redF(),
                  err);
      ASSERT_NEAR(res.pixelColor(i, j).greenF(), cmp_.pixelColor(i, j).greenF(),
                  err);
      ASSERT_NEAR(res.pixelColor(i, j).blueF(), cmp_.pixelColor(i, j).blueF(),
                  err);
    }
  }
}

TEST(FILTER, EMBOSS) {
  s21::Model model_;
  QImage org_("../../misc/images/sample-bw-dissat.png");
  QImage cmp_("../../misc/images/sample-ebmoss.png");

  QImage res(model_.Emboss(org_));
  for (int i = 1; i < 10; ++i) {
    for (int j = 1; j < 10; ++j) {
      ASSERT_NEAR(res.pixelColor(i, j).redF(), cmp_.pixelColor(i, j).redF(),
                  err);
      ASSERT_NEAR(res.pixelColor(i, j).greenF(), cmp_.pixelColor(i, j).greenF(),
                  err);
      ASSERT_NEAR(res.pixelColor(i, j).blueF(), cmp_.pixelColor(i, j).blueF(),
                  err);
    }
  }
}

TEST(FILTER, BLUR) {
  s21::Model model_;

  QImage org_("../../misc/images/sample-bw-dissat.png");
  QImage cmp_("../../misc/images/sample-box-blur.png");

  QImage res(model_.Boxblur(org_));

  for (int i = 1; i < 10; ++i) {
    for (int j = 1; j < 10; ++j) {
      ASSERT_NEAR(res.pixelColor(i, j).redF(), cmp_.pixelColor(i, j).redF(),
                  err);
      ASSERT_NEAR(res.pixelColor(i, j).greenF(), cmp_.pixelColor(i, j).greenF(),
                  err);
      ASSERT_NEAR(res.pixelColor(i, j).blueF(), cmp_.pixelColor(i, j).blueF(),
                  err);
    }
  }
}

// TEST(FILTER, SHARPEN) {
//   s21::Model model_;

//   QImage org_("../../misc/images/sample-bw-dissat.png");
//   QImage cmp_("../../misc/images/sample-sharpen.png");

//   QImage res(model_.Sharpen(org_));
//   std::cout << res.width() << " " << cmp_.width();

//   for (int i = 200; i < 205; ++i) {
//     for (int j = 200; j < 205; ++j) {
//       std::cout << i << " " << j << std::endl;

//       ASSERT_NEAR(res.pixelColor(i, j).redF(), cmp_.pixelColor(i, j).redF(),
//                   err);
//       ASSERT_NEAR(res.pixelColor(i, j).greenF(), cmp_.pixelColor(i,
//       j).greenF(),
//                   err);
//       ASSERT_NEAR(res.pixelColor(i, j).blueF(), cmp_.pixelColor(i,
//       j).blueF(),
//                   err);
//     }
//   }
// }

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
