#include <gtest/gtest.h>

#include <iostream>
#include <queue>

#include "s21_queue.h"

template <typename T> bool check_qs(s21::queue<T> &q, std::queue<T> &qq) {
  if (q.size() != qq.size())
    return false;
  if (!q.empty()) {
    if (q.front() != qq.front())
      return false;
    if (q.back() != qq.back())
      return false;
  }
  while (!q.empty()) {
    if (q.front() != qq.front())
      return false;
    q.pop();
    qq.pop();
  }
  return true;
}

TEST(init, def) {
  s21::queue<int> q;
  ASSERT_TRUE(q.empty());
  ASSERT_EQ(q.size(), 0);
}

TEST(init, init_list) {
  s21::queue<int> q({1, 2, 3, 4, 5, 6});
  std::queue<int> qq({1, 2, 3, 4, 5, 6});
  ASSERT_TRUE(check_qs(q, qq));
}

TEST(init, copy) {
  s21::queue<int> q({1, 2, 3, 4, 5, 6});
  std::queue<int> qq({1, 2, 3, 4, 5, 6});
  s21::queue<int> q_copy(q);
  std::queue<int> qq_copy(qq);
  ASSERT_TRUE(check_qs(q, qq));
  ASSERT_TRUE(check_qs(q_copy, qq_copy));
}

TEST(init, copy_empty) {
  s21::queue<int> q;
  s21::queue<int> q_copy(q);
  std::queue<int> qq;
  std::queue<int> qq_copy(qq);
  ASSERT_TRUE(check_qs(q, qq));
  ASSERT_TRUE(check_qs(q_copy, qq_copy));
}

TEST(init, move) {
  s21::queue<int> q({1, 5, 3, 3, 2, 1, 5});
  s21::queue<int> q_move(std::move(q));
  std::queue<int> qq({1, 5, 3, 3, 2, 1, 5});
  std::queue<int> qq_move(std::move(qq));
  ASSERT_TRUE(check_qs(q, qq));
  ASSERT_TRUE(check_qs(q_move, qq_move));
}

TEST(operator, move) {
  s21::queue<int> q({1, 5, 3, 3, 2, 1, 5});
  s21::queue<int> q_move;
  std::queue<int> qq({1, 5, 3, 3, 2, 1, 5});
  std::queue<int> qq_move;
  q_move = std::move(q);
  qq_move = std::move(qq);
  ASSERT_TRUE(check_qs(q, qq));
  ASSERT_TRUE(check_qs(q_move, qq_move));
}

TEST(push, once) {
  s21::queue<int> q;
  std::queue<int> qq;
  q.push(5);
  qq.push(5);
  ASSERT_TRUE(check_qs(q, qq));
}

TEST(pop, once) {
  s21::queue<int> q;
  std::queue<int> qq;
  q.push(5);
  q.pop();
  qq.push(5);
  qq.pop();
  ASSERT_TRUE(check_qs(q, qq));
}

TEST(push, push_pop_push) {
  s21::queue<int> q;
  std::queue<int> qq;
  q.push(5);
  q.push(22);
  q.pop();
  q.push(33);
  qq.push(5);
  qq.push(22);
  qq.pop();
  qq.push(33);
  ASSERT_TRUE(check_qs(q, qq));
}

TEST(push, in_for) {
  s21::queue<int> q;
  std::queue<int> qq;
  for (int i = 0; i < 1000; ++i) {
    q.push(i);
    qq.push(i);
  }
  ASSERT_TRUE(check_qs(q, qq));
}

TEST(swap, empty) {
  s21::queue<int> q;
  std::queue<int> qq;
  s21::queue<int> q_swap;
  std::queue<int> qq_swap;
  q.swap(q_swap);
  qq.swap(qq_swap);
  ASSERT_TRUE(check_qs(q, qq));
  ASSERT_TRUE(check_qs(q_swap, qq_swap));
}

TEST(swap, def) {
  s21::queue<int> q({1, 5, 23, 111});
  std::queue<int> qq({1, 5, 23, 111});
  s21::queue<int> q_swap({7, 23, 51, 77});
  std::queue<int> qq_swap({7, 23, 51, 77});
  q.swap(q_swap);
  qq.swap(qq_swap);
  ASSERT_TRUE(check_qs(q, qq));
  ASSERT_TRUE(check_qs(q_swap, qq_swap));
}

TEST(funcs, emplace_back_normal_value) {
  s21::queue<int> l({1, 2, 3, 4, 5, 6, 7, 8, 16});
  std::queue<int> sl({1, 2, 3, 4, 5, 6, 7, 8, 16});
  l.emplace_back(-1, 2, 33);
  for (auto k : {-1, 2, 33})
    sl.push(k);
  ASSERT_TRUE(check_qs(l, sl));
}

TEST(funcs, emplace_back_empty) {
  s21::queue<int> l({1, 2, 3, 4, 5, 6, 7, 8, 16});
  std::queue<int> sl({1, 2, 3, 4, 5, 6, 7, 8, 16});
  l.emplace_back();
  ASSERT_TRUE(check_qs(l, sl));
}

TEST(funcs, emplace_back_empty_list) {
  s21::queue<int> l;
  std::queue<int> sl;
  l.emplace_back(1, 2, 3, 4, 5);

  for (auto k : {1, 2, 3, 4, 5})
    sl.push(k);

  ASSERT_TRUE(check_qs(l, sl));
}

TEST(funcs, emplace_back_empty_all) {
  s21::queue<int> l;
  std::queue<int> sl;
  l.emplace_back();

  ASSERT_TRUE(check_qs(l, sl));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}