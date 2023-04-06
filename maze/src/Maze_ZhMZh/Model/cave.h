#ifndef CAVE_H
#define CAVE_H
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {

class Cave {
 public:
  Cave() = default;
  Cave(int h, int w, int birthLimit, int deathLimit);
  ~Cave() = default;
  int GetWidth() { return width_; }
  int GetHeight() { return height_; }
  void SetHeight(int h);
  void SetWidth(int w);
  void Generator();
  void ParseFile(std::string file_);
  void SetFile(std::string str) { fileName_ = str; }
  void SetPath(std::string path) { pathName_ = path; }

  void SaveFile();

  void Resize();
  bool UpdateScene();
  void SetBirth(int i) { birthLimit_ = i; }
  void SetDeath(int i) { deathLimit_ = i; }
  int CountNeighbors(int i, int j);
  std::vector<std::vector<bool>> GetCave() { return cave_; }

 private:
  std::vector<std::vector<bool>> cave_;
  int height_ = 0;
  int width_ = 0;
  int birthLimit_ = 0, deathLimit_ = 0;

  std::string fileName_;
  std::string pathName_;
};
}  // namespace s21
#endif  // CAVE_H
