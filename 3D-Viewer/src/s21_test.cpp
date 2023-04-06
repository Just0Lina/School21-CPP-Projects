#include <gtest/gtest.h>

#include <cstring>
#include <fstream>
#include <string>
#include <vector>

#include "controller/controller.h"

TEST(s21_3d_test, test1) {
  std::vector<float> standart = {
      1.0, -1.0,     -1.0, 1.0,  -1.0, 1.0,  -1.0,      -1.0,
      1.0, -1.0,     -1.0, -1.0, 1.0,  1.0,  -0.999999, 0.999999,
      1.0, 1.000001, -1.0, 1.0,  1.0,  -1.0, 1.0,       -1.0};
  s21::Facade testFacade;
  // s21::Controller &testFacade{s21::Controller::getInstance()};
  std::string name = "./objects/cube_test2.obj";
  testFacade.dataFilling(name);
  for (size_t i = 0; i < testFacade.getVertices().size(); i++) {
    ASSERT_FLOAT_EQ(testFacade.getVertices()[i], standart[i]);
  }
  double val = 3.0;

  testFacade.setAffine(s21::AffType::move, 0, 0, val);
  for (size_t i = 0; i < standart.size(); i += 3) {
    standart[i + 2] += val;
  }
  for (size_t i = 0; i < standart.size(); i++) {
    ASSERT_FLOAT_EQ(testFacade.getVertices()[i], standart[i]);
  }

  testFacade.setAffine(s21::AffType::scale, val, val, val);
  for (size_t i = 0; i < standart.size(); i++) {
    standart[i] *= val;
    ASSERT_FLOAT_EQ(testFacade.getVertices()[i], standart[i]);
  }

  testFacade.setAffine(s21::AffType::move, val, 0, 0);
  for (size_t i = 0; i < standart.size(); i += 3) {
    standart[i] = standart[i] + val;
  }
  for (size_t i = 0; i < standart.size(); i++) {
    ASSERT_FLOAT_EQ(testFacade.getVertices()[i], standart[i]);
  }

  testFacade.setAffine(s21::AffType::move, 0, val, 0);
  for (size_t i = 0; i < standart.size(); i += 3) {
    standart[i + 1] += val;
  }
  for (size_t i = 0; i < standart.size(); i++) {
    ASSERT_FLOAT_EQ(testFacade.getVertices()[i], standart[i]);
  }

  testFacade.setAffine(s21::AffType::rotation, val, 0, 0);
  testFacade.setAffine(s21::AffType::rotation, 0, val, 0);
  testFacade.setAffine(s21::AffType::rotation, 0, 0, val);
  ASSERT_EQ(testFacade.getVertices().size(), standart.size());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
