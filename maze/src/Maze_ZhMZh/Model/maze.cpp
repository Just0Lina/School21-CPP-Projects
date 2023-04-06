#include "maze.h"

namespace s21 {
void Maze::ParseFile(std::string file_) {
  Clean();
  std::string str_;
  std::stringstream temp;
  bool wall;
  bool first = true;
  int k = 0;
  std::ifstream fileRead(file_, std::ifstream::in);
  if (fileRead.is_open()) {
    fileRead.clear();
    fileRead.seekg(0);
    std::getline(fileRead, str_);
    height_ = std::stoi(&str_[0]);
    width_ = std::stoi(&str_[2]);
    while (!fileRead.eof()) {
      std::getline(fileRead, str_);
      MazeNode node_;
      if (!str_.empty()) {
        temp << str_;
        if (first == true) {
          while (temp >> wall) {
            if (wall == 1) node_.right_ = true;
            if (wall == 0) node_.right_ = false;
            row_.push_back(node_);
          }
          maze_.push_back(row_);
        } else {
          int m = 0;
          while (temp >> wall) {
            if (wall == 1) maze_[k][m].down_ = true;
            if (wall == 0) maze_[k][m].down_ = false;
            m++;
          }
          k++;
        }
        temp.clear();
        row_.clear();
      } else {
        first = false;
      }
    }
    if (k != height_) {
      maze_.clear();
      SetHeight(0);
      SetWidth(0);
      fileRead.close();
    }
    Borders();
  } else {
    fprintf(stderr, "No such file, mafaka\n");
  }
  fileRead.close();
}

void Maze::Borders() {
  for (int i = 0; i < height_; ++i) {
    for (int j = 0; j < width_; ++j) {
      if (j != 0 && maze_[i][j - 1].right_ == true) maze_[i][j].left_ = true;
      if (i != 0 && maze_[i - 1][j].down_ == true) maze_[i][j].top_ = true;
    }
  }
}

void Maze::Clean() {
  if (width_ && height_) {
    for (size_t i = 0; i < maze_.size(); i++) {
      for (size_t j = 0; j < maze_[i].size(); j++) {
        maze_[i][j].right_ = false;
        maze_[i][j].down_ = false;
        maze_[i][j].left_ = false;
        maze_[i][j].top_ = false;
        maze_[i][j].path_ = 0;
      }
    }
  }
  SetHeight(0);
  SetWidth(0);
  if (!maze_.empty()) {
    maze_.clear();
  }
}

void Maze::Generator() {
  std::vector<int> newLine_(width_);
  int count = 1;
  maze_.resize(height_);
  for (int i = 0; i < height_; ++i) {
    maze_[i].resize(width_);
  }

  for (int i = 0; i < height_ - 1; ++i) {
    NewLineSetter(newLine_, count);
    VerticalLineSet(newLine_, i);
    HorizontalLineSet(newLine_, i);
    CheckLine(newLine_, i);
    NextLine(newLine_, i);
  }
  NewLineSetter(newLine_, count);
  VerticalLineSet(newLine_, height_ - 1);
  CheckEnd(newLine_);
  SaveFile();
}

void Maze::NewLineSetter(std::vector<int> &line, int &count) {
  for (int i = 0; i < width_; i++) {
    if (line[i] == 0) {
      line[i] = count;
      count++;
    }
  }
}

void Maze::VerticalLineSet(std::vector<int> &line, int index) {
  for (int i = 0; i < width_ - 1; i++) {
    bool random = rand() > (RAND_MAX / 2);
    if (random || line[i] == line[i + 1]) {
      maze_[index][i].right_ = true;
    } else {
      ConcatSet(line, i);
    }
  }
  maze_[index][width_ - 1].right_ = true;
}

void Maze::ConcatSet(std::vector<int> &line, int index) {
  int elemNext = line[index + 1];
  int elem = line[index];
  for (size_t j = 0; j < line.size(); j++) {
    if (line[j] == elemNext) line[j] = elem;
  }
}

void Maze::HorizontalLineSet(std::vector<int> &line, int index) {
  for (int j = 0; j < width_; j++) {
    if (CalcSets(line, j) == 1) {
      maze_[index][j].down_ = false;
    } else {
      bool random = rand() > (RAND_MAX / 2);
      maze_[index][j].down_ = random;
    }
  }
}

int Maze::CalcSets(std::vector<int> line, int index) {
  int countSet = 0;
  for (size_t i = 0; i < line.size(); i++) {
    if (line[i] == line[index]) {
      countSet++;
    }
  }
  return countSet;
}

void Maze::CheckLine(std::vector<int> &line, int index) {
  for (int i = 0; i < width_; i++) {
    if (CalcHorizontal(line, index, i) == 0) {
      maze_[index][i].down_ = false;
    }
  }
}

int Maze::CalcHorizontal(std::vector<int> line, int index, int j) {
  int countWalls = 0;
  int elem = line[j];
  for (int i = 0; i < width_; i++) {
    if (line[i] == elem && maze_[index][i].down_ == false) {
      countWalls++;
    }
  }
  return countWalls;
}

void Maze::NextLine(std::vector<int> &line, int index) {
  for (int j = 0; j < width_; j++) {
    if (maze_[index][j].down_ == true) line[j] = 0;
  }
}

void Maze::CheckEnd(std::vector<int> &line) {
  for (int i = 0; i < width_ - 1; i++) {
    if (line[i] != line[i + 1]) {
      maze_[height_ - 1][i].right_ = false;
      ConcatSet(line, i);
    }
    maze_[height_ - 1][i].down_ = true;
  }
  maze_[height_ - 1][width_ - 1].down_ = true;
}

void Maze::SaveFile() {
  std::fstream fileMaze_;
  fileMaze_.open(fileName_, std::ios::out);

  fileMaze_ << height_ << " " << width_ << std::endl;
  for (int i = 0; i < height_; ++i) {
    for (int j = 0; j < width_; ++j) {
      fileMaze_ << maze_[i][j].right_ << " ";
    }
    fileMaze_ << std::endl;
  }
  fileMaze_ << std::endl;
  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      fileMaze_ << maze_[i][j].down_ << " ";
    }
    fileMaze_ << std::endl;
  }
}

