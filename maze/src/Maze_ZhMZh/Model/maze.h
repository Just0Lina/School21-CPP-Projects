#ifndef SRC_MAZE_H_
#define SRC_MAZE_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {
class Maze {
 public:
  Maze(){};
  ~Maze(){};

  struct MazeNode {
   public:
    bool right_ = false;
    bool down_ = false;
    bool left_ = false;
    bool top_ = false;

    int path_ = 0;
  };

  void ParseFile(std::string file_);
  void SetFile(std::string str) { fileName_ = str; }
  void SetHeight(int h) { height_ = h; }
  void SetWidth(int w) { width_ = w; }
  void SaveFile();

  void Clean();

  void CleanPathFinder();

  int GetHeight() { return height_; }
  int GetWidth() { return width_; }

  std::vector<std::vector<MazeNode>> &GetMaze() { return maze_; }
  std::vector<std::pair<int, int>> &GetPathFinder() { return pathFinder_; }
  void Borders();
  void Generator();

  void NewLineSetter(std::vector<int> &line, int &count);
  void VerticalLineSet(std::vector<int> &line, int index);
  void HorizontalLineSet(std::vector<int> &line, int index);
  int CalcSets(std::vector<int> line, int index);
  void CheckLine(std::vector<int> &line, int index);
  int CalcHorizontal(std::vector<int> line, int index, int i);
  void NextLine(std::vector<int> &line, int index);
  void CheckEnd(std::vector<int> &line);
  void ConcatSet(std::vector<int> &line, int index);
  void OverMaze(std::pair<int, int> startPoint_, std::pair<int, int> endPoint_);

 private:
  std::vector<std::vector<MazeNode>> maze_;
  std::vector<MazeNode> row_;
  int height_ = 0;
  int width_ = 0;
  int tempPath = 0;

  std::string fileName_;

  std::vector<std::pair<int, int>> pathFinder_{};
};

}  // namespace s21
#endif  // SRC_MAZE_H_
