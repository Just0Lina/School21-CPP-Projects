#include "cave.h"

#include <iostream>


s21::Cave::Cave(int h, int w, int birthLimit, int deathLimit)
    : height_(h), width_(w), birthLimit_(birthLimit), deathLimit_(deathLimit) {
  Resize();
}

void s21::Cave::Generator() {
  cave_.resize(height_);
  for (int i = 0; i < height_; ++i) {
    cave_[i].resize(width_);
    for (int j = 0; j < width_; ++j) {
      cave_[i][j] = rand() % 2;
    }
  }
  SaveFile();
}

void s21::Cave::SetWidth(int w) {
  width_ = w;
  for (int i = 0; i < height_; ++i) {
    cave_[i].resize(width_);
  }
}

void s21::Cave::SetHeight(int h) {
  height_ = h;
  cave_.resize(height_);
}

int s21::Cave::CountNeighbors(int i, int j) {
  int neighbors = 0;
  for (int row = i - 1; row < i + 2; row++) {
    for (int col = j - 1; col < j + 2; col++) {
      if (!(row == i && col == j) && (row >= 0 && row < height_) &&
          (col >= 0 && col < width_) && cave_[row][col]) {
        ++neighbors;
      } else if (row < 0 || row >= height_ || col < 0 || col >= width_) {
        ++neighbors;
      }
    }
  }
  return neighbors;
}

bool s21::Cave::UpdateScene() {
  bool flag = 0;
  Cave tmpCave(height_, width_, birthLimit_, deathLimit_);
  auto tmp = tmpCave.GetCave();
  for (int i = 0; i < height_; ++i) {
    for (int j = 0; j < width_; ++j) {
      int limits = CountNeighbors(i, j);
      if (!cave_[i][j] && limits > birthLimit_) {
        tmp[i][j] = !cave_[i][j];
        flag = 1;
      } else if (cave_[i][j] && limits < deathLimit_) {
        tmp[i][j] = !cave_[i][j];
        flag = 1;
      } else {
        tmp[i][j] = cave_[i][j];
      }
    }
  }

  cave_ = tmp;
  return flag;
}

void s21::Cave::ParseFile(std::string file_) {
  cave_.clear();
  SetHeight(0);
  SetWidth(0);
  std::string str_;
  std::string cell;
  std::stringstream temp;
  std::ifstream fileRead(file_, std::ifstream::in);
  if (fileRead.is_open()) {
    fileRead.clear();
    fileRead.seekg(0);
    std::getline(fileRead, str_);
    width_ = std::stoi(&str_[0]);
    height_ = std::stoi(&str_[2]);
    Resize();
    int r = 0, c = 0;
    for (int i = 0; i < height_; ++i) {
    // while (!fileRead.eof()) {
      std::getline(fileRead, str_);
      temp << str_;
      while (temp >> cell) {
        if (c >= width_) {
          c = 0;
          ++r;
        }
        if (cell == "0")
          cave_[r][c] = false;
        else if (cell == "1")
          cave_[r][c] = true;
        ++c;
      }
      temp.clear();
    }
    if (r != height_ - 1) {
      cave_.clear();
      SetHeight(0);
      SetWidth(0);
    }
  }
  fileRead.close();
}

void s21::Cave::SaveFile() {
  std::fstream fileCave_;
  fileCave_.open(fileName_, std::ios::out);
  fileCave_ << height_ << " " << width_ << std::endl;
  for (int i = 0; i < height_; ++i) {
    for (int j = 0; j < width_; ++j) {
      fileCave_ << cave_[i][j] << " ";
    }
    fileCave_ << std::endl;
  }
}

void s21::Cave::Resize() {
  cave_.resize(height_);
  for (int i = 0; i < height_; ++i) {
    cave_[i].resize(width_);
  }
}