void Maze::CleanPathFinder() {
  for (int i = 0; i < height_; ++i) {
    for (int j = 0; j < width_; ++j) {
      maze_[i][j].path_ = 0;
    }
  }
}

void Maze::OverMaze(std::pair<int, int> startPoint_,
                    std::pair<int, int> endPoint_) {
  bool deadend = false;
  pathFinder_.clear();
  CleanPathFinder();

  pathFinder_.push_back({startPoint_.first, startPoint_.second});
  tempPath = 1;
  while (!pathFinder_.empty() && pathFinder_.back() != endPoint_) {
    int y = pathFinder_.back().first;
    int x = pathFinder_.back().second;
    deadend = true;

    if (maze_[y][x].right_ == false && x + 1 < width_ &&
        maze_[y][x + 1].path_ == false) {
      maze_[y][x + 1].path_ += maze_[y][x].path_ + 1;
      pathFinder_.push_back({y, x + 1});
      deadend = false;
    }
    if (maze_[y][x].left_ == false && x - 1 >= 0 &&
        maze_[y][x - 1].path_ == 0) {
      maze_[y][x - 1].path_ += maze_[y][x].path_ + 1;
      pathFinder_.push_back({y, x - 1});
      deadend = false;
    }
    if (maze_[y][x].top_ == false && y - 1 >= 0 && maze_[y - 1][x].path_ == 0) {
      maze_[y - 1][x].path_ += maze_[y][x].path_ + 1;
      pathFinder_.push_back({y - 1, x});
      deadend = false;
    }
    if (maze_[y][x].down_ == false && y + 1 < height_ &&
        maze_[y + 1][x].path_ == 0) {
      maze_[y + 1][x].path_ += maze_[y][x].path_ + 1;
      pathFinder_.push_back({y + 1, x});
      deadend = false;
    }
    if (deadend == true) pathFinder_.pop_back();
    tempPath += 1;
    maze_[startPoint_.first][startPoint_.second].path_ = -1;
  }
}
}  // namespace s21
