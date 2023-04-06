#ifndef CONTROLLER_H
#define CONTROLLER_H

enum Type { Cave, Maze };

#include <QDebug>
#include <QFileDialog>

#include "../Model/cave.h"
#include "../Model/maze.h"

class Controller {
 private:
  Controller() = default;
  ~Controller() = default;
  s21::Cave cave;
  s21::Maze maze;

 public:
  static Controller &getInstance();
  s21::Cave &GetCave() { return cave; }
  s21::Maze &GetMaze() { return maze; }

  void GenerateObject(Type t, int fmt...);
  void LoadObject(Type t, std::string filename_, int birth = 0, int death = 0);
};
#endif  // CONTROLLER_H
