#include "controller.h"

namespace s21 {

void Controller::scaling(double val) {
  setAffine(s21::AffType::scale, val / newScale, 0, 0);
  if (val >= 0) newScale = val;
}

void Controller::movingX(double val) {
  setAffine(s21::AffType::move, val - newMoveX, 0, 0);
   newMoveX = val;
}

void Controller::movingY(double val) {
  setAffine(s21::AffType::move, 0, val - newMoveY, 0);
  newMoveY = val;
}

void Controller::movingZ(double val) {
  setAffine(s21::AffType::move, 0, 0, val - newMoveZ);

  newMoveZ = val;
}

void Controller::rotatingX(double val) {
  setAffine(s21::AffType::rotation, val - newRotationX, 0, 0);
  newRotationX = val;
}

void Controller::rotatingY(double val) {
  setAffine(s21::AffType::rotation, 0, val - newRotationY, 0);
  newRotationY = val;
}

void Controller::rotatingZ(double val) {
  setAffine(s21::AffType::rotation, 0, 0, val - newRotationZ);
  newRotationZ = val;
}
}  // namespace s21
