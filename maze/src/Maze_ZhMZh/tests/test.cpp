#include <gtest/gtest.h>

#include <iostream>

#include "../Model/cave.h"
#include "../Model/maze.h"

TEST(maze, test1) {
  s21::Maze maze_;
  maze_.SetHeight(18);
  maze_.SetWidth(18);

  ASSERT_EQ(maze_.GetHeight(), 18);
  ASSERT_EQ(maze_.GetWidth(), 18);
}

TEST(maze, test2) {
  s21::Maze maze_;
  maze_.ParseFile("../src/Maze_ZhMZh/tests/maze_test.txt");

  ASSERT_EQ(maze_.GetHeight(), 10);
  ASSERT_EQ(maze_.GetWidth(), 10);
}

TEST(maze, test3) {
  s21::Maze maze_;
  maze_.ParseFile("../src/Maze_ZhMZh/tests/maze_test.txt");

  std::pair<int, int> startPoint_{0, 0};
  std::pair<int, int> endPoint_{9, 9};
  maze_.OverMaze(startPoint_, endPoint_);

  ASSERT_EQ(maze_.GetHeight(), 10);
  ASSERT_EQ(maze_.GetWidth(), 10);
}

TEST(maze, test4) {
  s21::Maze maze_;
  maze_.SetHeight(50);
  maze_.SetWidth(50);
  maze_.Generator();

  ASSERT_EQ(maze_.GetHeight(), 50);
  ASSERT_EQ(maze_.GetWidth(), 50);
}

TEST(maze, test5) {
  s21::Maze maze_;
  maze_.SetHeight(50);
  maze_.SetWidth(50);
  maze_.Generator();

  ASSERT_EQ(maze_.GetHeight(), 50);
  ASSERT_EQ(maze_.GetWidth(), 50);

  maze_.Clean();

  ASSERT_EQ(maze_.GetHeight(), 0);
  ASSERT_EQ(maze_.GetWidth(), 0);
}

TEST(maze, test6) {
  s21::Maze maze_;
  maze_.ParseFile("../src/Maze_ZhMZh/tests/mazefake_test.txt");

  ASSERT_EQ(maze_.GetHeight(), 0);
  ASSERT_EQ(maze_.GetWidth(), 0);
}

TEST(cave, test1) {
  s21::Cave cave_;
  cave_.SetWidth(10);
  cave_.SetHeight(10);

  ASSERT_EQ(cave_.GetHeight(), 10);
  ASSERT_EQ(cave_.GetWidth(), 10);

  cave_.Generator();

  cave_.SetWidth(12);
  cave_.SetHeight(12);
  cave_.Resize();

  ASSERT_EQ(cave_.GetHeight(), 12);
  ASSERT_EQ(cave_.GetWidth(), 12);
}

TEST(cave, test2) {
  s21::Cave cave_;
  cave_.ParseFile("../src/Maze_ZhMZh/tests/cave_test.txt");
  int h = cave_.GetHeight();
  int w = cave_.GetWidth();
  cave_.SetBirth(5);
  cave_.SetDeath(1);
  cave_.CountNeighbors(h, w);
  cave_.UpdateScene();

  ASSERT_EQ(cave_.GetHeight(), 5);
  ASSERT_EQ(cave_.GetWidth(), 5);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
