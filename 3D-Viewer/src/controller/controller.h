#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/model.h"

namespace s21 {
class Controller {
 private:
  Controller() = default;
  ~Controller() = default;

 public:
  static Controller &getInstance() {
    static Controller controller;
    return controller;
  }

  double newScale = 1, newMoveX = 0, newMoveY = 0, newMoveZ = 0,
         newRotationX = 0, newRotationY = 0, newRotationZ = 0;
  void modelDataFillCall(std::string name) { facade_.dataFilling(name); }
  void setAffine(AffType type, double valX, double valY, double valZ) {
    facade_.setAffine(type, valX, valY, valZ);
  }

  void scaling(double val);

  void movingX(double val);
  void movingY(double val);
  void movingZ(double val);

  void rotatingX(double val);
  void rotatingY(double val);
  void rotatingZ(double val);

  std::vector<double> GetVertCall() { return facade_.getVertices(); }
  std::vector<unsigned int> GetPolygonCall() { return facade_.getPolygon(); }

 private:
  Facade facade_;
};

}  // namespace s21
#endif  // SRC__CONTROLLER_CONTROLLER_H_
