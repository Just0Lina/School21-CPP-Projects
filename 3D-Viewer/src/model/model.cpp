#include "model.h"

namespace s21 {
void Parse::dataFill(std::string name) {
  polygon.clear();
  vert.clear();
  std::string str;
  std::ifstream fileRead(name, std::ifstream::in);
  if (fileRead.is_open()) {
    fileRead.clear();
    fileRead.seekg(0);
    while (!fileRead.eof()) {
      char *token;
      std::getline(fileRead, str);
      if (strncmp(str.c_str(), "v ", 2) == 0) {
        token = std::strtok(const_cast<char *>(str.c_str()), "v \n");
        while (token != NULL) {
          double digit = atof(token);
          vert.push_back(digit);
          token = strtok(NULL, "v \n");
        }
      } else if (strncmp(str.c_str(), "f ", 2) == 0) {
        token = std::strtok(const_cast<char *>(str.c_str()), "f \n");
        int digit = std::atoi(token) - 1;
        int rdigit = digit;
        while ((token = std::strtok(NULL, "f \n"))) {
          int digit2 = std::atoi(token) - 1;
          if (digit2 >= 0) {
            polygon.push_back(rdigit);
            polygon.push_back(digit2);
            rdigit = digit2;
          }
        }
        polygon.push_back(rdigit);
        polygon.push_back(digit);
      }
    }
  } else {
    fprintf(stderr, "No such file, mafaka");
  }
  fileRead.close();
}

void Facade::setAffine(enum AffType type, double valX, double valY,
                      double valZ) {
  std::vector<double> &vert = getVertices();
  affine_->setAffine(type, vert, valX, valY, valZ);

}

void Affine::setAffine(enum AffType type, std::vector<double> &vert, double valX, double valY,
                      double valZ) {
  StrategyInterface trans;
  if (type == AffType::move) {
    trans.setStrategy(std::make_unique<Moving>());
  } else if (type == AffType::rotation) {
    trans.setStrategy(std::make_unique<Rotation>());
  } else {
    trans.setStrategy(std::make_unique<Scale>());
  }
  trans.AffCall(vert, valX, valY, valZ);

}

void Affine::Scale::AffineAlg(std::vector<double> &vert, double valX,
                             double valY, double valZ) {
  for (size_t i = 0; i < vert.size(); i++) {
    vert[i] = vert[i] * valX;
  }
  valY = valZ * 0.0;
  valZ = valY * 0.0;
  valZ = valY * valZ;
}

void Affine::Moving::AffineAlg(std::vector<double> &vert, double valX,
                              double valY, double valZ) {
  if (valX) moveX(vert, valX);
  if (valY) moveY(vert, valY);
  if (valZ) moveZ(vert, valZ);
}

void Affine::Moving::moveX(std::vector<double> &vert, double val) {
  for (size_t i = 0; i < vert.size(); i += 3) {
    //  for (size_t i = 0; i < vert.size(); i += 3) {
    vert[i] = vert[i] + val;
  }
}

void Affine::Moving::moveY(std::vector<double> &vert, double val) {
  for (size_t i = 0; i < vert.size(); i += 3) {
    vert[i + 1] = vert[i + 1] + val;
  }
}

void Affine::Moving::moveZ(std::vector<double> &vert, double val) {
  for (size_t i = 0; i < vert.size(); i += 3) {
    vert[i + 2] = vert[i + 2] + val;
  }
}

void Affine::Rotation::AffineAlg(std::vector<double> &vert, double valX,
                                double valY, double valZ) {
  if (valX) rotationX(vert, valX);
  if (valY) rotationY(vert, valY);
  if (valZ) rotationZ(vert, valZ);
}

void Affine::Rotation::rotationX(std::vector<double> &vert, double val) {
  for (size_t i = 0; i < vert.size(); i += 3) {
    double tempY = vert[i + 1];
    double tempZ = vert[i + 2];
    vert[i + 1] = cos(val) * tempY - sin(val) * tempZ;
    vert[i + 2] = sin(val) * tempY + cos(val) * tempZ;
  }
}

void Affine::Rotation::rotationY(std::vector<double> &vert, double val) {
  for (size_t i = 0; i < vert.size(); i += 3) {
    double tempX = vert[i];
    double tempZ = vert[i + 2];
    vert[i] = cos(val) * tempX + sin(val) * tempZ;
    vert[i + 2] = (-1) * sin(val) * tempX + cos(val) * tempZ;
  }
}

void Affine::Rotation::rotationZ(std::vector<double> &vert, double val) {
  for (size_t i = 0; i < vert.size(); i += 3) {
    double tempX = vert[i];
    double tempY = vert[i + 1];
    vert[i] = cos(val) * tempX - sin(val) * tempY;
    vert[i + 1] = sin(val) * tempX + cos(val) * tempY;
  }
}

Affine::StrategyInterface::StrategyInterface(std::unique_ptr<Transformation> trans)
    : trans_(std::move(trans)) {}

void Affine::StrategyInterface::AffCall(std::vector<double> &vert, double valX, double valY, double valZ) {
    if (trans_) {
        trans_->AffineAlg(vert, valX, valY, valZ);
    }
}
}  // namespace s21
