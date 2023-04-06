#ifndef SRC_MODEL_H_
#define SRC_MODEL_H_

#include <cmath>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

namespace s21 {
class Parse {
 public:
    Parse() {}
    ~Parse() {}
    std::vector<double> &GetVert() { return vert; }
    std::vector<unsigned int> &GetPolygon() { return polygon; }

    void dataFill(std::string name);

 private:
    std::vector<double> vert;
    std::vector<unsigned int> polygon;
};
enum AffType { rotation, scale, move };

class Affine {
 public:

  Affine() {}
  ~Affine() {}
//  void dataFill(std::string name);

  void setAffine(enum AffType type, std::vector<double> &vert,double valX, double valY, double valZ);

  class Transformation {
   public:
    virtual ~Transformation() = default;
    virtual void AffineAlg(std::vector<double> &vert, double valX, double valY,
                           double valZ) = 0;
  };

  class Scale : public Transformation {
   public:
    void AffineAlg(std::vector<double> &vert, double valX, double valY,
                   double valZ) override;

   private:
    void scaling(double val);
  };

  class Rotation : public Transformation {
   public:
    void AffineAlg(std::vector<double> &vert, double valX, double valY,
                   double valZ) override;

   private:
    void rotationX(std::vector<double> &vert, double valX);
    void rotationY(std::vector<double> &vert, double valY);
    void rotationZ(std::vector<double> &vert, double valZ);
  };

  class Moving : public Transformation {
   public:
    void AffineAlg(std::vector<double> &vert, double valX, double valY,
                   double valZ) override;

   private:
    void moveX(std::vector<double> &vert, double val);
    void moveY(std::vector<double> &vert, double val);
    void moveZ(std::vector<double> &vert, double val);
  };

  class StrategyInterface {
   private:
    std::unique_ptr<Transformation> trans_;

   public:
    explicit StrategyInterface(std::unique_ptr<Transformation> trans = {});
    ~StrategyInterface() {}
    void setStrategy(std::unique_ptr<Transformation> trans) {
      trans_ = std::move(trans);
    }

    void AffCall(std::vector<double> &vert, double valX, double valY,
                 double valZ);
  };
};


class Facade {
 protected:
    Parse *parser_;
    Affine *affine_;

 public:
    explicit Facade(Parse *parse_ = nullptr, Affine *affine_ = nullptr) {
        this->parser_ = parse_ ?: new Parse;
        this->affine_ = affine_ ?: new Affine;
    }
    ~Facade() {
      delete parser_;
      delete affine_;
    }

    std::vector<double>& getVertices() {
        return parser_->GetVert();
    }
    std::vector<unsigned int>& getPolygon() {
        return parser_->GetPolygon();
    }

    void setAffine(enum AffType type, double valX, double valY,
                          double valZ);
    void dataFilling(std::string name) {
        parser_->dataFill(name);
    }
 private:
   std::vector<double> vert;
   std::vector<unsigned int> polygon;

};
}  // namespace s21
#endif  //  SRC_MODEL_H_
