#include "controller.h"

Controller &Controller::getInstance() {
  static Controller controller;
  return controller;
}

void Controller::GenerateObject(Type t, int fmt...) {
  va_list args;
  va_start(args, fmt);
  if (t == Cave) {
    cave.SetHeight(va_arg(args, int));
    cave.SetWidth(va_arg(args, int));
    cave.SetBirth(va_arg(args, int));
    cave.SetDeath(va_arg(args, int));
    QString saveFile = QDir::homePath() + "/_aCave_.txt";
    cave.SetFile(saveFile.toStdString());
    cave.Generator();
  } else {
    maze.Clean();
    maze.SetHeight(va_arg(args, int));
    maze.SetWidth(va_arg(args, int));
    QString saveFile = QDir::homePath() + "/_aMaze_.txt";
    maze.SetFile(saveFile.toStdString());
    maze.Generator();
    maze.ParseFile(saveFile.toStdString());
  }
  va_end(args);
}

void Controller::LoadObject(Type t, std::string filename_, int birth,
                            int death) {
  if (t == Cave) {
    if (!filename_.empty()) {
      cave.ParseFile(filename_);
      cave.SetBirth(birth);
      cave.SetDeath(death);
    } else {
      return;
    }
  } else {
    maze.Clean();
    if (!filename_.empty()) {
      maze.ParseFile(filename_);
    } else {
      return;
    }
  }
}
